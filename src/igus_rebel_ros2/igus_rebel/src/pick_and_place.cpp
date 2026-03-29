#include <rclcpp/rclcpp.hpp>
#include <moveit_msgs/msg/robot_state.hpp>
#include <moveit_msgs/msg/constraints.hpp>
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

moveit_msgs::msg::Constraints makeUprightConstraint(const std::string& link_name)
{
  moveit_msgs::msg::Constraints constraints;
  moveit_msgs::msg::OrientationConstraint oc;
  oc.header.frame_id = "world";
  oc.link_name = link_name;
  oc.orientation.w = 1.0;
  oc.absolute_x_axis_tolerance = 1.0;
  oc.absolute_y_axis_tolerance = 1.0;
  oc.absolute_z_axis_tolerance = M_PI;
  oc.weight = 1.0;
  constraints.orientation_constraints.push_back(oc);
  return constraints;
}

class MTCTaskNode
{
public:
  MTCTaskNode(const rclcpp::NodeOptions& options);
  rclcpp::node_interfaces::NodeBaseInterface::SharedPtr getNodeBaseInterface();
  void doTask();

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

void MTCTaskNode::doTask()
{
  task_ = createTask();
  task_.enableIntrospection();

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

  for (const auto& sol : task_.solutions())
  {
    task_.introspection().publishSolution(*sol);
  }

  rclcpp::sleep_for(std::chrono::seconds(10));

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
  const auto& hand_eef_name  = "vacuum_eef";
  const auto& hand_frame     = "gripper_link";

  task.setProperty("group",    arm_group_name);
  task.setProperty("eef",      hand_eef_name);
  task.setProperty("ik_frame", hand_frame);

  // Links allowed to touch the object during grasp/carry
  auto all_links = std::vector<std::string>{
      "motor4", "motor5", "link4", "link5", "link6", "gripper_link"
  };

  // ---------------------------------------------------------------------------
  // Grasp transform  (U-cradle, scoop-from-below strategy)
  // ---------------------------------------------------------------------------
  auto makeGraspTransform = []() {
    Eigen::Isometry3d t = Eigen::Isometry3d::Identity();
    t.linear() = (Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitY()) *
                  Eigen::AngleAxisd(M_PI / 2.0, Eigen::Vector3d::UnitX()))
                     .toRotationMatrix();
    t.translation().z() = 0.11;  // standoff — tune to your hardware
    return t;
  };

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  mtc::Stage* current_state_ptr    = nullptr;
  mtc::Stage* attach_object_stage  = nullptr;
#pragma GCC diagnostic pop

  // ---------------------------------------------------------------------------
  // Planners
  // ---------------------------------------------------------------------------
  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor",     0.05);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.05);

  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(0.01);

  // ===========================================================================
  // STAGE 1 — Current state
  // ===========================================================================
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }

  // ===========================================================================
  // STAGE 2 — Allow rail / front-wall collision (permanent for whole task)
  // ===========================================================================
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow rail/wall collision");
    stage->allowCollisions("wall_front", "igus_7th_axis", true);
    task.add(std::move(stage));
  }

  // ===========================================================================
  // STAGE 3 — Connect to pick
  // ===========================================================================
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to pick",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // ===========================================================================
  // STAGE 4 — Pick serial container
  // ===========================================================================
  {
    auto grasp = std::make_unique<mtc::SerialContainer>("pick object");
    task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" });
    grasp->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

    // ── 4a: Approach along gripper Z ────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach object", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.01, 0.05);
      stage->setIKFrame(hand_frame);
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }

    // ── 4b: Scoop upward in world Z ─────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("scoop under cup", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.03, 0.10);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "scoop_approach");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }

    // ── 4c: Allow gripper_link <-> object collision BEFORE IK ───────────────
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow gripper/object collision");
      stage->allowCollisions("object", std::vector<std::string>{"gripper_link"}, true);
      grasp->insert(std::move(stage));  // into grasp container, not task
    }

    // ── 4d: Generate grasp pose + ComputeIK ─────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "grasp_pose");

      moveit_msgs::msg::RobotState pregrasp_state;
      pregrasp_state.is_diff = true;
      stage->setPreGraspPose(pregrasp_state);

      stage->setObject("object");
      stage->setAngleDelta(M_PI / 6);  // 30° steps
      stage->setMonitoredStage(current_state_ptr);

      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp pose IK", std::move(stage));
      wrapper->setMaxIKSolutions(16);
      wrapper->setMinSolutionDistance(0.5);
      wrapper->setIKFrame(makeGraspTransform(), hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT,    { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      wrapper->setIgnoreCollisions(false);  // gripper/object already allowed above
      grasp->insert(std::move(wrapper));
    }

    // ── 4e: Allow all arm links <-> object (for carry) ──────────────────────
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow collision (cradle,object)");
      stage->allowCollisions("object",
          task.getRobotModel()
              ->getJointModelGroup(arm_group_name)
              ->getLinkModelNamesWithCollisionGeometry(),
          true);
      stage->allowCollisions(std::vector<std::string>{"object"}, all_links, true);
      grasp->insert(std::move(stage));
    }

    // ── 4f: Attach object ───────────────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach object");
      stage->attachObject("object", hand_frame);
      attach_object_stage = stage.get();
      grasp->insert(std::move(stage));
    }

    // ── 4g: Lift straight up ────────────────────────────────────────────────
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
  }

  // ===========================================================================
  // STAGE 5 — Connect to place
  // ===========================================================================
  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to place",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }

  // ===========================================================================
  // STAGE 6 — Place serial container
  // ===========================================================================
  {
    auto place = std::make_unique<mtc::SerialContainer>("place object");
    task.properties().exposeTo(place->properties(), { "eef", "group", "ik_frame" });
    place->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });

    // ── 6a: Approach place (move down) ──────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach place", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.01, 0.10);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "approach_place");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = -1.0;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    // ── 6b: Generate place pose + ComputeIK ─────────────────────────────────
    {
      geometry_msgs::msg::PoseStamped place_pose;
      place_pose.header.frame_id = "world";
      place_pose.pose.position.x =  0.1;
      place_pose.pose.position.y = -0.3;
      place_pose.pose.position.z =  0.5;   // adjust to your desired drop height
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
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT,    { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      wrapper->setIgnoreCollisions(true);
      place->insert(std::move(wrapper));
    }

    // ── 6c: Lower cup onto surface ──────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("lower cup", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.03, 0.10);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "lower_cup");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = -1.0;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    // ── 6d: Detach object ───────────────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach object");
      stage->detachObject("object", hand_frame);
      place->insert(std::move(stage));
    }

    // ── 6e: Retreat down slightly ───────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.02, 0.05);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "retreat");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = -0.02;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    // ── 6f: Move backward in X ──────────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("backward", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.15);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "backward");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.x = 1.0;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    // ── 6g: Post-place lift ──────────────────────────────────────────────────
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("post-place lift", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.15);
      stage->setIKFrame(hand_frame);
      stage->properties().set("marker_ns", "post_place_lift");
      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;
      stage->setDirection(vec);
      place->insert(std::move(stage));
    }

    task.add(std::move(place));
  }

  // ===========================================================================
  // STAGE 7 — Return home
  // ===========================================================================
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

  mtc_task_node->doTask();

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}