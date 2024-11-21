from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os

def generate_launch_description():
    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join('/home/aurora/RM25/src/rm_robot_description/launch', 'rm_simulation.launch.py')
            )
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join('/home/aurora/RM25/src/rm_driver/livox_ros_driver2/launch_ROS2', 'rviz_MID360_launch.py')
            )
        )
    ])