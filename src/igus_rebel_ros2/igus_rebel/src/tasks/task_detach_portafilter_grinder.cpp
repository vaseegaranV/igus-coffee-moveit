#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createDetachPortafilterFromGrinder()
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
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
    //stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"delivery_station"}, true);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup");
    stage->detachObject("portafilter", hand_frame);
    task.add(std::move(stage));
  }

    // Twist unlock: rotate joint6 by -60° to disengage bayonet
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("twist unlock", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });

    std::map<std::string, double> joint_deltas;
    joint_deltas["joint6"] = M_PI / 3.0;  // reverse of twist lock
    stage->setDirection(joint_deltas);
    stage->setMinMaxDistance(0.0, M_PI / 3.0);

    task.add(std::move(stage));
  }

  // Retreat along +Y axis (reverse of approach)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;
    vec.vector.y = 1.0;  // reverse of approach
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  return task;
}