// #include "igus_rebel/simple_task.hpp"

// mtc::Task SimpleTask::createMoveToDeliveryStation()
// {
//   mtc::Task task;
//   task.stages()->setName("move cup to machine");
//   task.loadRobotModel(node_);
//   task.enableIntrospection(true);

//   const std::string arm_group_name = "igus_rebel_arm";
//   const std::string eef_name = "female_connector_eef";
//   const std::string hand_frame = "gripper_link";
  
//   task.setProperty("group", arm_group_name);
//   task.setProperty("eef", eef_name);
//   task.setProperty("ik_frame", hand_frame);

//   auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
//   sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
//   sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);
  
//   auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
//   cartesian_planner->setMaxVelocityScalingFactor(0.1);
//   cartesian_planner->setMaxAccelerationScalingFactor(0.1);
//   cartesian_planner->setStepSize(0.01);

//   mtc::Stage* current_state_ptr = nullptr;

//   // Get current robot state (with cup holder attached)
//   {
//     auto stage = std::make_unique<mtc::stages::CurrentState>("current");
//     current_state_ptr = stage.get();
//     task.add(std::move(stage));
//   }

//   // Move to coffee cup area
//   {
//     auto stage = std::make_unique<mtc::stages::Connect>(
//         "move to cup",
//         mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
//     stage->setTimeout(5.0);
//     stage->properties().configureInitFrom(mtc::Stage::PARENT);
//     task.add(std::move(stage));
//   }

//   // Allow collisions between coffee cup and gripper/cup_holder
//   {
//     auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
//     stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
//     stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
//     stage->allowCollisions("coffee_machine", std::vector<std::string>{"gripper_link"}, true);
//     task.add(std::move(stage));
//   }

//   {
//     auto stage = std::make_unique<mtc::stages::GeneratePose>("generate delivery pose");
//     stage->properties().configureInitFrom(mtc::Stage::PARENT);
//     stage->setMonitoredStage(current_state_ptr);

//     geometry_msgs::msg::PoseStamped target_pose;
//     target_pose.header.frame_id = "world";
//     target_pose.pose.position.x = 0.145;
//     target_pose.pose.position.y = -0.475;
//     target_pose.pose.position.z = 0.153;
//     target_pose.pose.orientation.x = 0.0;
//     target_pose.pose.orientation.y = -0.7071;
//     target_pose.pose.orientation.z = 0.0;
//     target_pose.pose.orientation.w = 0.7071;

//     stage->setPose(target_pose);

//     auto wrapper = std::make_unique<mtc::stages::ComputeIK>("delivery IK", std::move(stage));
//     wrapper->setMaxIKSolutions(8);
//     wrapper->setMinSolutionDistance(1.0);
//     wrapper->setIKFrame(hand_frame);
//     wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
//     wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
//     wrapper->setIgnoreCollisions(true);

//     task.add(std::move(wrapper));
//   }

//   // Detach the coffee cup — leave it at the machine
//   {
//     auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup");
//     stage->detachObject("object", hand_frame);
//     task.add(std::move(stage));
//   }

//   // Retreat — move down along world -Z
//   {
//     auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
//     stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
//     stage->setMinMaxDistance(0.02, 0.03);
//     stage->setIKFrame(hand_frame);
 
//     geometry_msgs::msg::Vector3Stamped vec;
//     vec.header.frame_id = "world";
//     vec.vector.z = -1.0;
//     stage->setDirection(vec);
 
//     task.add(std::move(stage));
//   }
 
//   // Retreat — move back along world +Y
//   {
//     auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
//     stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
//     stage->setMinMaxDistance(0.03, 0.13);
//     stage->setIKFrame(hand_frame);
 
//     geometry_msgs::msg::Vector3Stamped vec;
//     vec.header.frame_id = "gripper_link";
//     vec.vector.y = 1.0;
//     stage->setDirection(vec);
 
//     task.add(std::move(stage));
//   }

//   return task;
// }

#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createMoveToDeliveryStation()
{
  mtc::Task task;
  task.stages()->setName("move cup to delivery station");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);

  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name       = "female_connector_eef";
  const std::string hand_frame     = "gripper_link";

  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);

  // Cup target on delivery station (matches cup's spawn position with OX/OY/OZ offsets)
  // setup_environment: x = 0.115 + OX, y = -0.553 + OY, z = 0.115 + OZ
  // OX = +0.030, OY = -0.042, OZ = -0.012
  const double PLACE_X =  0.145;
  const double PLACE_Y = -0.465;
  const double PLACE_Z =  0.103;

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);

  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  // Current state (cup + holder attached to gripper)
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Allow cup, holder, and arm links to brush nearby stations
  mtc::Stage* allow_collisions_ptr = nullptr;
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow delivery collisions");

    auto all_links = task.getRobotModel()->getLinkModelNamesWithCollisionGeometry();
    stage->allowCollisions("delivery_station", all_links, true);
    stage->allowCollisions("tamping_station",  all_links, true);
    stage->allowCollisions("bin_station",      all_links, true);
    stage->allowCollisions("no_go_zone",       all_links, true);
    stage->allowCollisions("coffee_machine", all_links, true);

    stage->allowCollisions("object",     std::vector<std::string>{"delivery_station"}, true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"delivery_station"}, true);
    stage->allowCollisions("object",     std::vector<std::string>{"tamping_station"},  true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"tamping_station"},  true);
    stage->allowCollisions("object",     std::vector<std::string>{"bin_station"},      true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"bin_station"},      true);
    stage->allowCollisions("object",     std::vector<std::string>{"no_go_zone"},       true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"no_go_zone"},       true);
    stage->allowCollisions("object",     std::vector<std::string>{"cup_holder"},       true);
    stage->allowCollisions("object",     std::vector<std::string>{"coffee_machine"}, true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"coffee_machine"}, true);

    allow_collisions_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Lift cup up first to clear the coffee machine before traveling to delivery
  {
  auto stage = std::make_unique<mtc::stages::MoveRelative>("lift over machine", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.10, 0.20);
  stage->setIKFrame(hand_frame);

  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.z = 1.0;
  stage->setDirection(vec);

  task.add(std::move(stage));
  }

  // Free-space move toward the hover pose
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to hover above station",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Hover pose: directly above the delivery target (no forward offset — just straight down)
  {
    auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate hover pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "delivery_hover");
    stage->setObject("object");
    stage->setMonitoredStage(allow_collisions_ptr);

    geometry_msgs::msg::PoseStamped target;
    target.header.frame_id = "world";
    target.pose.position.x = PLACE_X;
    target.pose.position.y = PLACE_Y;
    target.pose.position.z = PLACE_Z + 0.19;

    // Same cup-upright orientation that worked at the coffee machine
    target.pose.orientation.x =  0.0;
    target.pose.orientation.y = -0.7071;
    target.pose.orientation.z =  0.0;
    target.pose.orientation.w =  0.7071;
    stage->setPose(target);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("hover pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    task.add(std::move(wrapper));
  }

  // Lower straight down onto the station (Cartesian, predictable)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lower onto station", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Detach the cup — leave it on the delivery station
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup");
    stage->detachObject("object", hand_frame);
    task.add(std::move(stage));
  }

  // Drop down a little clear of the cup before backing out (world -Z)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lower clear", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.005, 0.07);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Retreat — move back along world +Y
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from delivery", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.03, 0.13);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = 1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  return task;
}