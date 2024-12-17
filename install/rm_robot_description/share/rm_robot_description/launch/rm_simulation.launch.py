from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import Command, LaunchConfiguration
from launch.conditions import IfCondition, LaunchConfigurationEquals
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    bringup_dir = get_package_share_directory('rm_robot_description')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')

    # 指定 xacro 路径并生成机器人描述
    robot_description_content = Command([
        'xacro ',
        os.path.join(bringup_dir, 'urdf', 'simulation_waking_robot.xacro')
    ])

    # 创建启动配置变量
    use_sim_time = LaunchConfiguration('use_sim_time')
    use_rviz = LaunchConfiguration('rviz', default='true')

    # 声明启动参数
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='True',
        description='Use simulation (Gazebo) clock if true'
    )

    declare_world_cmd = DeclareLaunchArgument(
        'world',
        default_value='RMUL',
        description='Choose <RMUC> or <RMUL>'
    )

    declare_rviz_config_file_cmd = DeclareLaunchArgument(
        'rviz_config_file',
        default_value=os.path.join(bringup_dir, 'rviz', 'rviz2.rviz'),
        description='Full path to the RVIZ config file to use'
    )

    declare_robot_description_cmd = DeclareLaunchArgument(
        'robot_description',
        default_value=robot_description_content,  # 正确的默认值
        description='Robot description'
    )

    # 包含 Gazebo 客户端启动文件
    gazebo_client_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')
        ),
    )

    # 启动 joint_state_publisher 节点
    start_joint_state_publisher_cmd = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': robot_description_content
        }],
        output='screen'
    )

    # 启动 robot_state_publisher 节点
    start_robot_state_publisher_cmd = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{
            'use_sim_time': use_sim_time,
            'robot_description': robot_description_content
        }],
        output='screen'
    )

    # 启动 RViz
    start_rviz_cmd = Node(
        condition=IfCondition(use_rviz),
        package='rviz2',
        namespace='',
        executable='rviz2',
        arguments=['-d', LaunchConfiguration('rviz_config_file')],
        output='screen'
    )

    # 启动 spawn_entity 节点
    spawn_entity_cmd = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'robot',
            '-topic', 'robot_description',
            '-x', '0',
            '-y', '0',
            '-z', '0.1',
            '-Y', '0'
        ],
        output='screen'
    )

    # 创建 Gazebo 启动组（示例）
    # 您可以根据需要添加相应的 Gazebo 启动逻辑
    # 包含 Gazebo 服务器启动文件
    gazebo_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
        ),
        launch_arguments={'world': [os.path.join(bringup_dir, 'world', 'RMUL25.world')]}.items(),
)
    # 创建启动描述并添加动作
    ld = LaunchDescription()

    # 添加声明的启动参数
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(declare_world_cmd)
    ld.add_action(declare_rviz_config_file_cmd)
    ld.add_action(declare_robot_description_cmd)

    # 添加 Gazebo 客户端启动
    ld.add_action(gazebo_client_launch)

    # 添加节点启动
    ld.add_action(start_joint_state_publisher_cmd)
    ld.add_action(start_robot_state_publisher_cmd)

    # 添加 RViz 启动
    ld.add_action(start_rviz_cmd)

    ld.add_action(gazebo_server_launch)
    ld.add_action(spawn_entity_cmd)
    return ld