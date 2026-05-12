#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createPickupCupHolderTask()
{

  mtc::Task task;
  task.stages()->setName("pick cup holder");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);

  // Robot configuration
  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name = "female_connector_eef";
  const std::string hand_frame = "gripper_link";
  
  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);

  // Sampling planner for joint-space movements
  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);
  
  // Cartesian planner for straight-line movements
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.1);
  cartesian_planner->setMaxAccelerationScalingFactor(0.1);
  cartesian_planner->setStepSize(0.01);
  


  mtc::Stage* current_state_ptr = nullptr;
  
  // Stage 1: Get current robot state
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }
  
  // Stage 2: Move to tool station area
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to tool station",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }
  
  // Stage 3: Pick cup holder sequence
  {
    auto grasp_holder = std::make_unique<mtc::SerialContainer>("pick cup holder");
    task.properties().exposeTo(grasp_holder->properties(), { "eef", "group", "ik_frame" });
    grasp_holder->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

    // Allow collisions between cup holder and gripper/tool station during approach
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow connector/holder collision");
      stage->allowCollisions("cup_holder", std::vector<std::string>{"gripper_link"}, true);
      stage->allowCollisions("cup_holder", std::vector<std::string>{"tool_station"}, true);
      grasp_holder->insert(std::move(stage));
    }
    
    // Approach cup holder along -Y axis in gripper frame
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach holder", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.10);
      stage->setIKFrame(hand_frame);
      
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.y = -1.0;
      stage->setDirection(vec);
      
      grasp_holder->insert(std::move(stage));
    }
    
    // Generate grasp pose for cup holder with rotated approach
    {
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate holder grasp");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "holder_grasp");
      stage->setObject("cup_holder");
      stage->setAngleDelta(2 * M_PI);
      stage->setMonitoredStage(current_state_ptr);
      
      moveit_msgs::msg::RobotState pregrasp_state;
      pregrasp_state.is_diff = true;
      stage->setPreGraspPose(pregrasp_state);
      
      // Transform: offset -0.01m in Y, rotate 25.02° about Y for bayonet alignment
      Eigen::Isometry3d grasp_transform = Eigen::Isometry3d::Identity();
      grasp_transform.translation().y() = -0.01;
      grasp_transform.rotate(Eigen::AngleAxisd(25.02 * M_PI / 180.0, Eigen::Vector3d::UnitY()));
      
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("holder grasp IK", std::move(stage));
      wrapper->setMaxIKSolutions(8);
      wrapper->setMinSolutionDistance(1.0);
      wrapper->setIKFrame(grasp_transform, hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      wrapper->setIgnoreCollisions(true);
      
      grasp_holder->insert(std::move(wrapper));
    }

    // Keep collisions allowed after grasp
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("maintain allowed collisions");
      stage->allowCollisions("cup_holder", std::vector<std::string>{"gripper_link"}, true);
      stage->allowCollisions("cup_holder", std::vector<std::string>{"tool_station"}, true);
      grasp_holder->insert(std::move(stage));
    }
    
    // Twist lock: rotate joint6 by 60° to engage bayonet
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("twist lock", sampling_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      
      std::map<std::string, double> joint_deltas;
      joint_deltas["joint6"] = M_PI / 3.0;
      stage->setDirection(joint_deltas);
      stage->setMinMaxDistance(0.0, M_PI / 3.0);
      
      grasp_holder->insert(std::move(stage));
    }

    // Allow cup holder/tool station collision before attaching
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow holder/tool_station for attach");
      stage->allowCollisions("cup_holder", std::vector<std::string>{"tool_station"}, true);
      grasp_holder->insert(std::move(stage));
    }
    
    // Attach cup holder to gripper
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup holder");
      stage->attachObject("cup_holder", hand_frame);
      grasp_holder->insert(std::move(stage));
    }
    
    // Retreat along +X axis in gripper frame
    {
       auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
       stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
       stage->setMinMaxDistance(0.05, 0.10);
       stage->setIKFrame(hand_frame);
      
       geometry_msgs::msg::Vector3Stamped vec;
       vec.header.frame_id = hand_frame;
       vec.vector.x = 1.0;
       stage->setDirection(vec);
      
       grasp_holder->insert(std::move(stage));
    }
    
    task.add(std::move(grasp_holder));
  }
  
  return task;
}