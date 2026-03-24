#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <random>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("random_pose_node");

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.automatically_declare_parameters_from_overrides(true);
  auto node = std::make_shared<rclcpp::Node>("random_pose_node", options);

  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(node);
  auto spinner = std::thread([&executor]() { executor.spin(); });

  // Create MoveGroupInterface for the arm
  moveit::planning_interface::MoveGroupInterface move_group(node, "igus_rebel_arm");
  move_group.setMaxVelocityScalingFactor(0.1);
  move_group.setMaxAccelerationScalingFactor(0.1);
  move_group.setPlanningTime(5.0);

  // Get the robot's workspace bounds
  // Adjust these to match your robot's reachable workspace
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> x_dist(0.2, 0.3);
  std::uniform_real_distribution<double> y_dist(-0.2, 0.2);
  std::uniform_real_distribution<double> z_dist(0.2, 0.4);

  int num_poses = 2;  // number of random poses to visit

  for (int i = 0; i < num_poses; i++)
  {
    RCLCPP_INFO(LOGGER, "Moving to random pose %d/%d", i + 1, num_poses);

    geometry_msgs::msg::Pose target_pose;
    target_pose.position.x = x_dist(gen);
    target_pose.position.y = y_dist(gen);
    target_pose.position.z = z_dist(gen);

    // Keep orientation pointing downward
    target_pose.orientation.x = 0.0;
    target_pose.orientation.y = 0.707;
    target_pose.orientation.z = 0.0;
    target_pose.orientation.w = 0.707;

    move_group.setPoseTarget(target_pose);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    bool success = (move_group.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);

    if (success)
    {
      RCLCPP_INFO(LOGGER, "Plan found, executing...");
      move_group.execute(plan);
    }
    else
    {
      RCLCPP_WARN(LOGGER, "Planning failed for this pose, skipping...");
    }

    rclcpp::sleep_for(std::chrono::seconds(1));
  }

  RCLCPP_INFO(LOGGER, "Done! Returning to home...");
  move_group.setNamedTarget("home");
  move_group.move();

  executor.cancel();
  spinner.join();
  rclcpp::shutdown();
  return 0;
}