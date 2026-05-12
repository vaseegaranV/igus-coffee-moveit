#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPickCupFromMachineTask()
{
  mtc::Task task;
  task.stages()->setName("pick cup from machine");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);

  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name       = "female_connector_eef";
  const std::string hand_frame     = "gripper_link";

  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);

  // Cup position on coffee machine drip tray (same as place task)
  const double CUP_X = -0.346;
  const double CUP_Y = -0.200;
  const double CUP_Z =  0.165;

  // Hover offsets (mirror of place task: same forward and above offsets)
  const double APPROACH_Y_OFFSET = 0.04;   // 4cm in front of cup (so we descend clear of machine)
  const double APPROACH_Z_OFFSET = 0.30;   // 30cm above cup
  // After lowering, gripper sits ~5cm below the cup base before lifting up to wedge-grip
  const double GRIPPER_BELOW_CUP = 0.05;

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);

  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  // Stage 1: Current state
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Stage 2: Allow cup, holder, machine, no-go-zone interactions
  mtc::Stage* allow_collisions_ptr = nullptr;
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow pickup collisions");

    auto all_links = task.getRobotModel()->getLinkModelNamesWithCollisionGeometry();
    stage->allowCollisions("coffee_machine", all_links, true);
    stage->allowCollisions("no_go_zone",     all_links, true);

    stage->allowCollisions("object",     std::vector<std::string>{"coffee_machine"}, true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"coffee_machine"}, true);
    stage->allowCollisions("object",     std::vector<std::string>{"cup_holder"},     true);
    stage->allowCollisions("object",     std::vector<std::string>{"no_go_zone"},     true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"no_go_zone"},     true);

    allow_collisions_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Stage 3: Free-space move to hover pose (above and in front of cup)
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to hover above cup",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Stage 4: Generate hover pose for the gripper (above and in front of the cup)
  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate hover pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "pickup_hover");
    stage->setMonitoredStage(allow_collisions_ptr);

    geometry_msgs::msg::PoseStamped target;
    target.header.frame_id = "world";
    target.pose.position.x = CUP_X;
    target.pose.position.y = CUP_Y + APPROACH_Y_OFFSET;
    target.pose.position.z = CUP_Z + APPROACH_Z_OFFSET;

    // Same wrist orientation we used for the original cup pickup
    // (matches what task 2 used; cup should fit into gripper the same way)
    target.pose.orientation.x =  0.354;
    target.pose.orientation.y = -0.612;
    target.pose.orientation.z =  0.354;
    target.pose.orientation.w =  0.612;
    stage->setPose(target);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("hover IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });

    task.add(std::move(wrapper));
  }

  // Stage 5: Lower past the machine to a position next to the cup (Cartesian)
  // Final gripper Z = CUP_Z - GRIPPER_BELOW_CUP, so it lands below the cup base
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lower past machine", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    // Descent distance: APPROACH_Z_OFFSET + GRIPPER_BELOW_CUP = 0.30 + 0.05 = 0.35
    stage->setMinMaxDistance(0.34, 0.36);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Stage 6: Slide gripper toward the cup (-Y, into the slot under the cup)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("slide under cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.035, 0.045);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Stage 7: Allow cup-vs-gripper collisions for the wedge-grip motion
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup vs gripper");
    stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"cup_holder"},   true);
    task.add(std::move(stage));
  }

  // Stage 8: Lift cup along world +Z (wedge-grip motion, same as task 2)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift to wedge cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.04, 0.07);   // small lift to engage the wedge grip
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Stage 9: Attach the cup to the gripper
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup");
    stage->attachObject("object", hand_frame);
    task.add(std::move(stage));
  }

  // Stage 10: Slide back forward (+Y) to clear the slot before lifting away
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("slide out of slot", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.04, 0.06);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = 1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Stage 11: Lift well clear of the machine (world +Z)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift away", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.20, 0.30);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  return task;
}