#!/usr/bin/env python3
# FILE: robot_launch.py

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, Command, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    # 获取包的共享目录
    pkg_share = get_package_share_directory('four_omniwheel_robot')

    # 声明启动参数
    model_arg = DeclareLaunchArgument(
        'model',
        default_value='four_omniwheel_robot',
        description='Name of the robot model'
    )

    # 读取 URDF 文件内容
    robot_description_content = Command(['xacro ', os.path.join(pkg_share, 'urdf', 'four_omniwheel_robot.urdf')])
    robot_description = {'robot_description': robot_description_content}

    # joint_state_publisher_gui 节点
    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        output='screen'
    )

    # robot_state_publisher 节点
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )

    # rviz2 节点
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', os.path.join(pkg_share, 'rviz', 'urdf.rviz')],
        output='screen'
    )

    return LaunchDescription([
        model_arg,
        joint_state_publisher_gui_node,
        robot_state_publisher_node,
        rviz_node
    ])
