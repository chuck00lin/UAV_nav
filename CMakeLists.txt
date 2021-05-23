
cmake_minimum_required(VERSION 3.0.2)
project(uav_nav)

find_package(catkin REQUIRED COMPONENTS
  #---opencv---
  cv_bridge
  image_transport
  std_msgs
  #------
)


#catkin_package()
#if (CATKIN_ENABLE_TESTING)
#  find_package(roslaunch REQUIRED)
#  roslaunch_add_file_check(launch/cartographer_demo.launch)
#endif()

#next time add: urdf

catkin_package(
#--opencv--
  LIBRARIES uav_nav
  CATKIN_DEPENDS cv_bridge image_transport std_msgs
  DEPENDS system_lib
#------
)

## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

#--cartographer--
install(DIRECTORY launch configuration_files
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#--canny_edge_sol--
add_executable(canny_edge_sol src/canny_edge_sol.cpp)
target_link_libraries(canny_edge_sol ${catkin_LIBRARIES} ${OpenCV_LIBS} ${OpenCV_INCLUDE_DIRS})

