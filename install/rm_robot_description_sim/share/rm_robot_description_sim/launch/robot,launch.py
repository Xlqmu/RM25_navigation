import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration, Command
from launch.actions import DeclareLaunchArgument, GroupAction, AppendEnvironmentVariable, IncludeLaunchDescription
from launch_ros.actions import Node
from launch.conditions import IfCondition, LaunchConfigurationEquals
from launch.launch_description_sources import PythonLaunchDescriptionSource

class WorldType:
    RMUC = 'RMUC'
    RMUL = 'RMUL'

def get_world_config(world_type):
    world_configs = {
        WorldType.RMUC: {
            'x': '6.35',
            'y': '7.6',
            'z': '0.2',
            'yaw': '0.0',
            'world_path': 'world/RMUC24_world.world'
        },
        WorldType.RMUL: {
            'x': '4.3',
            'y': '3.35',
            'z': '1.16',
            'yaw': '0.0',
            'world_path': 'world/RMUL25.world'
        }
    }
    return world_configs.get(world_type, None)

def create_gazebo_launch_group(world_type, bringup_dir, pkg_gazebo_ros):
    world_config = get_world_config(world_type)
    if not world_config:
        return None
    return GroupAction(
        condition=LaunchConfigurationEquals('world', world_type),
        actions=[
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
                ),
                launch_arguments={'world': os.path.join(bringup_dir, world_config['world_path'])}.items(),
            ),
            Node(
                package='gazebo_ros',
                executable='spawn_entity.py',
                arguments=[
                    '-entity', 'robot',
                    '-topic', 'robot_description',
                    '-x', world_config['x'],
                    '-y', world_config['y'],
                    '-z', world_config['z'],
                    '-Y', world_config['yaw']
                ],
            )
        ]
    )

def generate_launch_description():
    bringup_dir = get_package_share_directory('rm_robot_description')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')

    use_sim_time = LaunchConfiguration('use_sim_time')
    robot_description = LaunchConfiguration('robot_description')
    use_rviz = LaunchConfiguration('rviz', default='true')

    append_enviroment = AppendEnvironmentVariable(
        'GAZEBO_PLUGIN_PATH',
        os.path.join(bringup_dir, 'meshes/obstacles/obstacle_plugin/lib')
    )

    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time', default_value='true', description='Use simulation (Gazebo) clock if true'
    )
    declare_world_cmd = DeclareLaunchArgument(
        'world', default_value=WorldType.RMUL, description='Choose <RMUC> or <RMUL>'
    )
    declare_robot_description_cmd = DeclareLaunchArgument(
        'robot_description',
        default_value=Command(['xacro ', os.path.join(bringup_dir, 'urdf/simulation_waking_robot.xacro')]),
        description='Robot description'
    )
    declare_rviz_config_file_cmd = DeclareLaunchArgument(
        'rviz_config_file',
        default_value=os.path.join(bringup_dir, 'rviz', 'rviz2.rviz'),
        description='Full path to the RVIZ config file to use'
    )

    gazebo_client_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py'))
    )

    start_joint_state_publisher_cmd = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    start_robot_state_publisher_cmd = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'use_sim_time': use_sim_time}],
        output='screen'
    )

    start_rviz_cmd = Node(
        condition=IfCondition(use_rviz),
        package='rviz2',
        executable='rviz2',
        arguments=['-d', LaunchConfiguration('rviz_config_file')]
    )

    bringup_RMUC_cmd_group = create_gazebo_launch_group(WorldType.RMUC, bringup_dir, pkg_gazebo_ros)
    bringup_RMUL_cmd_group = create_gazebo_launch_group(WorldType.RMUL, bringup_dir, pkg_gazebo_ros)

    ld = LaunchDescription()
    ld.add_action(append_enviroment)
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(declare_world_cmd)
    ld.add_action(declare_robot_description_cmd)
    ld.add_action(declare_rviz_config_file_cmd)
    ld.add_action(gazebo_client_launch)
    ld.add_action(start_joint_state_publisher_cmd)
    ld.add_action(start_robot_state_publisher_cmd)
    ld.add_action(start_rviz_cmd)
    if bringup_RMUC_cmd_group:
        ld.add_action(bringup_RMUC_cmd_group)
    if bringup_RMUL_cmd_group:
        ld.add_action(bringup_RMUL_cmd_group)
    return ld