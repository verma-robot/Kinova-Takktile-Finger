cmake_minimum_required(VERSION 3.0.2)
project(kinova_takktile_gripper_msgs)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  message_runtime
)

 add_message_files(
   FILES
   finger_proximal.msg
   finger_tip.msg
   Finger.msg
   kg3_gripper.msg
   palm.msg
   kg2_gripper.msg

 )

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package()

include_directories(  ${catkin_INCLUDE_DIRS})
