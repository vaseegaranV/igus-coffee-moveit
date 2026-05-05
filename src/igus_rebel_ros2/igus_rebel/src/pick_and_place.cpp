#include "igus_rebel/simple_task.hpp"
#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <geometric_shapes/shapes.h>
#include <geometric_shapes/shape_operations.h>
#include <geometric_shapes/mesh_operations.h>
#include <moveit/collision_detection/collision_matrix.hpp>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("simple_moveto");
namespace mtc = moveit::task_constructor;

SimpleTask::SimpleTask(const rclcpp::NodeOptions& options)
  : node_{ std::make_shared<rclcpp::Node>("simple_moveto_node", options) }
{
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr SimpleTask::getNodeBaseInterface()
{
  return node_->get_node_base_interface();
}

void SimpleTask::doTask()
{
  // Set up the planning scene with all collision objects
  setupPlanningScene();
  
  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Cup Holder ===");
  task_ = createPickupCupHolderTask();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick holder planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick holder execution failed");
    return;
  }
  
  // Execute Task 2: Pick up the coffee cup (with cup holder attached)
  RCLCPP_INFO(LOGGER, "=== TASK 2: Pick Coffee Cup ===");
  task_ = createPickCupTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Pick cup planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick cup execution failed");
    return;
  }

  // // Execute Task 3: Deliver coffee cup
  // RCLCPP_INFO(LOGGER, "=== TASK 3: Deliver Coffee Cup ===");
  // task_ = createMoveToDeliveryStation();
  // task_.init();
  // if (!task_.plan(20)) {
  //   RCLCPP_ERROR(LOGGER, "Deliver cup planning failed");
  //   return;
  // }
  // task_.introspection().publishSolution(*task_.solutions().front());
  // result = task_.execute(*task_.solutions().front());
  // if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
  //   RCLCPP_ERROR(LOGGER, "Pick cup execution failed");
  //   return;
  // }


  RCLCPP_INFO(LOGGER, "=== TASK 3: Place Coffee Cup ===");
  task_ = createMoveToCoffeeMachine();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "move to coffee machine planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "move to coffee machine execution failed");
    return;
  }
  

  RCLCPP_INFO(LOGGER, "=== TASK 4: Place Cup Holder ===");
  task_ = createPlaceCupHolderTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "place cup holder failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "place cup holder failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== Going Home ===");
  task_ = createGoHomeTask();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Go home planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "going home failed");
    return;
  }
  
  RCLCPP_INFO(LOGGER, "All tasks completed successfully!");
}


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
  cartesian_planner->setMaxVelocityScalingFactor(0.02);
  cartesian_planner->setMaxAccelerationScalingFactor(0.02);
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


mtc::Task SimpleTask::createPickCupTask()
{
  mtc::Task task;
  task.stages()->setName("pick coffee cup");
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
  cartesian_planner->setMaxVelocityScalingFactor(0.1);
  cartesian_planner->setMaxAccelerationScalingFactor(0.1);
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  // Get current robot state (with cup holder attached)
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Move to coffee cup area
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to cup",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Approach coffee cup along +Y axis in gripper frame
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.10);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;
    vec.vector.y = -1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  // Generate grasp pose and compute IK for coffee cup
  {
    auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate cup grasp");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "cup_grasp");
    stage->setObject("object");
    stage->setAngleDelta(M_PI / 6);
    stage->setMonitoredStage(current_state_ptr);
    
    moveit_msgs::msg::RobotState pregrasp_state;
    pregrasp_state.is_diff = true;
    stage->setPreGraspPose(pregrasp_state);
    
    Eigen::Isometry3d grasp_transform = Eigen::Isometry3d::Identity();
    grasp_transform.translation().y() = -0.13;
    grasp_transform.translation().x() = -0.02;
    grasp_transform.rotate(Eigen::AngleAxisd(90 * M_PI / 180.0, Eigen::Vector3d::UnitY()));
    
    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("cup grasp IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(grasp_transform, hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    
    task.add(std::move(wrapper));
  }

  // Allow collisions between coffee cup and gripper/cup_holder
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
    stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
    task.add(std::move(stage));
  }

  // Lift cup slightly along world +Z before attaching
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.07);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  // Attach coffee cup to gripper
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup");
    stage->attachObject("object", hand_frame);
    task.add(std::move(stage));
  }

  // Lift cup further along world +Z after attaching
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift cup higher", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.005, 0.3);
    stage->setIKFrame(hand_frame);
    
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    
    task.add(std::move(stage));
  }

  return task;
}


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
 
  // ── Tunable placement target (world frame) ─────────────────────────────
  // Coffee machine origin: (0.419, -0.316, 0.010)
  const double MACHINE_X        = -0.356;
  const double MACHINE_Y        = -0.457;
  const double PLACE_X_OFFSET   = -0.1;     // along world X relative to machine
  const double PLACE_Y_OFFSET   = 0.215;   // negative = pushed back into machine
  const double PLACE_Z          = 0.24;    // cup base height — tune
 
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
 
  // Allow cup & holder to collide with the coffee machine during placement
  mtc::Stage* allow_collisions_ptr = nullptr;
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup/holder vs coffee_machine");
    stage->allowCollisions("object",     std::vector<std::string>{"coffee_machine"}, true);
    //stage->allowCollisions("cup_holder", std::vector<std::string>{"coffee_machine"}, true);
    stage->allowCollisions("object",     std::vector<std::string>{"cup_holder"}, true);
    allow_collisions_ptr = stage.get();
    task.add(std::move(stage));
  }
 
  // Move to pre-place pose near the machine
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to machine",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }
 
  // Generate place pose by sampling orientations around the cup's attached frame
  {
    auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate place pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "place_pose");
    stage->setObject("object");                       // the attached coffee cup
    stage->setMonitoredStage(allow_collisions_ptr);   // monitor AFTER collisions allowed
 
    // Where the cup itself should end up in world
    geometry_msgs::msg::PoseStamped target;
    target.header.frame_id = "world";
    target.pose.position.x = MACHINE_X + PLACE_X_OFFSET;
    target.pose.position.y = MACHINE_Y + PLACE_Y_OFFSET;
    target.pose.position.z = PLACE_Z;
 
    // Wrist orientation copied from `tf2_echo world gripper_link` after task 2
    target.pose.orientation.x =  0.354;
    target.pose.orientation.y = -0.612;
    target.pose.orientation.z =  0.354;
    target.pose.orientation.w =  0.612;
 
    stage->setPose(target);
 
    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
 
    task.add(std::move(wrapper));
  }
 
  // Insert cup — slide toward the machine in world -Y
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("insert cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.005, 0.06);
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

  // Retreat — move down along world -Z
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.04, 0.05);
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
    stage->setMinMaxDistance(0.06, 0.13);
    stage->setIKFrame(hand_frame);
 
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "gripper_link";
    vec.vector.y = 1.0;
    stage->setDirection(vec);
 
    task.add(std::move(stage));
  }
 
  // // Small lift clear of the machine before ending
  // {
  //   auto stage = std::make_unique<mtc::stages::MoveRelative>("lift clear", cartesian_planner);
  //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  //   stage->setMinMaxDistance(0.03, 0.12);
  //   stage->setIKFrame(hand_frame);
 
  //   geometry_msgs::msg::Vector3Stamped vec;
  //   vec.header.frame_id = "world";
  //   vec.vector.z = 1.0;
  //   stage->setDirection(vec);
 
  //   task.add(std::move(stage));
  // }
 
  return task;
}

mtc::Task SimpleTask::createPlaceCupHolderTask()
{
  mtc::Task task;
  task.stages()->setName("place cup holder");
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
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow holder/station collisions");
    stage->allowCollisions("cup_holder", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("cup_holder", std::vector<std::string>{"tool_station"}, true);
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
    target_pose.pose.position.x = -0.517;
    target_pose.pose.position.y = -0.240;
    target_pose.pose.position.z =  0.437;
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
    auto stage = std::make_unique<mtc::stages::MoveRelative>("insert into station", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.03, 0.03);
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);

    task.add(std::move(stage));
  }

  // Detach cup holder from gripper
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup holder");
    stage->detachObject("cup_holder", hand_frame);
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

  // // Approach tool station along -X axis (reverse of retreat)
  // {
  //   auto stage = std::make_unique<mtc::stages::MoveRelative>("approach station", cartesian_planner);
  //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  //   stage->setMinMaxDistance(0.0, 0.10);
  //   stage->setIKFrame(hand_frame);

  //   geometry_msgs::msg::Vector3Stamped vec;
  //   vec.header.frame_id = hand_frame;
  //   vec.vector.x = -1.0;  // reverse of retreat
  //   stage->setDirection(vec);

  //   task.add(std::move(stage));
  // }

  // // Detach cup holder from gripper
  // {
  //   auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup holder");
  //   stage->detachObject("cup_holder", hand_frame);
  //   task.add(std::move(stage));
  // }

  // // Twist unlock: rotate joint6 by -60° to disengage bayonet
  // {
  //   auto stage = std::make_unique<mtc::stages::MoveRelative>("twist unlock", sampling_planner);
  //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });

  //   std::map<std::string, double> joint_deltas;
  //   joint_deltas["joint6"] = M_PI / 3.0;  // reverse of twist lock
  //   stage->setDirection(joint_deltas);
  //   stage->setMinMaxDistance(0.0, M_PI / 3.0);

  //   task.add(std::move(stage));
  // }

  // // Retreat along +Y axis (reverse of approach)
  // {
  //   auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
  //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
  //   stage->setMinMaxDistance(0.05, 0.10);
  //   stage->setIKFrame(hand_frame);

  //   geometry_msgs::msg::Vector3Stamped vec;
  //   vec.header.frame_id = hand_frame;
  //   vec.vector.y = 1.0;  // reverse of approach
  //   stage->setDirection(vec);

  //   task.add(std::move(stage));
  // }

  return task;
}

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

mtc::Task SimpleTask::createMoveToDeliveryStation()
{
  mtc::Task task;
  task.stages()->setName("move cup to machine");
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
  cartesian_planner->setMaxVelocityScalingFactor(0.1);
  cartesian_planner->setMaxAccelerationScalingFactor(0.1);
  cartesian_planner->setStepSize(0.01);

  mtc::Stage* current_state_ptr = nullptr;

  // Get current robot state (with cup holder attached)
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // Move to coffee cup area
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to cup",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Allow collisions between coffee cup and gripper/cup_holder
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collisions");
    stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
    stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
    stage->allowCollisions("coffee_machine", std::vector<std::string>{"gripper_link"}, true);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate delivery pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->setMonitoredStage(current_state_ptr);

    geometry_msgs::msg::PoseStamped target_pose;
    target_pose.header.frame_id = "world";
    target_pose.pose.position.x = 0.200;
    target_pose.pose.position.y = -0.322;
    target_pose.pose.position.z = 0.246;
    target_pose.pose.orientation.x = 0.0;
    target_pose.pose.orientation.y = -0.7071;
    target_pose.pose.orientation.z = 0.0;
    target_pose.pose.orientation.w = 0.7071;

    stage->setPose(target_pose);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("delivery IK", std::move(stage));
    wrapper->setMaxIKSolutions(8);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);

    task.add(std::move(wrapper));
  }

  // Detach the coffee cup — leave it at the machine
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach cup");
    stage->detachObject("object", hand_frame);
    task.add(std::move(stage));
  }

  // Retreat — move down along world -Z
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.04, 0.05);
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
    stage->setMinMaxDistance(0.03, 0.13);
    stage->setIKFrame(hand_frame);
 
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "gripper_link";
    vec.vector.y = 1.0;
    stage->setDirection(vec);
 
    task.add(std::move(stage));
  }

  return task;
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.automatically_declare_parameters_from_overrides(true);

  auto simple_task_node = std::make_shared<SimpleTask>(options);
  rclcpp::executors::MultiThreadedExecutor executor;

  // Spin executor in separate thread to handle callbacks
  auto spin_thread = std::make_unique<std::thread>([&executor, &simple_task_node]() {
    executor.add_node(simple_task_node->getNodeBaseInterface());
    executor.spin();
    executor.remove_node(simple_task_node->getNodeBaseInterface());
  });

  // Execute the task sequence
  simple_task_node->doTask();

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}