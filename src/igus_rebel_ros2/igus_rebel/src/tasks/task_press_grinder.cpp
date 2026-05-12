#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPressGrinderPowerButtonTask()
{
  mtc::Task task;
  task.stages()->setName("press grinder power button");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);


  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name = "female_connector_eef";
  const std::string hand_frame = "gripper_link";


  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);


  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);


  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(0.005);


  mtc::Stage* current_state_ptr = nullptr;


  // Stage 1: Current state
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }


  // Stage 2: Allow collisions with grinder
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow grinder collisions");
    stage->allowCollisions("grinder", std::vector<std::string>{"gripper_link"}, true);
    task.add(std::move(stage));
  }


  // Stage 3: Move to pre-press pose (in front of power button)
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to grinder",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(10.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }


  // Stage 4: Generate pre-press pose — gripper in front of button, pointing toward grinder
  // Grinder is at approx x=0.483, y=-0.427, z=0.013 (with offsets)
  // Power button assumed to be on the front face of the grinder
  // TUNE these values based on actual button position
  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate pre-press pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->setMonitoredStage(current_state_ptr);


    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "world";
    // Pre-press: 5cm in front of button — tune X, Y, Z to match actual button location
    target_pose.pose.position.x = 0.483;   // grinder x + OX
    target_pose.pose.position.y = -0.240;  // in front of grinder (less negative = closer to robot)
    target_pose.pose.position.z = 0.185;   // button height — tune this
    // Gripper pointing in +Y direction (toward grinder front face)
    target_pose.pose.orientation.x = 0.0;
    target_pose.pose.orientation.y = 0.7071;
    target_pose.pose.orientation.z = 0.0;
    target_pose.pose.orientation.w = 0.7071;


    stage->setPose(target_pose);


    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("pre-press IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);
    task.add(std::move(wrapper));
  }


  // Stage 5: Press - move toward grinder in +Y direction
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("press button", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.02, 0.05);  // press 2-5cm
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = -1.0;  // move toward grinder (negative Y)
    stage->setDirection(vec);


    task.add(std::move(stage));
  }


  // Stage 6: Retreat — pull back from button
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from button", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.02, 0.08);
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = 1.0;  // pull back
    stage->setDirection(vec);


    task.add(std::move(stage));
  }


  return task;
}