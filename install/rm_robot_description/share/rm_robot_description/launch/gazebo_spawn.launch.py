from launch import LaunchDescription
from launch.actions import GroupAction, IncludeLaunchDescription
from launch_ros.actions import Node
from launch.conditions import LaunchConfigurationEquals
from ament_index_python.packages import get_package_share_directory
import os
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
            'world_path': 'RMUC24_world.world'  # 相对于 world 目录
        },
        WorldType.RMUL: {
            'x': '4.3',
            'y': '3.35',
            'z': '1.16',
            'yaw': '0.0',
            'world_path': 'RMUL25.world'
            # 'world_path': 'RMUL2024_world/RMUL2024_world_dynamic_obstacles.world'
        }
    }
    return world_configs.get(world_type, None)

def generate_launch_description():
    bringup_dir = get_package_share_directory('rm_robot_description')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')

    # 创建 Gazebo 启动组
    def create_gazebo_launch_group(world_type):
        world_config = get_world_config(world_type)
        if world_config is None:
            return None

        return GroupAction(
            condition=LaunchConfigurationEquals('world', world_type),
            actions=[
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
                ),
                IncludeLaunchDescription(
                    PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')),
                    launch_arguments={'world': os.path.join(bringup_dir, 'world', world_config['world_path'])}.items(),
                )
            ]
        )

    bringup_RMUC_cmd_group = create_gazebo_launch_group(WorldType.RMUC)
    bringup_RMUL_cmd_group = create_gazebo_launch_group(WorldType.RMUL)

    return LaunchDescription([
        bringup_RMUL_cmd_group,
        bringup_RMUC_cmd_group,
    ])