cmake_minimum_required(VERSION 3.5)
project(four_omniwheel_robot)

# Set the default C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Find necessary packages
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_auto REQUIRED)  # Add this line to include ament_cmake_auto
ament_auto_find_build_dependencies()     # Finds and sets up dependencies automatically

# Enable linting tests if building tests
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# Uncomment the packages you need for your project
# find_package(rclcpp REQUIRED)
# find_package(gazebo_ros REQUIRED)
# find_package(tf2_ros REQUIRED)
# find_package(std_msgs REQUIRED)
# find_package(rviz2 REQUIRED)
# find_package(xacro REQUIRED)

# Add your executable if you have any source code (.cpp) files
# add_executable(your_node src/your_node.cpp)
# ament_target_dependencies(your_node rclcpp gazebo_ros tf2_ros std_msgs)

# Install launch, urdf, meshes, and config files
# install(DIRECTORY launch urdf meshes config rviz
#   DESTINATION share/${PROJECT_NAME}
# )

# Install specific files
# install(
#   FILES urdf/four_omniwheel_robot.xacro
#   DESTINATION share/${PROJECT_NAME}/urdf
# )

ament_auto_package()  # This should now work as expected
