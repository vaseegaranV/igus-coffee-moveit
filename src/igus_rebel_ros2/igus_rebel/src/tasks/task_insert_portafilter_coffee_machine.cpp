#include "igus_rebel/simple_task.hpp"

mtc::Task SimpleTask::createInsertPortafilterToCoffeeMachine()
{
  mtc::Task task;
  task.stages()->setName("insert portafilter to coffee machine");
  task.loadRobotModel(node_);
  task.enableIntrospection(true);


  const std::string arm_group_name = "igus_rebel_arm";
  const std::string eef_name       = "female_connector_eef";
  const std::string hand_frame     = "gripper_link";


  task.setProperty("group", arm_group_name);
  task.setProperty("eef", eef_name);
  task.setProperty("ik_frame", hand_frame);


  // Group head position — TUNE these
  const double INSERT_X = -0.326;
  const double INSERT_Y = -0.070;  // in front of machine
  const double INSERT_Z =  0.140;  // group head height


  auto sampling_planner = std::make_shared<mtc::solvers::PipelinePlanner>(node_);
  sampling_planner->setProperty("max_velocity_scaling_factor", 0.1);
  sampling_planner->setProperty("max_acceleration_scaling_factor", 0.1);


  auto cartesian_planner = std::make_shared<mtc::solvers::CartesianPath>();
  cartesian_planner->setMaxVelocityScalingFactor(0.05);
  cartesian_planner->setMaxAccelerationScalingFactor(0.05);
  cartesian_planner->setStepSize(0.005);


  mtc::Stage* current_state_ptr = nullptr;


  // Stage 1: Current state
  {
    auto stage = std::make_unique<mtc::stages::CurrentState>("current");
    current_state_ptr = stage.get();
    task.add(std::move(stage));
  }


  // Stage 2: Allow collisions
  mtc::Stage* allow_collisions_ptr = nullptr;
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("allow insertion collisions");
    auto all_links = task.getRobotModel()->getLinkModelNamesWithCollisionGeometry();


    stage->allowCollisions("coffee_machine", all_links, true);
    stage->allowCollisions("no_go_zone",     all_links, true);
    stage->allowCollisions("portafilter", std::vector<std::string>{"coffee_machine"}, true);
    stage->allowCollisions("portafilter", std::vector<std::string>{"gripper_link"},   true);
    stage->allowCollisions("portafilter", std::vector<std::string>{"no_go_zone"},     true);
    stage->allowCollisions("link4", std::vector<std::string>{"link5"}, true);
    stage->allowCollisions("tamping_station", std::vector<std::string>{"gripper_link"}, true);


    allow_collisions_ptr = stage.get();
    task.add(std::move(stage));
  }


// Stage 3: Move to hover pose using Cartesian planner — keeps portafilter level
{
    auto stage = std::make_unique<mtc::stages::Connect>(
        "move to hover above group head",
        mtc::stages::Connect::GroupPlannerVector{ { arm_group_name, sampling_planner } });
    stage->setTimeout(20.0);
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    task.add(std::move(stage));
  }


  // Stage 4: Generate hover pose above group head — same pattern as cup placement
  {
    auto stage = std::make_unique<mtc::stages::GeneratePose>("generate hover pose");
    stage->properties().configureInitFrom(mtc::Stage::PARENT);
    stage->setMonitoredStage(allow_collisions_ptr);


    geometry_msgs::msg::PoseStamped target;
    target.header.frame_id = "world";
    target.pose.position.x = INSERT_X;
    target.pose.position.y = INSERT_Y;
    target.pose.position.z = INSERT_Z + 0.50;  // 20cm above group head
    target.pose.orientation.x = 0.0;
    target.pose.orientation.y = -0.7071;
    target.pose.orientation.z = 0.0;
    target.pose.orientation.w = 0.7071;
    stage->setPose(target);


    auto wrapper = std::make_unique<mtc::stages::ComputeIK>("hover pose IK", std::move(stage));
    wrapper->setMaxIKSolutions(32);
    wrapper->setMinSolutionDistance(1.0);
    wrapper->setIKFrame(hand_frame);
    wrapper->properties().configureInitFrom(mtc::Stage::PARENT, { "eef", "group" });
    wrapper->properties().configureInitFrom(mtc::Stage::INTERFACE, { "target_pose" });
    wrapper->setIgnoreCollisions(true);
    task.add(std::move(wrapper));
  }


  // Stage 5: Lower down to group head height (Cartesian -Z)
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("lower to group head", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.44, 0.54);
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = -1.0;
    stage->setDirection(vec);
    task.add(std::move(stage));
  }


  // Stage 6: Insert — push portafilter into group head in -Y
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("insert portafilter", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.12);
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = -1.0;
    stage->setDirection(vec);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("rotate gripper", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });

    geometry_msgs::msg::TwistStamped twist;
    twist.header.frame_id = "world";
    twist.twist.angular.y = 1.0;  // rotate about world Y
    stage->setDirection(twist);
    stage->setMinMaxDistance(4.0 * M_PI / 180.0, 4.0 * M_PI / 180.0);  // exactly 10°

    task.add(std::move(stage));
  }


// Stage 7: Push up into group head seat
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("push up into seat", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.08, 0.08);  // tune push distance
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.z = 1.0;  // push up
    stage->setDirection(vec);
    task.add(std::move(stage));
  }




// // Stage 8: Bayonet twist — rotate handle 90° around portafilter long axis (world Y)
//   {
//     auto stage = std::make_unique<mtc::stages::MoveRelative>("twist lock", cartesian_planner);
//     stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });


//     geometry_msgs::msg::TwistStamped twist;
//     twist.header.frame_id = "world";
//     twist.twist.angular.y = -1.0;  // try 1.0 if wrong direction
//     stage->setDirection(twist);
//     stage->setMinMaxDistance(M_PI / 2.0, M_PI / 2.0);


//     task.add(std::move(stage));
//   }


// Stage 9: Detach portafilter — locked into machine
  {
    auto stage = std::make_unique<mtc::stages::ModifyPlanningScene>("detach portafilter");
    stage->detachObject("portafilter", hand_frame);
    task.add(std::move(stage));
  }

  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("twist unlock", sampling_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });

    std::map<std::string, double> joint_deltas;
    joint_deltas["joint6"] = M_PI / 3.0;  // reverse of twist lock
    stage->setDirection(joint_deltas);
    stage->setMinMaxDistance(0.0, M_PI / 3.0);

    task.add(std::move(stage));
  }

  // Stage 10: Retreat — pull back in +Y
  {
    auto stage = std::make_unique<mtc::stages::MoveRelative>("retreat from machine", cartesian_planner);
    stage->properties().configureInitFrom(mtc::Stage::PARENT, { "group" });
    stage->setMinMaxDistance(0.05, 0.20);
    stage->setIKFrame(hand_frame);


    geometry_msgs::msg::Vector3Stamped vec;
    vec.header.frame_id = "world";
    vec.vector.y = 1.0;
    stage->setDirection(vec);
    task.add(std::move(stage));
  }


  return task;
}
