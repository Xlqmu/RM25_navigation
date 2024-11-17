import os
import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo
from launch_ros.actions import Node
import xacro

def generate_launch_description():
    # Get the path to the XACRO file
    xacro_file = os.path.join(
        os.path.dirname(__file__), '..', 'urdf', 'robot.urdf.xacro')
    
    # Process the XACRO file and generate the URDF content
    robot_description = xacro.process_file(xacro_file).toxml()

    return LaunchDescription([
        DeclareLaunchArgument('robot_description', default_value=robot_description, description='Robot Description'),
        
        # Start the robot_state_publisher node with the generated robot_description
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            parameters=[{'robot_description': robot_description}]
        ),
    ])
