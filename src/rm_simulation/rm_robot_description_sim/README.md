### 需求

sudo apt install ros-humble-nav2-common
sudo apt install ros-humble-behaviortree-cpp
sudo apt install ros-humble-navigation2
sudo apt install ros-humble-geographic-msgs
sudo apt install ros-humble-nav2-util
sudo locale-gen en_US.UTF-8
sudo update-locale

目前可用的是
urdf:four_omniwheel_robot.urdf
launch:robot.launch.py
rviz:urdf_config.rviz

    # 获取默认模型路径
    default_model_path = os.path.join(get_package_share_directory('rm_robot_description'), 'urdf', 'four_omniwheel_robot.urdf')
    default_rviz_config_path = os.path.join(get_package_share_directory('rm_robot_description'), 'rviz', 'urdf_config.rviz')
    default_dae_path = os.path.join(get_package_share_directory('rm_robot_description'), 'dae', '3v3_map.dae')