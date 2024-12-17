cmake_minimum_required(VERSION 3.10)
project(rm_robot_description_sim)

## Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Enforcing clean code with -Wall and -Werror
add_compile_options(-Wall -Werror)

if(POLICY CMP0009)
  cmake_policy(SET CMP0009 NEW)
endif()

if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ${CMAKE_EXPORT_COMPILE_COMMANDS})
endif()

# Add rclcpp as a dependency
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
###########
## Build ##
###########

# Add the node executable instead of a library
add_executable(${PROJECT_NAME}
  src/control_robot_keyboard.cpp
)

ament_target_dependencies(rm_robot_description_sim
  rclcpp
  sensor_msgs
  geometry_msgs
  nav_msgs
  tf2_ros
  tf2_geometry_msgs
)

install(TARGETS rm_robot_description_sim
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  list(APPEND AMENT_LINT_AUTO_EXCLUDE
    ament_cmake_copyright
    ament_cmake_uncrustify
  )
  ament_lint_auto_find_test_dependencies()
endif()

#############
## Install ##
#############

# 安装 launch 文件
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# 安装 URDF 文件
install(DIRECTORY urdf/
  DESTINATION share/${PROJECT_NAME}/urdf
)

# 安装模型和网格文件
install(DIRECTORY meshes/
  DESTINATION share/${PROJECT_NAME}/meshes
)

# 安装世界文件
install(DIRECTORY world/
  DESTINATION share/${PROJECT_NAME}/world
)

# 安装 RViz 配置文件
install(DIRECTORY rviz/
  DESTINATION share/${PROJECT_NAME}/rviz
)

#############
## 生成包 ##
#############

ament_package()
