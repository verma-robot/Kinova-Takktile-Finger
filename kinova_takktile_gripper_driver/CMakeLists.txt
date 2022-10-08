cmake_minimum_required(VERSION 3.0.2)
project(kinova_takktile_gripper_driver)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  kinova_takktile_gripper_msgs
  roscpp
  rospy
  sensor_msgs
  tf
)
link_directories(${PROJECT_SOURCE_DIR}/lib/)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES kinova_takktile_gripper_driver
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(kinova_takktile_gripper_driver_node src/kinova_takktile_gripper_node.cpp  src/kinova_takktile_gripper.cpp )
target_link_libraries(kinova_takktile_gripper_driver_node ${catkin_LIBRARIES} dl)
add_dependencies(kinova_takktile_gripper_driver_node  ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ) 

install(FILES  lib/kinova_takktile_gripper_api.so  DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})


install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
