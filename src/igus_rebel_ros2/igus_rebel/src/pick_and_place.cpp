#include <rclcpp/rclcpp.hpp>
#include <moveit_msgs/msg/robot_state.hpp>
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

  // Coffee cup approximated as a cylinder
  // Adjust these to match your real cup:
  //   dimensions[0] = height (m)
  //   dimensions[1] = radius (m)
  object.primitives[0].type = shape_msgs::msg::SolidPrimitive::CYLINDER;
  object.primitives[0].dimensions = { 0.12, 0.04 };  // 12cm tall, 4cm radius

  geometry_msgs::msg::Pose pose;
  pose.position.x = 0.7;
  pose.position.y = -0.3;
  // z = half the cylinder height so it sits on the floor plane
  pose.position.z = 0.06;
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
  const auto& hand_eef_name = "vacuum_eef";
  const auto& hand_frame = "gripper_link";

  task.setProperty("group", arm_group_name);
  task.setProperty("eef", hand_eef_name);
  task.setProperty("ik_frame", hand_frame);

  // Links that are allowed to be near/touching the object during grasp
  auto all_links = std::vector<std::string>{
      "motor4", "motor5", "link4", "link5", "link6",
      "gripper_link" };

  // ---------------------------------------------------------------------------
  // Grasp transform for the passive U-cradle gripper
  //
  // The cradle has no open/close action. The strategy is:
  //   1. Position the U-cradle below and to the side of the cup base
  //   2. Move upward (world Z) so the cradle scoops under the cup
  //   3. Continue lifting to pick
  //
  // Transform breakdown:
  //   - UnitY rotation (pi/2):  points gripper_link Z axis horizontally toward cup
  //   - UnitX rotation (pi/2):  rotates cradle opening to face upward (scooping orientation)
  //   - Z translation:          standoff from gripper_link origin to cup centre
  //                             = gripper_mount depth + cup radius clearance
  //                             Tune this value to match your hardware.
  // ---------------------------------------------------------------------------
  auto makeGraspTransform = []() {
    Eigen::Isometry3d t = Eigen::Isometry3d::Identity();
    t.linear() = (Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitY()) *
                  Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitX()))
                     .toRotationMatrix();
    // Adjust this offset to place the cradle correctly under the cup base.
    // Current value: 53mm gripper mount + ~40mm to cup centreline.
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

  // Stage 2: Connect to pick
  auto stage_move_to_pick = std::make_unique<mtc::stages::Connect>(
      "move to pick",
      mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
  stage_move_to_pick->setTimeout(5.0);
  stage_move_to_pick->properties().configureInitFrom(mtc::Stage::PARENT);
  task.add(std::move(stage_move_to_pick));

  // Stage 3: Pick serial container
  auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
  task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" });
  grasp->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });

    stage->setMinMaxDistance(0.01, 0.05);  // THIS controls pre-grasp distance
    stage->setIKFrame(hand_frame);

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = hand_frame;

    vec.vector.z = 1.0;  // move forward along gripper

    stage->setDirection(vec);
    grasp->insert(std::move(stage));
  }

  // Stage 3a: Scoop approach — move upward in world Z to slide cradle under cup
  // The arm positions the cradle slightly below the cup base, then lifts here.
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("scoop under cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.03, 0.10);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "scoop_approach");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";  // world Z = straight up
    vec.vector.z = 1.0;
    stage->setDirection(vec);
    grasp->insert(std::move(stage));
  }

  // Stage 3b: Generate grasp pose + ComputeIK
  {
    auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->properties().set("marker_ns", "grasp_pose");

    // GenerateGraspPose validates pregrasp against the eef group (vacuum_gripper),
    // which has zero joints. Pass a completely empty diff state — no joint names,
    // no positions — just is_diff=true to satisfy the validator.
    moveit_msgs::msg::RobotState pregrasp_state;
    pregrasp_state.is_diff = true;
    stage->setPreGraspPose(pregrasp_state);

    stage->setObject("object");

    // U-cradle has one valid approach orientation (opening must face the cup).
    // Sample a full rotation so MTC can find the one feasible IK solution,
    // but ComputeIK's minSolutionDistance will prune near-duplicates.
    stage->setAngleDelta(M_PI / 6);  // 30° steps — coarser is fine for a fixed-shape cradle

    stage->setMonitoredStage(current_state_ptr);

    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(16);
    wrapper->setMinSolutionDistance(0.5);
    wrapper->setIKFrame(makeGraspTransform(), hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(false);
    grasp->insert(std::move(wrapper));
  }

  // Stage 3c: Allow collision between cradle and cup
  // The cup rests inside the U-cradle during the entire lift, so collision must be allowed.
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (cradle,object)");
    stage->allowCollisions("object",
        task.getRobotModel()->getJointModelGroup(arm_group_name)->getLinkModelNamesWithCollisionGeometry(),
        true);
    stage->allowCollisions(std::vector<std::string>{"object"}, all_links, true);
    grasp->insert(std::move(stage));
  }

  // Stage 3d: Attach object to gripper_link
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
    stage->attachObject("object", hand_frame);
    attach_object_stage = stage.get();
    grasp->insert(std::move(stage));
  }

  // Stage 3e: Lift object straight up in world Z
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

  // Stage 4: Connect to place
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to place",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // Stage 5: Place serial container
  auto place = std::make_unique<mtc::SerialContainer>("place object");
  task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" });
  place->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

  // Stage 5a: Generate place pose + ComputeIK
  {
    geometry_msgs::msg::PoseStamped place_pose;
    place_pose.header.frame_id = "world";
    place_pose.pose.position.x = 0.1;
    place_pose.pose.position.y = -0.3;
    // z = half cup height so it rests on the surface
    place_pose.pose.position.z = 0.06;
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

  // Stage 5b: Lower cup onto surface — move down in world Z
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lower cup", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.03, 0.10);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "lower_cup");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;  // move down to set cup on surface
    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  // Stage 5c: Detach object
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
    stage->detachObject("object", hand_frame);
    place->insert(std::move(stage));
  }

  // Stage 5d: Retreat — slide cradle out from under the cup by moving away horizontally
  // The cradle must slide out sideways (world X or Y), not straight up,
  // otherwise it would knock the cup over.
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "retreat");
    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    // Retreat in -X (away from the place position).
    // Change to Y or adjust sign depending on your scene layout.
    vec.vector.z = -0.05;
    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("backward", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "backward");

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.x = -1.0;

    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("post-place lift", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.15);
    stage->setIKFrame(hand_frame);
    stage->properties().set("marker_ns", "post_place_lift");

    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;  // lift UP

    stage->setDirection(vec);
    place->insert(std::move(stage));
  }

  task.add(std::move(place));

  // Stage 6: Return to home
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