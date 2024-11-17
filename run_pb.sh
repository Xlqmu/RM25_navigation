cd ~/RM25
colcon build --packages-select rm_robot_description
source /opt/ros/humble/setup.bash
source /home/aurora/RM25/install/setup.bash
ros2 launch rm_robot_description rm_simulation.launch.py