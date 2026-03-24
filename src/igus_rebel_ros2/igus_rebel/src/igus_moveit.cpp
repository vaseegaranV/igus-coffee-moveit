#include <rclcpp/rclcpp.hpp>
#include "moveit_ros_planning_interface/moveit/move_group_interface/move_group_interface.hpp"
#include <geometry_msgs/geometry_msgs/msg/pose_stamped.hpp>
#include "igus_rebel_msgs/srv/set_digital_output.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    options.parameter_overrides({{"use_sim_time", rclcpp::ParameterValue(true)}});
    auto node_ = std::make_shared<rclcpp::Node>("IgusMoveitNode", options);

    // Digital output ros-service
    auto client = node_->create_client<igus_rebel_msgs::srv::SetDigitalOutput>("set_digital_output");
    auto request = std::make_shared<igus_rebel_msgs::srv::SetDigitalOutput::Request>();

    // rclcpp::executors::SingleThreadedExecutor executor;
    // executor.add_node(node_);

    // std::thread spin_thread([&executor]() { executor.spin(); });

    const std::string PLANNING_GROUP = "igus_rebel_arm";
    moveit::planning_interface::MoveGroupInterface move_group(node_,PLANNING_GROUP);

    // Ensure MoveIt has received the latest state before proceeding
    rclcpp::sleep_for(std::chrono::seconds(1));

    auto current_pose = move_group.getCurrentJointValues();
    RCLCPP_INFO(node_->get_logger(), "Current Joint 2 Position: %.4f", current_pose[2]);

    double joint_vals_1[] = {0.1, 0.00523599, -0.7033677, 1.7645279, -0.109956, 1.478294, -0.171042};
    double joint_vals_2[] = {0.2, -1.492257, -0.7033677, 1.7645279, 0.00349066, 1.254892, -0.171042};
    double joint_vals_3[] = {0.2, -1.492257, -0.2059489, 1.7645279, 0.00349066, 1.50971, -0.171042};
    double joint_vals_4[] = {0.2, -1.492257, -0.00872665, 2.14675, 0.00523599, 0.9320058, -0.174533};
    double joint_vals_5[] = {0.2, -1.492257, -0.2059489, 1.7645279, 0.00349066, 1.50971, -0.171042};
    
    // --------------------------------------------------MAIN PROGRAM ---------------------------------------------------------------
    while (rclcpp::ok())
    {
        // ---------------- Executing Joint_vals_1 -----------------
        for(int i=0; i<7; i++)
        {
            current_pose[i] = joint_vals_1[i];
        }

        // Set new joint target
        move_group.setJointValueTarget(current_pose);

        // Plan and execute the motion
        move_group.move();

        // Ensure MoveIt has received the latest state before proceeding
        rclcpp::sleep_for(std::chrono::seconds(10));

        // ---------------- Executing Joint_vals_2 -----------------
        for(int i=0; i<7; i++)
        {
            current_pose[i] = joint_vals_2[i];
        }

        // Set new joint target
        move_group.setJointValueTarget(current_pose);

        // Plan and execute the motion
        move_group.move();

        // Ensure MoveIt has received the latest state before proceeding
        rclcpp::sleep_for(std::chrono::seconds(10));

        // ---------------- Executing Joint_vals_3 -----------------
        for(int i=0; i<7; i++)
        {
            current_pose[i] = joint_vals_3[i];
        }

        // Set new joint target
        move_group.setJointValueTarget(current_pose);

        // Plan and execute the motion
        move_group.move();

        // Ensure MoveIt has received the latest state before proceeding
        rclcpp::sleep_for(std::chrono::seconds(5));

        // ---------------- Executing Joint_vals_4 -----------------
        for(int i=0; i<7; i++)
        {
            current_pose[i] = joint_vals_4[i];
        }

        // Set new joint target
        move_group.setJointValueTarget(current_pose);

        // Plan and execute the motion
        move_group.move();

        // Ensure MoveIt has received the latest state before proceeding
        rclcpp::sleep_for(std::chrono::seconds(5));

        // ---------------- Executing Joint_vals_5 -----------------
        for(int i=0; i<7; i++)
        {
            current_pose[i] = joint_vals_5[i];
        }

        // Set new joint target
        move_group.setJointValueTarget(current_pose);

        // Plan and execute the motion
        move_group.move();

        // Ensure MoveIt has received the latest state before proceeding
        rclcpp::sleep_for(std::chrono::seconds(5));
    }

    rclcpp::shutdown();
    // spin_thread.join();
    return 0;
}