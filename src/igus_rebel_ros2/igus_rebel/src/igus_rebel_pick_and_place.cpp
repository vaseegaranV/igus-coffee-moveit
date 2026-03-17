#include <rclcpp/rclcpp.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/stages/compute_ik.h>
#include <moveit/task_constructor/stages/modify_planning_scene.h>
#include <moveit/task_constructor/stages/connect.h>
#include <moveit/task_constructor/stages/move_relative.h>
#include <moveit/task_constructor/stages/generate_grasp_pose.h>
#include <moveit/task_constructor/stages/generate_place_pose.h>
#if __has_include(<tf2_geometry_msgs/tf2_geometry_msgs.hpp>)
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#else
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#endif
#if __has_include(<tf2_eigen/tf2_eigen.hpp>)
#include <tf2_eigen/tf2_eigen.hpp>
#else
#include <tf2_eigen/tf2_eigen.h>
#endif

static const rclcpp::Logger LOGGER = rclcpp::get_logger("mtc_igus");
namespace mtc = moveit::task_constructor;

class MTCTaskNode
{
public:
  MTCTaskNode(const rclcpp::NodeOptions& options);
  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();
  void doTask();
  void setupPlanningScene();

private:
  mtc::Task createTask();
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
};

MTCTaskNode::MTCTaskNode(const rclcpp::NodeOptions& options)
  : node_{ std::make_shared<rclcpp::Node>("mtc_node", options) }
{
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr MTCTaskNode::getNodeBaseInterface()
{
  return node_->get_node_base_interface();
}

void MTCTaskNode::setupPlanningScene()
{
  moveit_msgs::msg::CollisionObject object;
  object.id = "object";
  object.header.frame_id = "world";
  object.primitives.resize(1);
  object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  object.primitives[0].dimensions = { 0.1, 0.02 };

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.3;
  pose.position.y = -0.3;
  pose.position.z = 0.07;
  pose.orientation.w = 1.0;
  object.pose = pose;

  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(object);
}

void MTCTaskNode::doTask()
{
  task_ = createTask();

  try
  {
    task_.init();
  }
  catch (mtc::InitStageException& e)
  {
    RCLCPP_ERROR_STREAM(LOGGER, e);
    return;
  }

  if (!task_.plan(5))
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());

  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS)
  {
    RCLCPP_ERROR_STREAM(LOGGER, "Task execution failed");
    return;
  }
}

mtc::Task MTCTaskNode::createTask()
{
  mtc::Task task;
  task.stages()->setName("demo task");
  task.loadRobotModel(node_);

  const auto& arm_group_name = "igus_rebel_arm";
  const auto& hand_group_name = "gripper";
  const auto& hand_eef_name = "gripper_eef";
  const auto& hand_frame = "link6";

  task.setProperty("group", arm_group_name);
  task.setProperty("eef", hand_eef_name);
  task.setProperty("ik_frame", hand_frame);

  auto all_links = std::vector<std::string>{
      "motor4", "motor5", "link4", "link5", "link6",
      "gripper_mount", "left_finger", "right_finger"};

  // Gripper approach transform:
  // - Y rotation: approach from the side
  // - X rotation: correct EEF orientation so fingers span the cylinder
  // - Z offset: accounts for gripper_mount (0.053) + finger contact point (0.04)
  auto makeGraspTransform = []() {
    Eigen::Isometry3d t = Eigen::Isometry3d::Identity();
    t.linear() = (Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitY()) *
                  Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitX()))
                     .toRotationMatrix();
    t.translation().z() = 0.093;
    return t;
  };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  mtc::Stage* current_state_ptr = nullptr;
  mtc::Stage* attach_object_stage = nullptr;
#pragma GCC diagnostic pop

  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.05);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.05);
  auto interpolation_planner = std::make_shared<mtc::solvers::JointInterpolationPlanner>();
  interpolation_planner->setMaxVelocityScalingFactor(0.1);
  interpolation_planner->setMaxAccelerationScalingFactor(0.1);
  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(.01);
  

  // ---------------------------------------------------------------
  // PICK
  // ---------------------------------------------------------------

  // Stage 1: Current state
  auto stage_state_current = std::make_unique<mtc::stages::CurrentState>("current");
  current_state_ptr = stage_state_current.get();
  task.add(std::move(stage_state_current));

  // Stage 2: Open gripper
  auto stage_open_hand = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
  stage_open_hand->setGroup(hand_group_name);
  stage_open_hand->setGoal("open");
  task.add(std::move(stage_open_hand));

  // Stage 3: Connect to pick
  auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>(
      "move to pick",
      mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
  stage_move_to_pick->setTimeout(5.0);
  stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage_move_to_pick));

  // Stage 4: Pick serial container
  auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
  task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" });
  grasp->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

  // Stage 4a: Approach object (Cartesian move toward grasp pose from standoff)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "approach_object");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;  // move along gripper's own Z axis
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    grasp->insert(std::move(stage));
  }

  // Stage 4b: Generate grasp pose + ComputeIK
  {
    auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "grasp_pose");
    stage->setPreGraspPose("open");
    stage->setObject("object");
    stage->setAngleDelta(M_PI / 12);
    stage->setMonitoredStage(current_state_ptr);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(16);
    wrapper->setMinSolutionDistance(0.5);
    wrapper->setIKFrame(makeGraspTransform(), hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(false);  // gripper must be outside object at grasp pose
    grasp->insert(std::move(wrapper));
  }

  // Stage 4c: Allow collision between hand/arm and object
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (hand,object)");
    stage->allowCollisions("object",
        task.getRobotModel()->getJointModelGroup(hand_group_name)->getLinkModelNamesWithCollisionGeometry(),
        true);
    stage->allowCollisions("object",
        task.getRobotModel()->getJointModelGroup(arm_group_name)->getLinkModelNamesWithCollisionGeometry(),
        true);
    stage->allowCollisions(std::vector<std::string>{"object"}, all_links, true);
    grasp->insert(std::move(stage));
  }

  // Stage 4d: Close gripper
  {
    auto stage = std::make_unique<mtc::stages::MoveTo>("close hand", interpolation_planner);
    stage->setGroup(hand_group_name);
    stage->setGoal("closed");
    grasp->insert(std::move(stage));
  }

  // Stage 4e: Attach object
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
    stage->attachObject("object", hand_frame);
    attach_object_stage = stage.get();
    grasp->insert(std::move(stage));
  }

  // Stage 4f: Lift object
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lift object", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "lift_object");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    grasp->insert(std::move(stage));
  }

  task.add(std::move(grasp));

  // ---------------------------------------------------------------
  // PLACE
  // ---------------------------------------------------------------

  // Stage 5: Connect to place
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to place",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Stage 6: Place serial container
  auto place = std::make_unique<mtc::SerialContainer>("place object");
  task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" });
  place->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

  // Stage 6a: Generate place pose + ComputeIK
  {
    geometry_msgs::msg::PoseStamped place_pose;
    place_pose.header.frame_id = "world";
    place_pose.pose.position.x = 0.1;
    place_pose.pose.position.y = -0.3;
    place_pose.pose.position.z = 0.07;
    place_pose.pose.orientation.w = 1.0;

    auto stage = std::make_unique<mtc::stages::GeneratePlacePose>("generate place pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "place_pose");
    stage->setObject("object");
    stage->setPose(place_pose);
    stage->setMonitoredStage(attach_object_stage);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("place pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(16);
    wrapper->setMinSolutionDistance(0.5);
    wrapper->setIKFrame(makeGraspTransform(), hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);
    place->insert(std::move(wrapper));
  }

  // Stage 6b: Approach place position (Cartesian move in along gripper Z)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach place", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "approach_place");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  // Stage 6c: Open gripper to release object
  {
    auto stage = std::make_unique<mtc::stages::MoveTo>("open hand", interpolation_planner);
    stage->setGroup(hand_group_name);
    stage->setGoal("open");
    place->insert(std::move(stage));
  }

  // Stage 6d: Detach object
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
    stage->detachObject("object", hand_frame);
    place->insert(std::move(stage));
  }

  // Stage 6e: Retreat after placing
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "retreat");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  task.add(std::move(place));

  // Stage 7: Return to home
  {
    auto stage = std::make_unique<mtc::stages::MoveTo>("return home", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setGroup(arm_group_name);
    stage->setGoal("home");
    task.add(std::move(stage));
  }

  return task;
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.automatically_declare_parameters_from_overrides(true);

  auto mtc_task_node = std::make_shared<MTCTaskNode>(options);
  rclcpp::executors::MultiThreadedExecutor executor;

  auto spin_thread = std::make_unique<std::thread>([&executor, &mtc_task_node]() {
    executor.add_node(mtc_task_node->getNodeBaseInterface());
    executor.spin();
    executor.remove_node(mtc_task_node->getNodeBaseInterface());
  });

  mtc_task_node->setupPlanningScene();
  mtc_task_node->doTask();

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}