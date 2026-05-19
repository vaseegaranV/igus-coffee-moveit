#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createAttachPortafilterFromCoffeeMachine()
{
  mtc::Task task;
  task.stages()->setName("attach portafilter from coffee machine");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);


  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name       = "female_connector_eef";
  const std::string hand_frame     = "gripper_link";


  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);


  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);


  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.1);
  cartesian_planner->setMaxAccelerationScalingFactor(0.1);
  cartesian_planner->setStepSize(0.01);


  mtc::Stage* current_state_ptr = nullptr;

  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to grinder",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach holder", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;
    vec.vector.y = -1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate holder grasp");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "holder_grasp");
    stage->setObject("portafilter");
    stage->setAngleDelta(2 * M_PI);
    stage->setMonitoredStage(current_state_ptr);
    
    moveit_msgs::msg::RobotState pregrasp_state;
    pregrasp_state.is_diff = true;
    stage->setPreGraspPose(pregrasp_state);
    
    Eigen::Isometry3d grasp_transform = Eigen::Isometry3d::Identity();
    grasp_transform.translation().y() = -0.25;
    grasp_transform.translation().x() = -0.062;
    grasp_transform.translation().z() = 0.004;
    grasp_transform.rotate(Eigen::AngleAxisd(25.02 * M_PI / 180.0, Eigen::Vector3d::UnitY()));
    
    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("holder grasp IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(grasp_transform, hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);
    
    task.add(std::move(wrapper));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("twist lock", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    
    std::map<std::string, double> joint_deltas;
    joint_deltas["joint6"] = M_PI / 3.0;
    stage->setDirection(joint_deltas);
    stage->setMinMaxDistance(0.0, M_PI / 3.0);
    
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow holder/tool_station for attach");
    stage->allowCollisions("portafilter", std::vector<std::string>{"tool_station"}, true);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach portafilter");
    stage->attachObject("portafilter", hand_frame);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.02, 0.05);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  return task;
}
