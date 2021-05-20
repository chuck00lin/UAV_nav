# UAV_nav
UAV pixhawk4-ROS-Ardupilot navigation

## Install
dependency
- ROS-noetic
- Cartographer
```
sudo apt-get install ros-noetic-move-base
sudo apt-get install ros-noetic-amcl

# check if installed: ls /opt/ros/noetic/lib/{find your package}
```

## Usage
### Cartographer
1) Online SLAM with TG15
```
roslaunch uav_nav uav_bag_to_map.launch bag_filename:=${HOME}/Document/bagfiles/2021-04-02-10-40-04.bag

```

## Error Shooting
- Cartographer_ros CMake Error:
```
CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
Please set them or make sure they are set and tested correctly in the CMake files:
GMOCK_LIBRARY
    linked by target "time_conversion_test" ...
```
Solved
```
sudo apt install libgmock-dev
```

