#include "igus_rebel/simple_task.hpp"


mtc::Task SimpleTask::createMoveToCoffeeMachine()
{
mtc::Task task;
task.stages()->setName("place cup at machine");
task.loadRobotModel(node_);
task.enableIntrospection(true);




const std::string arm_group_name = "igus_rebel_arm";
const std::string eef_name       = "female_connector_eef";
const std::string hand_frame     = "gripper_link";




task.setProperty("group", arm_group_name);
task.setProperty("eef", eef_name);
task.setProperty("ik_frame", hand_frame);




// Cup target position on coffee machine drip tray (measured via Publish Point)
const double PLACE_X = -0.316;
const double PLACE_Y = -0.242;
const double PLACE_Z =  0.153;




auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);




auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
cartesian_planner->setMaxVelocityScalingFactor(0.05);
cartesian_planner->setMaxAccelerationScalingFactor(0.05);
cartesian_planner->setStepSize(0.01);




mtc::Stage* current_state_ptr = nullptr;




// Current state (cup + holder already attached to gripper)
{
  auto stage = std::make_unique<mtc::stages::CurrentState>("current");
  current_state_ptr = stage.get();
  task.add(std::move(stage));
}




// Allow cup, holder, and arm links to brush the coffee machine during placement
mtc::Stage* allow_collisions_ptr = nullptr;
{
  auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow placement collisions");




  // Get every robot link with collision geometry
  auto all_links = task.getRobotModel()->getLinkModelNamesWithCollisionGeometry();




  // Allow every robot link to brush the coffee machine and the no_go_zone
  stage->allowCollisions("coffee_machine", all_links, true);
  stage->allowCollisions("no_go_zone",     all_links, true);




  // Cup, holder, machine, and no_go_zone interactions
  stage->allowCollisions("object",     std::vector<std::string>{"coffee_machine"}, true);
  stage->allowCollisions("cup_holder", std::vector<std::string>{"coffee_machine"}, true);
  stage->allowCollisions("object",     std::vector<std::string>{"cup_holder"},     true);
  stage->allowCollisions("object",     std::vector<std::string>{"no_go_zone"},     true);
  stage->allowCollisions("cup_holder", std::vector<std::string>{"no_go_zone"},     true);




  allow_collisions_ptr = stage.get();
  task.add(std::move(stage));
}


// Retreat — move back along world +Y
{
  auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.05, 0.335);
  stage->setIKFrame(hand_frame);
  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.y = 1.0;
  stage->setDirection(vec);
  task.add(std::move(stage));
}


// Stage: free-space move to hover pose above the drip tray
{
  auto stage = std::make_unique<mtc::stages::Connect>(
      "move to hover above tray",
      mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
  stage->setTimeout(5.0);
  stage->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage));
}




// Stage: generate the hover pose (same X/Y as place, higher Z)
{
  auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate hover pose");
  stage->properties().configureInitFrom(mtc::Stage::PARENT);
  stage->properties().set("marker_ns", "hover_pose");
  stage->setObject("object");
  stage->setMonitoredStage(allow_collisions_ptr);




  geometry_msgs::msg::PoseStamped target;
  target.header.frame_id = "world";
  target.pose.position.x = PLACE_X + 0.1;
  target.pose.position.y = PLACE_Y + 0.07;
  target.pose.position.z = PLACE_Z + 0.35;   // 30cm above final position — well above machine top
  target.pose.orientation.x = 0.0;
  target.pose.orientation.y = -0.7071;
  target.pose.orientation.z = 0.0;
  target.pose.orientation.w = 0.7071;
  stage->setPose(target);




  auto wrapper = std::make_unique<mtc::stages::ComputeIK>("hover pose IK", std::move(stage));
  wrapper->setMaxIKSolutions(8);
  wrapper->setMinSolutionDistance(1.0);
  wrapper->setIKFrame(hand_frame);
  wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
  wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
  task.add(std::move(wrapper));
}




// Stage: lower straight down to the place pose (Cartesian, predictable path)
{
  auto stage = std::make_unique<mtc::stages::MoveRelative>("lower onto tray", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.295, 0.365);   // ~20cm down, matching the hover offset
  stage->setIKFrame(hand_frame);




  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.z = -1.0;
  stage->setDirection(vec);




  task.add(std::move(stage));
}
// After "lower onto tray" — slide cup horizontally back into the tray
{
auto stage = std::make_unique<mtc::stages::MoveRelative>("nudge into tray", cartesian_planner);
stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
stage->setMinMaxDistance(0.03, 0.11);
stage->setIKFrame(hand_frame);




geometry_msgs::msg::Vector3Stamped vec;
vec.header.frame_id = "world";
vec.vector.x = -1.0;
stage->setDirection(vec);




task.add(std::move(stage));
}
// Insert cup — slide toward the machine in world -Y
{
  auto stage = std::make_unique<mtc::stages::MoveRelative>("insert cup", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.005, 0.12);
  stage->setIKFrame(hand_frame);




  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.y = -1.0;
  stage->setDirection(vec);




  task.add(std::move(stage));
}




// Detach the coffee cup — leave it at the machine
{
  auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup");
  stage->detachObject("object", hand_frame);
  task.add(std::move(stage));
}




// Drop down clear of the cup before backing out (world -Z)
{
  auto stage = std::make_unique<mtc::stages::MoveRelative>("lower clear", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.005, 0.05);
  stage->setIKFrame(hand_frame);
  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.z = -1.0;
  stage->setDirection(vec);
  task.add(std::move(stage));
}




// Retreat — move back along world +Y
{
  auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.03, 0.11);
  stage->setIKFrame(hand_frame);
  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.y = 1.0;
  stage->setDirection(vec);
  task.add(std::move(stage));
}




return task;
}



