#include "igus_rebel/simple_task.hpp"
#include <rclcpp/rclcpp.hpp>
#include <moveit/task_constructor/task.h>
#include <moveit/task_constructor/solvers.h>
#include <moveit/task_constructor/stages.h>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <geometric_shapes/shapes.h>
#include <geometric_shapes/shape_operations.h>
#include <geometric_shapes/mesh_operations.h>
#include <moveit/collision_detection/collision_matrix.hpp>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("simple_moveto");
namespace mtc = moveit::task_constructor;

SimpleTask::SimpleTask(const rclcpp::NodeOptions& options)
  : node_{ std::make_shared<rclcpp::Node>("simple_moveto_node", options) }
{
}

rclcpp::node_interfaces::NodeBaseInterface::SharedPtr SimpleTask::getNodeBaseInterface()
{
  return node_->get_node_base_interface();
}

void SimpleTask::doTask()
{
  // Set up the planning scene with all collision objects
  setupPlanningScene();

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createPressLeftButtonTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  auto result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Portafilter ===");
  task_ = createPickupPortafilter();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Portafilter ===");
  task_ = createGoHomeTask();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Insert Portafilter ===");
  task_ = createInsertPortafilterToGrinder();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createDetachPortafilterFromGrinder();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createPressGrinderPowerButtonTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createAttachPortafilterFromGrinder();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createTampPortafilterTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Portafilter ===");
  task_ = createInsertPortafilterToCoffeeMachine();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Cup Holder ===");
  task_ = createPickupCupHolderTask();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick holder planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick holder execution failed");
    return;
  }
  
  // Execute Task 2: Pick up the coffee cup (with cup holder attached)
  RCLCPP_INFO(LOGGER, "=== TASK 2: Pick Coffee Cup ===");
  task_ = createPickCupTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Pick cup planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick cup execution failed");
    return;
  }


  RCLCPP_INFO(LOGGER, "=== TASK 3: Place Coffee Cup ===");
  task_ = createMoveToCoffeeMachine();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "move to coffee machine planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "move to coffee machine execution failed");
    return;
  }

  // Execute Task after place coffee cup in Coffee Machine
  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button ===");
  task_ = createPressMiddleButtonTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press button execution failed");
    return;
  }

  // Execute Task after place coffee cup in Coffee Machine
  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button ===");
  task_ = createPickCupFromMachineTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press button execution failed");
    return;
  }


  RCLCPP_INFO(LOGGER, "=== TASK 1: Insert Portafilter ===");
  task_ = createMoveToDeliveryStation();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK 4: Place Cup Holder ===");
  task_ = createPlaceCupHolderTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "place cup holder failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "place cup holder failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createPressLeftButtonTask();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Pick Portafilter ===");
  task_ = createAttachPortafilterFromGrinder();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK 1: Insert Portafilter ===");
  task_ = createBinDispose();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }

  RCLCPP_INFO(LOGGER, "=== TASK X: Press Left Button (Off) ===");
  task_ = createCleanBrush();
  task_.init();
  if (!task_.plan(20)) {
    RCLCPP_ERROR(LOGGER, "Press left button planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Press left button execution failed");
    return;
  }

  // Execute Task 1: Pick up the cup holder from tool station
  RCLCPP_INFO(LOGGER, "=== TASK 1: Place Portafilter ===");
  task_ = createPlacePortafilter();
  task_.init();
  if (!task_.plan(10)) {
    RCLCPP_ERROR(LOGGER, "Place portafilter planning failed");
    return;
  }
  task_.introspection().publishSolution(*task_.solutions().front());
  result = task_.execute(*task_.solutions().front());
  if (result.val != moveit_msgs::msg::MoveItErrorCodes::SUCCESS) {
    RCLCPP_ERROR(LOGGER, "Pick portafilter execution failed");
    return;
  }
  
  RCLCPP_INFO(LOGGER, "All tasks completed successfully!");
}


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions options;
  options.automatically_declare_parameters_from_overrides(true);

  auto simple_task_node = std::make_shared<SimpleTask>(options);
  rclcpp::executors::MultiThreadedExecutor executor;

  // Spin executor in separate thread to handle callbacks
  auto spin_thread = std::make_unique<std::thread>([&executor, &simple_task_node]() {
    executor.add_node(simple_task_node->getNodeBaseInterface());
    executor.spin();
    executor.remove_node(simple_task_node->getNodeBaseInterface());
  });

  // Execute the task sequence
  simple_task_node->doTask();

  spin_thread->join();
  rclcpp::shutdown();
  return 0;
}