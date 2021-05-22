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

## Working
- Cartographer sstatic landmark
- Aruco - detect

### Opencv 4.5.2
my_env
- python 2.7.18
- python 3.8.5
- pip 21.1 (python3.8)
depencency

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libgtk2.0-dev
sudo apt-get install pkg-config
sudo apt-get install python-dev python-numpy python3-dev python3-numpy
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libjpeg-dev libpng-dev libtiff-dev
```
install
```
mkdir opencv
cd opencv
git clone https://github.com/opencv/opencv.git
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j4
sudo make install
sudo ldconfig #動態連結庫
```
check, if nothing come up than success
```
python
import cv2
```
