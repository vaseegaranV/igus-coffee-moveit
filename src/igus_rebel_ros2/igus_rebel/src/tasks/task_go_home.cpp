#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createGoHomeTask()
{
  mtc::Task task;
  task.stages()->setName("go home");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);

  const std::string arm_group_name = "igus_rebel_arm";

  task.setProperty("group", arm_group_name);
  task.setProperty("eef", "female_connector_eef");
  task.setProperty("ik_frame", "gripper_link");

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);

  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveTo>("home position", sampling_planner);
    stage->setGroup(arm_group_name);
    stage->setGoal("home");
    task.add(std::move(stage));
  }

  return task;
}