cmake_minimum_required(VERSION 3.14)
project(rm_mapping)

# 找到依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# 添加可执行文件
add_executable(map_server_node src/map_server_node.cpp)

# 链接依赖库
ament_target_dependencies(map_server_node rclcpp nav_msgs sensor_msgs)

# 安装目标
install(TARGETS
  map_server_node
  DESTINATION lib/${PROJECT_NAME})

# 安装 launch 文件（如果有）
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
