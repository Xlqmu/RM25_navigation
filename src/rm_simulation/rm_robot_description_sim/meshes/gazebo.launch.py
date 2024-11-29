import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import PathJoinSubstitution

def generate_launch_description():
    # 获取包路径
    gazebo_ros_pkg = get_package_share_directory('gazebo_ros')
    four_omniwheel_robot_pkg = get_package_share_directory('four_omniwheel_robot')

    # Gazebo 启动文件路径
    gazebo_launch_file = PathJoinSubstitution([gazebo_ros_pkg, 'launch', 'gazebo.launch.py'])

    # URDF 文件路径
    urdf_file = PathJoinSubstitution([four_omniwheel_robot_pkg, 'urdf', 'four_omniwheel_robot.urdf'])

    return LaunchDescription([
        # 启动 Gazebo
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gazebo_launch_file)
        ),

        # 发布 base_link 和 base_footprint 之间的静态变换
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='tf_footprint_base',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'base_footprint']
        ),

        # 在 Gazebo 中生成四轮全向轮小车模型
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',  # 保持为 'spawn_entity.py'
            name='spawn_model',
            arguments=[
                '-file', urdf_file,
                #'-urdf',
                #'-model', 'four_omniwheel_robot',
                '-entity', 'four_omniwheel_robot',  # 添加 -entity 参数
                '-x', '0',
                '-y', '0',
                '-z', '0.5'
            ],
            output='screen'
        ),

        # 使用 ExecuteProcess 发布 /calibrated 话题，确保使用 YAML 格式
        ExecuteProcess(
            cmd=['ros2', 'topic', 'pub', '/calibrated', 'std_msgs/msg/Bool', '{data: true}'],
            output='screen'
        )
    ])
