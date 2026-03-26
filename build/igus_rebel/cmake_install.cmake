# Install script for directory: /home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/igus_rebel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel/rebel.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/libigus_rebel.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so"
         OLD_RPATH "/home/vasee22/ws_moveit/install/moveit_ros_planning/lib:/home/vasee22/ws_moveit/install/moveit_core/lib:/home/vasee22/ws_moveit/install/moveit_msgs/lib:/opt/ros/jazzy/lib:/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/igus_rebel_msgs/lib:/home/vasee22/ws_moveit/install/moveit_ros_planning_interface/lib:/home/vasee22/ws_moveit/install/moveit_ros_move_group/lib:/home/vasee22/ws_moveit/install/moveit_ros_warehouse/lib:/home/vasee22/ws_moveit/install/moveit_ros_occupancy_map_monitor/lib:/opt/ros/jazzy/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libigus_rebel.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igus_rebel" TYPE EXECUTABLE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/igus_moveit")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit"
         OLD_RPATH "/home/vasee22/ws_moveit/install/moveit_ros_planning_interface/lib:/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/igus_rebel_msgs/lib:/home/vasee22/ws_moveit/install/moveit_ros_move_group/lib:/home/vasee22/ws_moveit/install/moveit_ros_planning/lib:/home/vasee22/ws_moveit/install/moveit_core/lib:/home/vasee22/ws_moveit/install/moveit_msgs/lib:/opt/ros/jazzy/lib:/home/vasee22/ws_moveit/install/moveit_ros_warehouse/lib:/home/vasee22/ws_moveit/install/moveit_ros_occupancy_map_monitor/lib:/opt/ros/jazzy/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_moveit")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/CMakeFiles/igus_moveit.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igus_rebel" TYPE EXECUTABLE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/igus_rail_moveit")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit"
         OLD_RPATH "/home/vasee22/ws_moveit/install/moveit_ros_planning_interface/lib:/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/igus_rebel_msgs/lib:/home/vasee22/ws_moveit/install/moveit_ros_move_group/lib:/home/vasee22/ws_moveit/install/moveit_ros_planning/lib:/home/vasee22/ws_moveit/install/moveit_core/lib:/home/vasee22/ws_moveit/install/moveit_msgs/lib:/opt/ros/jazzy/lib:/home/vasee22/ws_moveit/install/moveit_ros_warehouse/lib:/home/vasee22/ws_moveit/install/moveit_ros_occupancy_map_monitor/lib:/opt/ros/jazzy/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/igus_rail_moveit")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/CMakeFiles/igus_rail_moveit.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/igus_rebel" TYPE EXECUTABLE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/pick_and_place")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place"
         OLD_RPATH "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/install/igus_rebel_msgs/lib:/home/vasee22/ws_moveit/install/moveit_task_constructor_core/lib:/home/vasee22/ws_moveit/install/moveit_ros_planning_interface/lib:/home/vasee22/ws_moveit/install/moveit_ros_move_group/lib:/home/vasee22/ws_moveit/install/moveit_ros_planning/lib:/home/vasee22/ws_moveit/install/moveit_core/lib:/home/vasee22/ws_moveit/install/moveit_msgs/lib:/opt/ros/jazzy/lib:/home/vasee22/ws_moveit/install/moveit_ros_warehouse/lib:/home/vasee22/ws_moveit/install/rviz_marker_tools/lib:/home/vasee22/ws_moveit/install/moveit_ros_occupancy_map_monitor/lib:/opt/ros/jazzy/lib/x86_64-linux-gnu:/home/vasee22/ws_moveit/install/moveit_task_constructor_msgs/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/igus_rebel/pick_and_place")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/CMakeFiles/pick_and_place.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel/rebel.xml")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/" TYPE DIRECTORY FILES
    "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel/config"
    "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel/launch"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/igus_rebel")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/igus_rebel")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/environment" TYPE FILE FILES "/opt/ros/jazzy/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/environment" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/environment" TYPE FILE FILES "/opt/ros/jazzy/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/environment" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/path.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/local_setup.bash")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/local_setup.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_environment_hooks/package.dsv")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_index/share/ament_index/resource_index/packages/igus_rebel")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/hardware_interface__pluginlib__plugin" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_index/share/ament_index/resource_index/hardware_interface__pluginlib__plugin/igus_rebel")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel/cmake" TYPE FILE FILES
    "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_core/igus_rebelConfig.cmake"
    "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/ament_cmake_core/igus_rebelConfig-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/igus_rebel" TYPE FILE FILES "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/src/igus_rebel_ros2/igus_rebel/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/vasee22/COAR-ROS2-Workspace-mai/COAR-ROS2-Workspace-main/build/igus_rebel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
