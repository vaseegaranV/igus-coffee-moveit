from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder

def generate_launch_description():
    moveit_config = (
        MoveItConfigsBuilder("igus_rebel")
        .robot_description_semantic(file_path="config/igus_rebel2.srdf")
        .planning_pipelines(pipelines=["ompl", "pilz_industrial_motion_planner"])
        .to_dict()
    )

    ompl_fix = {
        "ompl": {
            "planning_plugins": ["ompl_interface/OMPLPlanner"],
            "request_adapters": [
                "default_planning_request_adapters/ResolveConstraintFrames",
                "default_planning_request_adapters/ValidateWorkspaceBounds",
                "default_planning_request_adapters/CheckStartStateBounds",
                "default_planning_request_adapters/CheckStartStateCollision",
            ],
            "response_adapters": [
                "default_planning_response_adapters/AddTimeOptimalParameterization",
                "default_planning_response_adapters/ValidateSolution",
                "default_planning_response_adapters/DisplayMotionPath",
            ],
        }
    }

    pick_place_demo = Node(
        package='igus_rebel',
        executable='pick_and_place',
        output="screen",
        parameters=[
            moveit_config,
            ompl_fix,
            {'use_sim_time': True},
        ],
    )

    return LaunchDescription([pick_place_demo])