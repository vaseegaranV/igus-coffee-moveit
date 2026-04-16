#ifndef SIMPLE_TASK_HPP
#define SIMPLE_TASK_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>

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

#endif