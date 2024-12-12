cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0009 NEW)
cmake_policy(SET CMP0074 NEW)

project(rm_robot_description)

## Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.
add_definitions(-Wall -Werror)

## Find packages
find_package(PCL REQUIRED)
find_package(ament_cmake_auto REQUIRED)

ament_auto_find_build_dependencies()

## Include PCL directories
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})

## Your executable or library
# add_executable(your_executable src/main.cpp)
# target_link_libraries(your_executable ${PCL_LIBRARIES})

install(DIRECTORY
  urdf world rviz launch meshes
  DESTINATION share/${PROJECT_NAME}
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

ament_auto_package(
  INSTALL_TO_SHARE
  launch
  urdf
  meshes
  world
  rviz
  xacro
)