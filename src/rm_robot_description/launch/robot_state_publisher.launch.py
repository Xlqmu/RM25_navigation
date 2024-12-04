from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, Command
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    bringup_dir = get_package_share_directory('rm_robot_description')

    # 指定 xacro 路径
    default_robot_description = Command(['xacro ', os.path.join(bringup_dir, 'urdf', 'simulation_waking_robot.xacro')])

    return LaunchDescription([
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            parameters=[{
                'use_sim_time': LaunchConfiguration('use_sim_time'),
                'robot_description': default_robot_description
            }],
            output='screen'
        ),
    ])