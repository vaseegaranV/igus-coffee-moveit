cmake_minimum_required(VERSION 3.8)
project(igus_rebel)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(igus_rebel_msgs REQUIRED)
find_package(geometry_msgs)
find_package(moveit_ros_planning_interface)
find_package(moveit_task_constructor_core REQUIRED)

find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)

# Include directories
include_directories(
  include
  /opt/ros/jazzy/include/
  /home/COAR-ROS2-WORKSPACE/install/igus_rebel_msgs/include/igus_rebel_msgs/
)

# Add hardware interface shared library
add_library(${PROJECT_NAME} SHARED
  src/Rebel.cpp
  src/RebelSocket.cpp
  src/CriMessages.cpp
)

add_executable(igus_moveit src/igus_moveit.cpp)
add_executable(igus_rail_moveit src/igus_rail_moveit.cpp)

# FIXED: Both .cpp files are part of ONE executable
add_executable(main 
  src/main.cpp
  src/tasks/task_attach_portafilter_grinder.cpp
  src/tasks/task_clean_portafilter.cpp
  src/tasks/task_detach_portafilter_grinder.cpp
  src/tasks/task_dispose_portafilter_bin.cpp
  src/tasks/task_go_home.cpp
  src/tasks/task_insert_cup_coffee_machine.cpp
  src/tasks/task_insert_portafilter_grinder.cpp
  src/tasks/task_pick_cup_coffee_machine.cpp
  src/tasks/task_pick_cup_holder.cpp
  src/tasks/task_pick_cup.cpp
  src/tasks/task_pick_portafilter.cpp
  src/tasks/task_place_cup_delivery_station.cpp
  src/tasks/task_place_cup_holder.cpp
  src/tasks/task_place_portafilter.cpp
  src/tasks/task_press_grinder.cpp
  src/tasks/task_press_left_coffee_machine.cpp
  src/tasks/task_press_middle_coffee_machine.cpp
  src/tasks/task_tamp_portafilter.cpp
  src/tasks/task_insert_portafilter_coffee_machine.cpp
  src/tasks/task_attach_portafilter_coffee_machine.cpp
  src/setup_environment.cpp
)

add_executable(random_pose_node src/random_poses.cpp)


target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC)

# Add library dependencies
ament_target_dependencies(${PROJECT_NAME}
  pluginlib hardware_interface igus_rebel_msgs geometry_msgs moveit_ros_planning_interface rclcpp
)

ament_target_dependencies(igus_moveit geometry_msgs moveit_ros_planning_interface rclcpp igus_rebel_msgs)
ament_target_dependencies(igus_rail_moveit geometry_msgs moveit_ros_planning_interface rclcpp igus_rebel_msgs)
ament_target_dependencies(main geometry_msgs moveit_ros_planning_interface rclcpp igus_rebel_msgs moveit_task_constructor_core)
# REMOVED: setup_environment line - it's now part of main
ament_target_dependencies(random_pose_node rclcpp moveit_ros_planning_interface)

pluginlib_export_plugin_description_file(hardware_interface rebel.xml)

# Install the shared library
install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# FIXED: Removed setup_environment from install
install(TARGETS 
    igus_moveit
    igus_rail_moveit
    main
    random_pose_node
    DESTINATION lib/${PROJECT_NAME}) 

# Install the plugin description xml file
install(FILES
  rebel.xml
  DESTINATION share/${PROJECT_NAME}
)

# Install package folders
install(DIRECTORY
  config
  launch
  # rviz
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()