cmake_minimum_required(VERSION 3.5)
project(rm_localization)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(PCL REQUIRED)

ament_package()

install(TARGETS
	pcd_publisher
	DESTINATION lib/${PROJECT_NAME})
