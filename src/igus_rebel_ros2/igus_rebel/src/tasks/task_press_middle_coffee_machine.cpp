#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPressMiddleButtonTask()
{
 mtc::Task task;
 task.stages()->setName("press middle button");
 task.loadRobotModel(node_);
 task.enableIntrospection(true);
 const std::string arm_group_name = "igus_rebel_arm";
 const std::string eef_name       = "female_connector_eef";
 const std::string hand_frame     = "gripper_link";
 task.setProperty("group", arm_group_name);
 task.setProperty("eef", eef_name);
 task.setProperty("ik_frame", hand_frame);
 // ── Tunable button position (world frame) ─────────────────────────────
 // Middle button location measured via RViz Publish Point tool
 const double BUTTON_X = -0.361 + 0.030;
 const double BUTTON_Y = -0.328 - 0.012;
 const double BUTTON_Z =  0.266 - 0.012;
 // How far in front of the button to start (gripper tip clearance)
 const double PREPRESS_OFFSET_Y = 0.13;   // 5cm in front of button face
 // How far to push into the button
 const double PRESS_DEPTH       = 0.00005;   // 2cm push (tunable)
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
 // Stage 2: Allow gripper / cup_holder / arm to brush the coffee machine for the press
 mtc::Stage* allow_collisions_ptr = nullptr;
 {
  auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow press collisions");

  auto arm_links = task.getRobotModel()
                       ->getJointModelGroup(arm_group_name)
                       ->getLinkModelNamesWithCollisionGeometry();

  stage->allowCollisions("coffee_machine",  arm_links, true);
  stage->allowCollisions("coffee_machine",  std::vector<std::string>{"cup_holder"}, true);
  stage->allowCollisions("no_go_zone",      arm_links, true);
  stage->allowCollisions("no_go_zone",      std::vector<std::string>{"cup_holder"}, true);

  allow_collisions_ptr = stage.get();
  task.add(std::move(stage));
 }
 // Move back first to clear the coffee machine before approaching the button
 {
  auto stage = std::make_unique<mtc::stages::MoveRelative>("lift over machine", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.0, 0.40);   // 5-20cm lift — looser since we may already be high
  stage->setIKFrame(hand_frame);

  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.y = 1.0;
  stage->setDirection(vec);

  task.add(std::move(stage));
 }

  // Move up to clear the coffee machine before approaching the button
 {
  auto stage = std::make_unique<mtc::stages::MoveRelative>("lift over machine", cartesian_planner);
  stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  stage->setMinMaxDistance(0.0, 0.20);   // 5-20cm lift — looser since we may already be high
  stage->setIKFrame(hand_frame);

  geometry_msgs::msg::Vector3Stamped vec;
  vec.header.frame_id = "world";
  vec.vector.z = 1.0;
  stage->setDirection(vec);

  task.add(std::move(stage));
 }

  // Go to home before approaching the button — known-safe waypoint
 {
  auto stage = std::make_unique<mtc::stages::MoveTo>("via home", sampling_planner);
  stage->setGroup(arm_group_name);
  stage->setGoal("home");
  task.add(std::move(stage));
 }
 // Stage 3: Move arm toward the pre-press pose
 {
   auto stage = std::make_unique<mtc::stages::Connect>(
       "move to pre-press",
       mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
   stage->setTimeout(5.0);
   stage->properties().configureInitFrom(mtc::Stage::PARENT);
   task.add(std::move(stage));
 }
 // Stage 4: Generate pre-press pose and solve IK
 {
   auto stage = std::make_unique<mtc::stages::GeneratePose>("generate pre-press pose");
   stage->properties().configureInitFrom(mtc::Stage::PARENT);
   stage->properties().set("marker_ns", "press_pose");
   stage->setMonitoredStage(allow_collisions_ptr);
   geometry_msgs::msg::PoseStamped target;
   target.header.frame_id = "world";
   target.pose.position.x = BUTTON_X;
   target.pose.position.y = BUTTON_Y + PREPRESS_OFFSET_Y;   // start in front of the button
   target.pose.position.z = BUTTON_Z;
   // Wrist orientation: gripper pointing toward the machine (-Y).
   // This is the same orientation that worked for the cup pickup approach.
   // Adjust if the gripper "tip" isn't aligned with this in your robot.
   target.pose.orientation.x =  0.0;
   target.pose.orientation.y =  0.0;
   target.pose.orientation.z = -0.7071;
   target.pose.orientation.w =  0.7071;
   stage->setPose(target);
   auto wrapper = std::make_unique<mtc::stages::ComputeIK>("pre-press IK", std::move(stage));
   wrapper->setMaxIKSolutions(8);
   wrapper->setMinSolutionDistance(1.0);
   wrapper->setIKFrame(hand_frame);
   wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
   wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
   task.add(std::move(wrapper));
 }
 // Stage 5: Press — push gripper toward the button (world -Y)
 {
   auto stage = std::make_unique<mtc::stages::MoveRelative>("press button", cartesian_planner);
   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
   // stage->setMinMaxDistance(PRESS_DEPTH * 0.5, PREPRESS_OFFSET_Y + PRESS_DEPTH);
   stage->setMinMaxDistance(0.005, 0.12);   //Adjust max for button press
   stage->setIKFrame(hand_frame);
   geometry_msgs::msg::Vector3Stamped vec;
   vec.header.frame_id = "world";
   vec.vector.y = -1.0;
   stage->setDirection(vec);
   task.add(std::move(stage));
 }
 // Stage 6: Retract — pull gripper back from the button (world +Y)
 {
   auto stage = std::make_unique<mtc::stages::MoveRelative>("retract from button", cartesian_planner);
   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
   stage->setMinMaxDistance(0.003, 0.04);
   stage->setIKFrame(hand_frame);
   geometry_msgs::msg::Vector3Stamped vec;
   vec.header.frame_id = "world";
   vec.vector.y = 1.0;
   stage->setDirection(vec);
   task.add(std::move(stage));
 }
 return task;
}