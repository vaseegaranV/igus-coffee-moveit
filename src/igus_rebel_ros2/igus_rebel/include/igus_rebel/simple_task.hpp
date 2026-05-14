#ifndef SIMPLE_TASK_HPP
#define SIMPLE_TASK_HPP

#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/task_constructor/solvers.h>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <moveit_msgs/msg/robot_state.hpp>
#include <Eigen/Geometry>

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
  mtc::Task createPickupPortafilter();
  mtc::Task createPickCupTask();
  mtc::Task createMoveToCoffeeMachine();
  mtc::Task createPlaceCupHolderTask();
  mtc::Task createPlacePortafilter();
  mtc::Task createGoHomeTask();
  mtc::Task createMoveToDeliveryStation();
  mtc::Task createPressMiddleButtonTask();
  mtc::Task createPressLeftButtonTask();
  mtc::Task createInsertPortafilterToGrinder();
  mtc::Task createDetachPortafilterFromGrinder();
  mtc::Task createAttachPortafilterFromGrinder();
  mtc::Task createCleanBrush();
  mtc::Task createBinDispose();
  mtc::Task createPickCupFromMachineTask();
  mtc::Task createPressGrinderPowerButtonTask();
  mtc::Task createTampPortafilterTask();
  mtc::Task createInsertPortafilterToCoffeeMachine();
  mtc::Task createAttachPortafilterFromCoffeeMachine();
  mtc::Task task_;
  rclcpp::Node::SharedPtr node_;
};

#endif