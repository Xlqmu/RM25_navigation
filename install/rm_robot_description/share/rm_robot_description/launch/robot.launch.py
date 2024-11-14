import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import PathJoinSubstitution

def generate_launch_description():
    # 
    gazebo_ros_pkg = get_package_share_directory('gazebo_ros')
    four_omniwheel_robot_pkg = get_package_share_directory('rm_robot_description')

    # Gazebo 启动文件路径
    gazebo_launch_file = PathJoinSubstitution([gazebo_ros_pkg, 'launch', 'gazebo.launch.py'])

    # SDF 文件路径
    rm_robot_description_pkg = get_package_share_directory('rm_robot_description')
    sdf_file = os.path.join(rm_robot_description_pkg, 'sdf', 'models.sdf')

    return LaunchDescription([
        # 启动 Gazebo
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gazebo_launch_file)
        ),

        # 发布 static transform between base_link and base_footprint
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='tf_footprint_base',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'base_footprint']
        ),

        # 在 Gazebo 中生成四轮全向轮小车模型
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            name='spawn_model',
            arguments=[
                '-file', sdf_file,
                '-entity', 'four_omniwheel_robot',
                '-x', '0',
                '-y', '0',
                '-z', '0.5'
            ],
            output='screen'
        ),

        # 使用 ExecuteProcess 发布 /calibrated 话题
        ExecuteProcess(
            cmd=['ros2', 'topic', 'pub', '/calibrated', 'std_msgs/msg/Bool', '{data: true}'],
            output='screen'
        )
    ])
