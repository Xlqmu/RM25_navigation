import os
from launch import LaunchDescription
from launch_ros.actions import Node

def lidar_sim_start():
    return LaunchDescription([
        Node(
            package='rm_robot_description_sim',
            executable='mid360_lidar_sim',
            name='mid360_lidar_sim',
            output='screen',
            parameters=[
                {'lidar_topic': 'scan'},
                {'lidar_frame': 'mid360_link'},
                {'lidar_file': os.path.join(os.path.expanduser(''), 'rm_simulation_ws', 'src', 'rm_robot_description_sim', 'config', 'mid360', 'mid360_lidar.yaml')}
            ]
        )
    ])