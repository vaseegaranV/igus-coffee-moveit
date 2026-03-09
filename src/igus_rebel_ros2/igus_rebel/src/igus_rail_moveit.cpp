#include <rclcpp/rclcpp.hpp>
// #include "moveit_ros_planning_interface/moveit/move_group_interface/move_group_interface.hpp"
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "igus_rebel_msgs/srv/set_digital_output.hpp"
#include "std_msgs/msg/int16.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

using SetDigitalOutput = igus_rebel_msgs::srv::SetDigitalOutput;

std::shared_ptr<rclcpp::Node> node_;
rclcpp::Client<SetDigitalOutput>::SharedPtr client;
std::shared_ptr<SetDigitalOutput::Request> request;
rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr trigger_subscriber;
rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber;

std::mutex trigger_mutex;
bool trigger_flag = false;
bool laser_flag = false;
bool only_once = true;

void send_digital_output(int output_number, bool state)
{
    request->output.output = output_number;
    request->output.is_on = state;

    while ((!client->wait_for_service(std::chrono::seconds(1)) && rclcpp::ok()))
    {
        RCLCPP_INFO(node_->get_logger(), "Waiting for service...");
    }

    auto future = client->async_send_request(request,
        [](rclcpp::Client<SetDigitalOutput>::SharedFuture result) {
            if (result.get()->success) {
                RCLCPP_INFO(node_->get_logger(), "Service call succeeded.");
            } else {
                RCLCPP_ERROR(node_->get_logger(), "Service call failed.");
            }
        }
    );
}

void run_output_sequence()
{
    std::lock_guard<std::mutex> lock(trigger_mutex);
    if (!trigger_flag) return; // Do nothing if not triggered

    try
    {
        // DOut24 ON → 10s → OFF
        RCLCPP_INFO(node_->get_logger(), "Moving left");
        send_digital_output(23, true);
        rclcpp::sleep_for(std::chrono::seconds(25));
        send_digital_output(23, false);

        // DOut25 ON → 200ms → OFF → 10s
        RCLCPP_INFO(node_->get_logger(), "Moving right");
        send_digital_output(24, true);
        rclcpp::sleep_for(std::chrono::milliseconds(200));
        send_digital_output(24, false);

    }
    catch(const std::exception& e)
    {
        send_digital_output(23, false);
        RCLCPP_ERROR(node_->get_logger(), "Exception: %s", e.what());
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    options.parameter_overrides({{"use_sim_time", rclcpp::ParameterValue(true)}});
    node_ = std::make_shared<rclcpp::Node>("IgusRailMoveitNode", options);

    // Create service client and request object
    client = node_->create_client<SetDigitalOutput>("set_digital_output");
    request = std::make_shared<SetDigitalOutput::Request>();

    // Initialize the rail
    // RCLCPP_INFO(node_->get_logger(), "Disable DOUT22");
    // send_digital_output(22, false);

    // RCLCPP_INFO(node_->get_logger(), "Disable DOUT21");
    // send_digital_output(21, false);

    joint_state_subscriber = node_->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states_with_rail", 10,
        [](sensor_msgs::msg::JointState::SharedPtr msg) {

            if (only_once) {

                // Initialize the rail
                RCLCPP_INFO(node_->get_logger(), "Disable DOUT22");
                send_digital_output(22, false);

                RCLCPP_INFO(node_->get_logger(), "Disable DOUT21");
                send_digital_output(21, false);

                RCLCPP_INFO(node_->get_logger(), "Disable DOUT23");
                send_digital_output(23, false);

                // Referencing the rail
                RCLCPP_INFO(node_->get_logger(), "Referencing the rail");
                send_digital_output(24, true);
                rclcpp::sleep_for(std::chrono::milliseconds(200));
                send_digital_output(24, false);
                rclcpp::sleep_for(std::chrono::seconds(10));
                RCLCPP_INFO(node_->get_logger(), "Referencing DONE");
                only_once = false;

            }

            // Process joint state data if needed
            if (msg->position[0] < 0.0205)
            {
                laser_flag = true;
                trigger_flag = false;
            }
            else
            {
                laser_flag = false;
                trigger_flag = true;
            }
        }
    );

    // Subscription to trigger topic
    trigger_subscriber = node_->create_subscription<std_msgs::msg::Int16>(
        "/laser_trigger", 10,
        [](std_msgs::msg::Int16::SharedPtr msg) {
            if (msg->data == 1) {
                if (!trigger_flag) {
                    RCLCPP_INFO(node_->get_logger(), "Trigger received: starting output sequence");
                    std::lock_guard<std::mutex> lock(trigger_mutex);
                    trigger_flag = true;

                    // Run the output sequence in a separate thread so it doesn't block the callback
                    std::thread(run_output_sequence).detach();
                }
            }
        }
    );

    // Spin the node
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node_);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
