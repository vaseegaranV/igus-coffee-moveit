from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, Command, FindExecutable
from launch_ros.substitutions import FindPackageShare
from launch.actions import ExecuteProcess

import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Declare launch arguments
    debug_arg = DeclareLaunchArgument(
        'debug', default_value='false', description='Enable debugging')
    
    hardware_protocol_arg = DeclareLaunchArgument(
        "hardware_protocol",
        default_value="gazebo",  # Using Gazebo for physics simulation
        choices=["mock_hardware", "gazebo", "rebel"],
        description="Which hardware protocol or mock hardware should be used")
    
    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time', 
        default_value='true',  # True because we're using Gazebo
        description='Use sim time if true')
    
    use_gui_arg = DeclareLaunchArgument(
        'use_gui', default_value='true', description='')
    
    gazebo_gui_arg = DeclareLaunchArgument(
        'gazebo_gui', 
        default_value='false',  # Hide Gazebo GUI by default
        description='Show Gazebo GUI window')
    
    paused_arg = DeclareLaunchArgument(
        'paused', default_value='false', description='Start Gazebo paused')
    
    # Get launch configurations
    hardware_protocol = LaunchConfiguration('hardware_protocol')
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_gui = LaunchConfiguration('use_gui')
    
    # Robot description
    robot_description_file = os.path.join(
        get_package_share_directory('igus_rebel_description'),
        'urdf1',
        'igus_rebel_robot.urdf.xacro'
    )

    robot_description = Command(
        [
            FindExecutable(name="xacro"),
            " ",
            robot_description_file,
            " hardware_protocol:=",
            hardware_protocol,
        ]
    )

    # Launch Gazebo (GUI hidden by default)
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('igus_rebel_moveit_config'), 
                        'launch', 'gazebo.launch.py')
        ),
    )

    # Robot state publisher
    robot_state_pub_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{
            'robot_description': robot_description,
            'use_sim_time': use_sim_time
        }],
        output="both",
    )

    # MoveIt move_group
    moveit_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('igus_rebel_moveit_config'), 
                        'launch', 'move_group.launch.py')
        ),
        launch_arguments={
            'hardware_protocol': hardware_protocol,
            'use_sim_time': use_sim_time,
            'use_gui': use_gui,
        }.items(),
    )

    # RViz2
    default_rviz_file = os.path.join(
        get_package_share_directory('igus_rebel_moveit_config'),
        'launch',
        'moveit.rviz'
    )
    
    rviz_arg = DeclareLaunchArgument(
        'rviz_config', 
        default_value=default_rviz_file, 
        description='Path to RViz config file')
    
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output='screen',
        parameters=[{
            "use_sim_time": use_sim_time,
        }],
        arguments=["--display-config", LaunchConfiguration('rviz_config')]
    )

    # coffee_cell_env_process = ExecuteProcess(
    #     cmd=['python3', '/home/vasee22/igus-coffee-moveit/src/igus_rebel_ros2/igus_rebel_moveit_config/launch/coffee_cell_environment.py'],
    #     output='screen'
    # )

    return LaunchDescription([
        debug_arg,
        hardware_protocol_arg,
        use_sim_time_arg,
        use_gui_arg,
        gazebo_gui_arg,
        paused_arg,
        rviz_arg,
        gazebo_launch,           # Gazebo runs (hidden GUI)
        robot_state_pub_node,    # Publishes TF
        moveit_launch,           # MoveIt planning
        rviz_node,               # Visualization
        #coffee_cell_env_process,
    ])