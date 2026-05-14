#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPlacePortafilter()
{
  mtc::Task task;
  task.stages()->setName("place portafilter");
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
  cartesian_planner->setMaxVelocityScalingFactor(0.02);
  cartesian_planner->setMaxAccelerationScalingFactor(0.02);
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  // Get current robot state (with cup holder attached)
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Allow collisions for approach to tool station
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow portafilter/station collisions");
    stage->allowCollisions("portafilter", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("portafilter", std::vector<std::string>{"tool_station"}, true);
    task.add(std::move(stage));
  }

  // Move to tool station area
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to tool station",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate place pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->setMonitoredStage(current_state_ptr);

    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "world";
    target_pose.pose.position.x = -0.383;
    target_pose.pose.position.y = -0.171;
    target_pose.pose.position.z =  0.490;
    target_pose.pose.orientation.x = -0.478;
    target_pose.pose.orientation.y = -0.478;
    target_pose.pose.orientation.z = -0.521;
    target_pose.pose.orientation.w =  0.521;

    stage->setPose(target_pose);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);

    task.add(std::move(wrapper));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("insert into tool station", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.10, 0.10);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Detach cup holder from gripper
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach portafilter");
    stage->detachObject("portafilter", hand_frame);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("twist unlock", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    
    std::map<std::string, double> joint_deltas;
    joint_deltas["joint6"] = -M_PI / 3.0;
    stage->setDirection(joint_deltas);
    stage->setMinMaxDistance(0.0, M_PI / 3.0);
    
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat holder", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;
    vec.vector.y = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  return task;
}