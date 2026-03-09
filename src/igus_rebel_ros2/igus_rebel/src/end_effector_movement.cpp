#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include "igus_rebel_msgs/srv/set_digital_output.hpp"

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    options.parameter_overrides({{"use_sim_time", rclcpp::ParameterValue(true)}});
    auto node_ = std::make_shared<rclcpp::Node>("EndEffectorMovementNode", options);

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node_);
    std::thread spin_thread([&executor]() { executor.spin(); });

    const std::string PLANNING_GROUP = "igus_rebel_arm";
    moveit::planning_interface::MoveGroupInterface move_group(node_, PLANNING_GROUP);
    moveit::planning_interface::MoveGroupInterface gripper(node_, "gripper");

    rclcpp::sleep_for(std::chrono::seconds(1));

    auto current_pose = move_group.getCurrentJointValues();
    RCLCPP_INFO(node_->get_logger(), "Current Joint 2 Position: %.4f", current_pose[2]);

    std::vector<geometry_msgs::msg::Pose> poses(5);

    poses[0].position.x = 0.1;
    poses[0].position.y = 0.0;
    poses[0].position.z = 0.4;
    poses[0].orientation.w = 1.0;

    poses[1].position.x = 0.2;
    poses[1].position.y = 0.2;
    poses[1].position.z = 0.3;
    poses[1].orientation.w = 1.0;

    poses[2].position.x = 0.1;
    poses[2].position.y = -0.2;
    poses[2].position.z = 0.5;
    poses[2].orientation.w = 1.0;

    poses[3].position.x = 0.4;
    poses[3].position.y = 0.1;
    poses[3].position.z = 0.2;
    poses[3].orientation.w = 1.0;

    poses[4].position.x = 0.3;
    poses[4].position.y = -0.1;
    poses[4].position.z = 0.35;
    poses[4].orientation.w = 1.0;

    int wait_times[] = {10, 10, 5, 5, 5};
    bool gripper_open = true;  // alternates open/close each pose

    while (rclcpp::ok()){
        for (int i = 0; i < 5; i++){

            // Open or close gripper
            if (gripper_open){
                RCLCPP_INFO(node_->get_logger(), "Opening gripper");
                gripper.setNamedTarget("open");
            } else {
                RCLCPP_INFO(node_->get_logger(), "Closing gripper");
                gripper.setNamedTarget("closed");
            }
            gripper.move();
            gripper_open = !gripper_open;  // alternate next time

            rclcpp::sleep_for(std::chrono::seconds(wait_times[i]));
        }
    }

    rclcpp::shutdown();
    spin_thread.join();
    return 0;
}