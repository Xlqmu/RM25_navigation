import os
from ament_index_python.packages import get_package_share_directory
import launch
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue

def generate_launch_description():
    # 获取默认模型路径
    default_model_path = os.path.join(get_package_share_directory('rm_robot_description'), 'urdf', 'four_omniwheel_robot.urdf')
    default_rviz_config_path = os.path.join(get_package_share_directory('rm_robot_description'), 'rviz', 'rviz2.rviz')
    default_dae_path = os.path.join(get_package_share_directory('rm_robot_description'), 'dae', '3v3_map.dae')
    default_world_path = os.path.join(get_package_share_directory('rm_robot_description'), 'world', 'RMUL25.world')

    # 创建节点
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        condition=launch.conditions.UnlessCondition(LaunchConfiguration('gui'))
    )
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{'robot_description': ParameterValue(Command(['xacro ', LaunchConfiguration('model')]), value_type=str)}],
        output='screen'
    )
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
    )
    gazebo_server_node = Node(
        package='gazebo_ros',
        executable='/usr/bin/gzserver',
        name='gazebo_server',
        output='screen',
        arguments=['-s', 'libgazebo_ros_factory.so', LaunchConfiguration('world')]
    )
    gazebo_client_node = Node(
        package='gazebo_ros',
        executable='/usr/bin/gzclient',
        name='gazebo_client',
        output='screen'
    )
    spawn_entity_node = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='spawn_entity',
        output='screen',
        arguments=['-entity', 'robot', '-file', LaunchConfiguration('model')]
    )

    return LaunchDescription([
        DeclareLaunchArgument(name='gui', default_value='True', description='Flag to enable joint_state_publisher_gui'),
        DeclareLaunchArgument(name='model', default_value=default_model_path, description='Absolute path to robot urdf file'),
        DeclareLaunchArgument(name='rvizconfig', default_value=default_rviz_config_path, description='Absolute path to rviz config file'),
        DeclareLaunchArgument(name='dae', default_value=default_dae_path, description='Absolute path to robot dae file'),
        DeclareLaunchArgument(name='world', default_value=default_world_path, description='Absolute path to gazebo world file'),
        joint_state_publisher_node,
        robot_state_publisher_node,
        rviz_node,
        gazebo_server_node,
        gazebo_client_node,
        spawn_entity_node
    ])