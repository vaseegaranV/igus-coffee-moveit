#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPickCupTask()
{
  mtc::Task task;
  task.stages()->setName("pick cup from delivery station");
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
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to delivery station",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Generate pick pose
  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate pick pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->setMonitoredStage(current_state_ptr);

    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "world";
    target_pose.pose.position.x = 0.145;
    target_pose.pose.position.y = -0.355;
    target_pose.pose.position.z = 0.123;
    target_pose.pose.orientation.x = 0.0;
    target_pose.pose.orientation.y = -0.7071;
    target_pose.pose.orientation.z = 0.0;
    target_pose.pose.orientation.w = 0.7071;

    stage->setPose(target_pose);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("pick IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);

    task.add(std::move(wrapper));
  }

  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
    //stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
    stage->allowCollisions("portafilter", std::vector<std::string>{"cup_holder"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"delivery_station"}, true);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
    stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
    task.add(std::move(stage));
  }

  // Approach from world -Y
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.1, 0.1);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = -1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  // Move up slightly in world +Z
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift slightly", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.07);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  // Attach cup
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup");
    stage->attachObject("object", hand_frame);
    task.add(std::move(stage));
  }

  // Lift up
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.1);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  return task;
}