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

class SimpleTask
{
public:
  SimpleTask(const rclcpp::NodeOptions& options);
  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();
  void doTask();

private:
  void setupPlanningScene();
  mtc::Task createPickupCupHolderTask();
  mtc::Task createPickCupTask();
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
};

SimpleTask::SimpleTask(const rclcpp::NodeOptions& options)
  : node_{ std::make_shared<rclcpp::Node>("simple_moveto_node", options) }
{
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr SimpleTask::getNodeBaseInterface()
{
  return node_->get_node_base_interface();
}

void SimpleTask::setupPlanningScene()
{
  RCLCPP_INFO(LOGGER, "Setting up planning scene...");
  
  moveit::planning_interface::PlanningSceneInterface psi;
  std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
  std::vector<moveit_msgs::msg::ObjectColor> object_colors;
  
  // Constants from Python file
  const double RAIL_BASE_Z = 0.0;
  const double RAIL_HEIGHT = 0.120;
  const double TABLE_SIZE_Z = 0.100;
  const double FLOOR_Z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE_SIZE_Z;
  const double _table_surface_z = RAIL_BASE_Z - RAIL_HEIGHT;
  
  const double CELL_WIDTH = 2.000;
  const double CELL_DEPTH = 1.000;
  const double CELL_HEIGHT = 1.587;
  const double CELL_WALL_T = 0.045;
  
  // ── Walls ──────────────────────────────────────────────────────────────
  {
    double hw = CELL_WIDTH / 2.0;
    double hd = CELL_DEPTH / 2.0;
    double wall_cz = FLOOR_Z + CELL_HEIGHT / 2.0;
    
    // Wall front
    moveit_msgs::msg::CollisionObject wall_front;
    wall_front.header.frame_id = "world";
    wall_front.id = "wall_front";
    
    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions = {CELL_WIDTH, CELL_WALL_T, CELL_HEIGHT};
    
    geometry_msgs::msg::Pose pose;
    pose.position.x = 0.0;
    pose.position.y = hd + CELL_WALL_T / 2;
    pose.position.z = wall_cz;
    pose.orientation.w = 1.0;
    
    wall_front.primitives.push_back(primitive);
    wall_front.primitive_poses.push_back(pose);
    wall_front.operation = wall_front.ADD;
    collision_objects.push_back(wall_front);
    
    moveit_msgs::msg::ObjectColor wall_front_color;
    wall_front_color.id = "wall_front";
    wall_front_color.color.r = 0.7;
    wall_front_color.color.g = 0.7;
    wall_front_color.color.b = 0.7;
    wall_front_color.color.a = 0.4;
    object_colors.push_back(wall_front_color);
    
    // Wall left
    moveit_msgs::msg::CollisionObject wall_left;
    wall_left.header.frame_id = "world";
    wall_left.id = "wall_left";
    
    primitive.dimensions = {CELL_WALL_T, CELL_DEPTH, CELL_HEIGHT};
    pose.position.x = -(hw + CELL_WALL_T / 2);
    pose.position.y = 0.0;
    pose.position.z = wall_cz;
    
    wall_left.primitives.push_back(primitive);
    wall_left.primitive_poses.push_back(pose);
    wall_left.operation = wall_left.ADD;
    collision_objects.push_back(wall_left);
    
    moveit_msgs::msg::ObjectColor wall_left_color;
    wall_left_color.id = "wall_left";
    wall_left_color.color.r = 0.7;
    wall_left_color.color.g = 0.7;
    wall_left_color.color.b = 0.7;
    wall_left_color.color.a = 0.4;
    object_colors.push_back(wall_left_color);
    
    // Wall right
    moveit_msgs::msg::CollisionObject wall_right;
    wall_right.header.frame_id = "world";
    wall_right.id = "wall_right";
    
    pose.position.x = hw + CELL_WALL_T / 2;
    
    wall_right.primitives.push_back(primitive);
    wall_right.primitive_poses.push_back(pose);
    wall_right.operation = wall_right.ADD;
    collision_objects.push_back(wall_right);
    
    moveit_msgs::msg::ObjectColor wall_right_color;
    wall_right_color.id = "wall_right";
    wall_right_color.color.r = 0.7;
    wall_right_color.color.g = 0.7;
    wall_right_color.color.b = 0.7;
    wall_right_color.color.a = 0.4;
    object_colors.push_back(wall_right_color);
  }
  
  // ── Ceiling ────────────────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject ceiling;
    ceiling.header.frame_id = "world";
    ceiling.id = "ceiling";
    
    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions = {CELL_WIDTH, CELL_DEPTH, CELL_WALL_T};
    
    geometry_msgs::msg::Pose pose;
    pose.position.x = 0.0;
    pose.position.y = 0.0;
    pose.position.z = FLOOR_Z + CELL_HEIGHT + CELL_WALL_T / 2;
    pose.orientation.w = 1.0;
    
    ceiling.primitives.push_back(primitive);
    ceiling.primitive_poses.push_back(pose);
    ceiling.operation = ceiling.ADD;
    collision_objects.push_back(ceiling);
    
    moveit_msgs::msg::ObjectColor ceiling_color;
    ceiling_color.id = "ceiling";
    ceiling_color.color.r = 0.8;
    ceiling_color.color.g = 0.8;
    ceiling_color.color.b = 0.9;
    ceiling_color.color.a = 0.3;
    object_colors.push_back(ceiling_color);
  }
  
  // ── Welding table ──────────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject table;
    table.header.frame_id = "world";
    table.id = "welding_table";
    
    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions = {2.000, 1.000, 0.100};
    
    geometry_msgs::msg::Pose pose;
    pose.position.x = 0.0;
    pose.position.y = 0.0;
    pose.position.z = RAIL_BASE_Z - RAIL_HEIGHT - TABLE_SIZE_Z / 2;
    pose.orientation.w = 1.0;
    
    table.primitives.push_back(primitive);
    table.primitive_poses.push_back(pose);
    table.operation = table.ADD;
    collision_objects.push_back(table);
    
    moveit_msgs::msg::ObjectColor table_color;
    table_color.id = "welding_table";
    table_color.color.r = 0.3;
    table_color.color.g = 0.3;
    table_color.color.b = 0.35;
    table_color.color.a = 0.9;
    object_colors.push_back(table_color);
  }
  
  // ── No-go zone ─────────────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject no_go;
    no_go.header.frame_id = "world";
    no_go.id = "no_go_zone";
    
    shape_msgs::msg::SolidPrimitive primitive;
    primitive.type = primitive.BOX;
    primitive.dimensions = {2.00, 0.35, 0.13};
    
    geometry_msgs::msg::Pose pose;
    pose.position.x = 0.00;
    pose.position.y = -0.32;
    pose.position.z = _table_surface_z + 0.13 / 2;
    pose.orientation.w = 1.0;
    
    no_go.primitives.push_back(primitive);
    no_go.primitive_poses.push_back(pose);
    no_go.operation = no_go.ADD;
    collision_objects.push_back(no_go);
    
    moveit_msgs::msg::ObjectColor no_go_color;
    no_go_color.id = "no_go_zone";
    no_go_color.color.r = 0.1;
    no_go_color.color.g = 0.6;
    no_go_color.color.b = 0.7;
    no_go_color.color.a = 0.5;
    object_colors.push_back(no_go_color);
  }
  
  // ── Coffee cup (mesh) ──────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject cup;
    cup.header.frame_id = "world";
    cup.id = "object";
    
    shapes::Mesh* mesh = shapes::createMeshFromResource(
        "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/coffee_cup.stl");
    
    if (mesh)
    {
      shape_msgs::msg::Mesh mesh_msg;
      shapes::ShapeMsg mesh_msg_variant;
      shapes::constructMsgFromShape(mesh, mesh_msg_variant);
      mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
      
      geometry_msgs::msg::Pose pose;
      pose.position.x = 0.700;
      pose.position.y = -0.300;
      pose.position.z = _table_surface_z + 0.7;
      pose.orientation.w = 1.0;
      
      cup.meshes.push_back(mesh_msg);
      cup.mesh_poses.push_back(pose);
      cup.operation = cup.ADD;
      collision_objects.push_back(cup);
      
      moveit_msgs::msg::ObjectColor cup_color;
      cup_color.id = "object";
      cup_color.color.r = 0.9;
      cup_color.color.g = 0.7;
      cup_color.color.b = 0.3;
      cup_color.color.a = 1.0;
      object_colors.push_back(cup_color);
      
      delete mesh;
    }
  }
  
  // ── Grinder (mesh) ─────────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject grinder;
    grinder.header.frame_id = "world";
    grinder.id = "grinder";
    
    shapes::Mesh* mesh = shapes::createMeshFromResource(
        "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Coffee Grinder.stl",
        Eigen::Vector3d(0.001, 0.001, 0.001));
    
    if (mesh)
    {
      shape_msgs::msg::Mesh mesh_msg;
      shapes::ShapeMsg mesh_msg_variant;
      shapes::constructMsgFromShape(mesh, mesh_msg_variant);
      mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
      
      geometry_msgs::msg::Pose pose;
      pose.position.x = 0.000;
      pose.position.y = -0.300;
      pose.position.z = 0.010;
      pose.orientation.x = 0.0;
      pose.orientation.y = 0.0;
      pose.orientation.z = 1.0;
      pose.orientation.w = 0.0;
      
      grinder.meshes.push_back(mesh_msg);
      grinder.mesh_poses.push_back(pose);
      grinder.operation = grinder.ADD;
      collision_objects.push_back(grinder);
      
      moveit_msgs::msg::ObjectColor grinder_color;
      grinder_color.id = "grinder";
      grinder_color.color.r = 0.3;
      grinder_color.color.g = 0.8;
      grinder_color.color.b = 0.9;
      grinder_color.color.a = 1.0;
      object_colors.push_back(grinder_color);
      
      delete mesh;
    }
  }
  
  // ── Coffee machine (mesh) ──────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject coffee_machine;
    coffee_machine.header.frame_id = "world";
    coffee_machine.id = "coffee_machine";
    
    shapes::Mesh* mesh = shapes::createMeshFromResource(
        "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeMachine.stl",
        Eigen::Vector3d(0.001, 0.001, 0.001));
    
    if (mesh)
    {
      shape_msgs::msg::Mesh mesh_msg;
      shapes::ShapeMsg mesh_msg_variant;
      shapes::constructMsgFromShape(mesh, mesh_msg_variant);
      mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
      
      geometry_msgs::msg::Pose pose;
      pose.position.x = 0.419;
      pose.position.y = -0.316;
      pose.position.z = 0.010;
      pose.orientation.w = 1.0;
      
      coffee_machine.meshes.push_back(mesh_msg);
      coffee_machine.mesh_poses.push_back(pose);
      coffee_machine.operation = coffee_machine.ADD;
      collision_objects.push_back(coffee_machine);
      
      moveit_msgs::msg::ObjectColor coffee_machine_color;
      coffee_machine_color.id = "coffee_machine";
      coffee_machine_color.color.r = 0.2;
      coffee_machine_color.color.g = 0.6;
      coffee_machine_color.color.b = 0.2;
      coffee_machine_color.color.a = 1.0;
      object_colors.push_back(coffee_machine_color);
      
      delete mesh;
    }
  }
  
  // ── Tool station (mesh) ────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject tool_station;
    tool_station.header.frame_id = "world";
    tool_station.id = "tool_station";
    
    shapes::Mesh* mesh = shapes::createMeshFromResource(
        "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/Tool Station.stl",
        Eigen::Vector3d(0.001, 0.001, 0.001));
    
    if (mesh)
    {
      shape_msgs::msg::Mesh mesh_msg;
      shapes::ShapeMsg mesh_msg_variant;
      shapes::constructMsgFromShape(mesh, mesh_msg_variant);
      mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
      
      geometry_msgs::msg::Pose pose;
      pose.position.x = -0.670;
      pose.position.y = -0.300;
      pose.position.z = 0.210;
      pose.orientation.x = 0.0;
      pose.orientation.y = 0.0;
      pose.orientation.z = 0.7071;
      pose.orientation.w = 0.7071;
      
      tool_station.meshes.push_back(mesh_msg);
      tool_station.mesh_poses.push_back(pose);
      tool_station.operation = tool_station.ADD;
      collision_objects.push_back(tool_station);
      
      moveit_msgs::msg::ObjectColor tool_station_color;
      tool_station_color.id = "tool_station";
      tool_station_color.color.r = 0.7;
      tool_station_color.color.g = 0.1;
      tool_station_color.color.b = 0.8;
      tool_station_color.color.a = 1.0;
      object_colors.push_back(tool_station_color);
      
      delete mesh;
    }
  }
  
  // ── Cup holder (mesh) ──────────────────────────────────────────────────
  {
    moveit_msgs::msg::CollisionObject cup_holder;
    cup_holder.header.frame_id = "world";
    cup_holder.id = "cup_holder";
    
    shapes::Mesh* mesh = shapes::createMeshFromResource(
        "file:///home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_description/meshes/CoffeeCupHolder.stl",
        Eigen::Vector3d(0.001, 0.001, 0.001));
    
    if (mesh)
    {
      shape_msgs::msg::Mesh mesh_msg;
      shapes::ShapeMsg mesh_msg_variant;
      shapes::constructMsgFromShape(mesh, mesh_msg_variant);
      mesh_msg = boost::get<shape_msgs::msg::Mesh>(mesh_msg_variant);
      
      geometry_msgs::msg::Pose pose;
      pose.position.x = -0.469;
      pose.position.y = -0.351;
      pose.position.z = 0.210;
      pose.orientation.x = 0.0;
      pose.orientation.y = 0.0;
      pose.orientation.z = -0.7071;
      pose.orientation.w = 0.7071;
      
      cup_holder.meshes.push_back(mesh_msg);
      cup_holder.mesh_poses.push_back(pose);
      cup_holder.operation = cup_holder.ADD;
      collision_objects.push_back(cup_holder);
      
      moveit_msgs::msg::ObjectColor cup_holder_color;
      cup_holder_color.id = "cup_holder";
      cup_holder_color.color.r = 0.1;
      cup_holder_color.color.g = 0.1;
      cup_holder_color.color.b = 0.1;
      cup_holder_color.color.a = 0.5;
      object_colors.push_back(cup_holder_color);
      
      delete mesh;
    }
  }
  
  // ── Add all objects to planning scene with colors ──────────────────────
  RCLCPP_INFO(LOGGER, "Adding %zu collision objects with colors to planning scene...", collision_objects.size());
  psi.applyCollisionObjects(collision_objects, object_colors);
  
  rclcpp::sleep_for(std::chrono::seconds(1));
  
  RCLCPP_INFO(LOGGER, "Planning scene setup complete!");
}

void SimpleTask::doTask()
{
  setupPlanningScene();
  
  // Task 1: Pick cup holder
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Cup Holder ===");
  task_ = createPickupCupHolderTask();
  task_.init();
  if (!task_.plan(5)) {
    RCLCPP_ERROR(LOGGER, "Pick holder planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick holder execution failed");
    return;
  }
  
  // Task 2: Pick coffee cup
  RCLCPP_INFO(LOGGER, "=== TASK 2: Pick Coffee Cup ===");
  task_ = createPickCupTask();
  task_.init();
  if (!task_.plan(5)) {
    RCLCPP_ERROR(LOGGER, "Pick cup planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick cup execution failed");
    return;
  }
  
  RCLCPP_INFO(LOGGER, "Both tasks completed successfully!");
}


mtc::Task SimpleTask::createPickupCupHolderTask()
{
  // -------------------------------------------------------------------------
  // SETUP: Create task and load robot model
  // -------------------------------------------------------------------------
  
  mtc::Task task;
  task.stages()->setName("pick cup holder");  // Name shown in RViz
  task.loadRobotModel(node_);  // Load URDF/SRDF into task

  task.enableIntrospection(true);
  
  // -------------------------------------------------------------------------
  // CONFIGURATION: Define which parts of the robot we're using
  // -------------------------------------------------------------------------
  
  // Planning group = which joints to move (from SRDF)
  const std::string arm_group_name = "igus_rebel_arm";
  
  // End effector = the female bayonet connector (from SRDF)
  const std::string eef_name = "female_connector_eef";
  
  // Hand frame = the link where we'll attach objects
  const std::string hand_frame = "gripper_link";
  
  // Set default properties for all stages (stages can inherit these)
  task.setProperty("group", arm_group_name);  // Which joints to plan for
  task.setProperty("eef", eef_name);          // Which end effector we're using
  task.setProperty("ik_frame", hand_frame);   // Reference frame for IK
  
  // -------------------------------------------------------------------------
  // PLANNERS: Create motion planners we'll use
  // -------------------------------------------------------------------------
  
  // Sampling planner (RRT) - for free-space motion, can handle complex obstacles
  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);     // Slow = 10% max speed
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1); // Slow = 10% max accel
  
  // Cartesian planner - for straight-line motion in workspace (approach/retreat)
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.02);     // Slow = 10% max speed
  cartesian_planner->setMaxAccelerationScalingFactor(0.02); // Slow = 10% max accel
  cartesian_planner->setStepSize(0.01);  // 1cm steps for collision checking
  
  // -------------------------------------------------------------------------
  // MONITORING: Pointer to capture the initial state
  // -------------------------------------------------------------------------
  
  // We'll save a pointer to CurrentState so later stages can reference it
  // This is for setMonitoredStage() - tells GenerateGraspPose to use
  // object position from THIS state, not from current planning state
  mtc::Stage* current_state_ptr = nullptr;
  
  // ===========================================================================
  // STAGE 1 — Current State (GENERATOR)
  // ===========================================================================
  // Purpose: Capture where the robot is right now
  // Input: Nothing
  // Output: Current robot joint positions + planning scene state
  // This is the starting point for all planning
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();  // Save pointer for later stages to reference
    task.add(std::move(stage));       // Add stage to task
  }
  
  // ===========================================================================
  // STAGE 2 — Move to Tool Station (CONNECTOR)
  // ===========================================================================
  // Purpose: Move arm from current position to near the tool station
  // Input: Current state (from Stage 1)
  // Output: Robot positioned near tool station
  // Plans: Free-space motion using sampling planner
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to tool station",  // Stage name
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    
    stage->setTimeout(5.0);  // Allow up to 5 seconds for planning
    
    // Inherit "group" property from task (so it knows which joints to move)
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    
    task.add(std::move(stage));
  }
  
  // ===========================================================================
  // STAGE 3 — Pick Cup Holder (SERIAL CONTAINER)
  // ===========================================================================
  // Purpose: Group multiple stages into one logical "pick" operation
  // All substages must succeed in order for the pick to succeed
  {
    auto grasp_holder = std::make_unique<mtc::SerialContainer>("pick cup holder");
    
    // Expose task properties to this container
    task.properties().exposeTo(grasp_holder->properties(), { "eef", "group", "ik_frame" });
    
    // Container inherits eef, group, ik_frame from task
    grasp_holder->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

    // ── 3b: Allow Connector/Holder Collision (PROPAGATOR) ───────────────
    // Purpose: Tell planning scene that gripper_link can touch cup_holder
    // Without this, IK will reject poses where connector touches holder
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow connector/holder collision");
      
      // Allow collision between cup_holder and gripper_link
      stage->allowCollisions("cup_holder",                          // Object 1
                            std::vector<std::string>{"gripper_link"}, // Object 2
                            true);                                    // true = allow
                  
      stage->allowCollisions("cup_holder",
                            std::vector<std::string>{"tool_station"},
                            true);
      
      grasp_holder->insert(std::move(stage));
    }
    
    // ── 3a: Approach Cup Holder (PROPAGATOR) ────────────────────────────
    // Purpose: Move closer to cup holder along gripper's Z axis
    // This gets us into position before grasping
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach holder", cartesian_planner);
      
      // Inherit "group" from parent container
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      
      // Move between 5cm and 10cm
      stage->setMinMaxDistance(0.05, 0.10);
      
      // Move relative to gripper_link frame
      stage->setIKFrame(hand_frame);
      
      // Define direction: along gripper's +Z axis
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;  // Direction is in gripper's local frame
      vec.vector.y = -1.0;                // Move along +Z (forward for gripper)
      stage->setDirection(vec);
      
      grasp_holder->insert(std::move(stage));  // Add to container (not task)
    }
    
    
    // ── 3d: Generate Grasp Pose + Compute IK (GENERATOR + CONNECTOR) ────
    // Purpose: Try different approach angles and find which ones are reachable
    // GenerateGraspPose creates multiple possible grasp poses around the object
    // ComputeIK filters out poses the robot can't reach
    {
      // GENERATOR: Creates multiple grasp poses
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate holder grasp");
      
      // Inherit properties from container
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      
      // Namespace for visualization markers in RViz
      stage->properties().set("marker_ns", "holder_grasp");
      
      // Which object to grasp (must match name in planning scene)
      stage->setObject("cup_holder");
      
      // Try grasps every 60 degrees around the object (360/60 = 6 poses)
      stage->setAngleDelta(2 * M_PI);  // π/3 radians = 60 degrees
      
      // Use object pose from current_state_ptr, NOT from current planning state
      // Important because planning state evolves as we plan
      stage->setMonitoredStage(current_state_ptr);
      
      // Define pre-grasp gripper configuration (before closing on object)
      // For parallel-jaw grippers, this would be "fingers open"
      // For bayonet connector with no joints, is_diff=true means "no change"
      moveit_msgs::msg::RobotState pregrasp_state;
      pregrasp_state.is_diff = true;  // true = keep current gripper state
      stage->setPreGraspPose(pregrasp_state);
      
      // Define grasp transform: where gripper should be relative to object center
      Eigen::Isometry3d grasp_transform = Eigen::Isometry3d::Identity();
      
      grasp_transform.translation().y() = -0.01;  // 8cm standoff
      grasp_transform.rotate(Eigen::AngleAxisd(25.02 * M_PI / 180.0, Eigen::Vector3d::UnitY()));
      
      // CONNECTOR: Wrap generator in ComputeIK to filter unreachable poses
      // This takes Cartesian poses → tries to find joint angles → keeps valid ones
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("holder grasp IK", std::move(stage));
      
      // Try up to 8 different IK solutions per grasp pose
      wrapper->setMaxIKSolutions(8);
      
      // Solutions must be at least 1.0 radians different (avoid near-duplicates)
      wrapper->setMinSolutionDistance(1.0);
      
      // Apply the grasp transform to hand_frame
      wrapper->setIKFrame(grasp_transform, hand_frame);
      
      // Inherit eef and group from parent
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      
      // Inherit target_pose from the generator (INTERFACE = from wrapped stage)
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });

      wrapper->setIgnoreCollisions(true);
      
      grasp_holder->insert(std::move(wrapper));
    }

    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("maintain allowed collisions");
      stage->allowCollisions("cup_holder", std::vector<std::string>{"gripper_link"}, true);
      stage->allowCollisions("cup_holder", std::vector<std::string>{"tool_station"}, true);
      grasp_holder->insert(std::move(stage));
    }
    
    // ── 3e: Twist Lock - 60° Joint Rotation (PROPAGATOR) ────────────────
    // Purpose: Rotate joint6 by 60 degrees to engage bayonet lock
    // This is a joint-space motion, not Cartesian
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("twist lock", sampling_planner);
      
      // Inherit group from parent
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      
      // Define joint deltas (how much to rotate each joint)
      std::map<std::string, double> joint_deltas;
      joint_deltas["joint6"] = M_PI / 3.0;  // 60 degrees = π/3 radians
      
      // Set the direction as joint deltas
      stage->setDirection(joint_deltas);
      
      // Allow rotation from 0 to 60 degrees (planner picks optimal distance)
      stage->setMinMaxDistance(0.0, M_PI / 3.0);
      
      grasp_holder->insert(std::move(stage));
    }

    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow holder/tool_station for attach");
      stage->allowCollisions("cup_holder",
                            std::vector<std::string>{"tool_station"},
                            true);
      grasp_holder->insert(std::move(stage));
    }
    
    // ── 3f: Attach Cup Holder (PROPAGATOR) ──────────────────────────────
    // Purpose: Make cup_holder part of the robot kinematic chain
    // After this, cup_holder moves rigidly with hand_frame
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup holder");
      
      // Attach "cup_holder" object to "gripper_link" frame
      // Now when gripper moves, cup holder moves with it
      stage->attachObject("cup_holder", hand_frame);
      
      grasp_holder->insert(std::move(stage));
    }
    
    // ── 3g: Retreat from Tool Station (PROPAGATOR) ──────────────────────
    // Purpose: Back away from tool station after picking holder
    // Cartesian motion away from tool station
    {
       auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
      
       // Inherit group
       stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      
       // Move between 5cm and 10cm
       stage->setMinMaxDistance(0.05, 0.10);
      
       // Move relative to gripper frame
       stage->setIKFrame(hand_frame);
      
       // Define direction: along gripper's -Z axis (backward)
       geometry_msgs::msg::Vector3Stamped vec;
       vec.header.frame_id = hand_frame;
       vec.vector.x = 1.0;  // Negative = backward
       stage->setDirection(vec);
      
       grasp_holder->insert(std::move(stage));
    }
    
    // Add the entire container to the task
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

  // Planning group = which joints to move (from SRDF)
  const std::string arm_group_name = "igus_rebel_arm";
  
  // End effector = the female bayonet connector (from SRDF)
  const std::string eef_name = "female_connector_eef";
  
  // Hand frame = the link where we'll attach objects
  const std::string hand_frame = "gripper_link";
  
  // Set default properties for all stages (stages can inherit these)
  task.setProperty("group", arm_group_name);  // Which joints to plan for
  task.setProperty("eef", eef_name);          // Which end effector we're using
  task.setProperty("ik_frame", hand_frame);   // Reference frame for IK
  
  // Sampling planner (RRT) - for free-space motion, can handle complex obstacles
  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);     // Slow = 10% max speed
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1); // Slow = 10% max accel
  
  // Cartesian planner - for straight-line motion in workspace (approach/retreat)
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.1);     // Slow = 10% max speed
  cartesian_planner->setMaxAccelerationScalingFactor(0.1); // Slow = 10% max accel
  cartesian_planner->setStepSize(0.01);  // 1cm steps for collision checking
  
  mtc::Stage* current_state_ptr = nullptr;

  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();  // Save pointer for later stages to reference
    task.add(std::move(stage));       // Add stage to task
  }

  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to cup",  // Stage name
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    
    stage->setTimeout(5.0);  // Allow up to 5 seconds for planning
    
    // Inherit "group" property from task (so it knows which joints to move)
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    
    task.add(std::move(stage));
  }

  // Pick cup container
  {
    auto grasp = std::make_unique<mtc::SerialContainer>("pick coffee cup");
    task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" });
    grasp->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });
    
    // Allow collisions
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow cup collision");
      stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
      stage->allowCollisions("object", std::vector<std::string>{"cup_holder"}, true);
      grasp->insert(std::move(stage));
    }
    
    // Approach
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach cup", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.001, 0.10);
      stage->setIKFrame(hand_frame);
      
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.z = 1.0;  // Approach from above (assuming Z is up)
      stage->setDirection(vec);
      
      grasp->insert(std::move(stage));
    }
    
    // Generate grasp pose + IK
    {
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate cup grasp");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "cup_grasp");
      stage->setObject("object");  // This is your coffee cup
      stage->setAngleDelta(M_PI / 6);  // Try every 30 degrees
      stage->setMonitoredStage(current_state_ptr);
      
      moveit_msgs::msg::RobotState pregrasp_state;
      pregrasp_state.is_diff = true;
      stage->setPreGraspPose(pregrasp_state);
      
      Eigen::Isometry3d grasp_transform = Eigen::Isometry3d::Identity();
      grasp_transform.translation().y() = -0.13;  // Grasp from top, 5cm offset
      grasp_transform.rotate(Eigen::AngleAxisd(90 * M_PI / 180.0, Eigen::Vector3d::UnitY()));
      
      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("cup grasp IK", std::move(stage));
      wrapper->setMaxIKSolutions(8);
      wrapper->setMinSolutionDistance(1.0);
      wrapper->setIKFrame(grasp_transform, hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      
      grasp->insert(std::move(wrapper));
    }

    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("lift cup", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.07, 0.09);
      stage->setIKFrame(hand_frame);
      
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;  // Lift up in world frame
      stage->setDirection(vec);
      
      grasp->insert(std::move(stage));
    }
    
    // Attach cup
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach cup");
      stage->attachObject("object", hand_frame);
      grasp->insert(std::move(stage));
    }
    
    // Lift
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("lift cup", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.10);
      stage->setIKFrame(hand_frame);
      
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;  // Lift up in world frame
      stage->setDirection(vec);
      
      grasp->insert(std::move(stage));
    }
    
    task.add(std::move(grasp));
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

  auto spin_thread = std::make_unique<std::thread>([&executor, &simple_task_node]() {
    executor.add_node(simple_task_node->getNodeBaseInterface());
    executor.spin();
    executor.remove_node(simple_task_node->getNodeBaseInterface());
  });

  simple_task_node->doTask();

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}