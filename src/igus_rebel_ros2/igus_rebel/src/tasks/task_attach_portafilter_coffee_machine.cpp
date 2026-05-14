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
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.2);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.2);


  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.2);
  cartesian_planner->setMaxAccelerationScalingFactor(0.2);
  cartesian_planner->setStepSize(0.01);


  mtc::Stage* current_state_ptr = nullptr;


  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }


  {
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to coffee machine",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(5.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }


  {
    auto grasp = std::make_unique<mtc::SerialContainer>("attach portafilter");
    task.properties().exposeTo(grasp->properties(), { "eef", "group", "ik_frame" });
    grasp->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group", "ik_frame" });


    // Allow collisions with coffee machine during approach
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow machine collisions");
      auto all_links = task.getRobotModel()->getLinkModelNamesWithCollisionGeometry();
      stage->allowCollisions("coffee_machine", all_links, true);
      stage->allowCollisions("portafilter", std::vector<std::string>{"coffee_machine"}, true);
      stage->allowCollisions("portafilter", std::vector<std::string>{"gripper_link"}, true);
      grasp->insert(std::move(stage));
    }


    // Approach portafilter along -Y axis in world frame
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("approach portafilter", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.15);
      stage->setIKFrame(hand_frame);


      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = hand_frame;
      vec.vector.y = -1.0;
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }


    // Generate grasp pose — same transform as createAttachPortafilterFromGrinder
    {
      auto stage = std::make_unique<mtc::stages::GenerateGraspPose>("generate grasp pose");
      stage->properties().configureInitFrom(mtc::Stage::PARENT);
      stage->properties().set("marker_ns", "portafilter_grasp");
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


      auto wrapper = std::make_unique<mtc::stages::ComputeIK>("grasp IK", std::move(stage));
      wrapper->setMaxIKSolutions(8);
      wrapper->setMinSolutionDistance(1.0);
      wrapper->setIKFrame(grasp_transform, hand_frame);
      wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
      wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
      wrapper->setIgnoreCollisions(true);
      grasp->insert(std::move(wrapper));
    }


    // Allow machine collision before attaching
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow machine for attach");
      stage->allowCollisions("portafilter", std::vector<std::string>{"coffee_machine"}, true);
      grasp->insert(std::move(stage));
    }


    // // Twist lock: rotate joint6 by 60° to engage bayonet
    // {
    //   auto stage = std::make_unique<mtc::stages::MoveRelative>("twist lock", sampling_planner);
    //   stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    //   std::map<std::string, double> joint_deltas;
    //   joint_deltas["joint6"] = M_PI / 3.0;
    //   stage->setDirection(joint_deltas);
    //   stage->setMinMaxDistance(0.0, M_PI / 3.0);
    //   grasp->insert(std::move(stage));
    // }


    // Attach portafilter to gripper
    {
      auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("attach portafilter");
      stage->attachObject("portafilter", hand_frame);
      grasp->insert(std::move(stage));
    }


// Retreat along +Y (out of machine) then up
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.05, 0.20);
      stage->setIKFrame(hand_frame);


      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.y = 1.0;  // pull out of machine in +Y
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }


    // Lift up clear of machine
    {
      auto stage = std::make_unique<mtc::stages::MoveRelative>("lift clear", cartesian_planner);
      stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
      stage->setMinMaxDistance(0.10, 0.25);
      stage->setIKFrame(hand_frame);


      geometry_msgs::msg::Vector3Stamped vec;
      vec.header.frame_id = "world";
      vec.vector.z = 1.0;  // lift up
      stage->setDirection(vec);
      grasp->insert(std::move(stage));
    }


    task.add(std::move(grasp));
  }


  return task;
}
