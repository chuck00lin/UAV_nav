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
- git clone to your ROS workspace
- catkin build uav_sim

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

### ~~Opencv 4.5.2~~ Opencv 4.2 by noetic
my_env
~~ python 2.7.18~~ (purged)
- python 3.8.5
- pip 21.1 (python3.8)

find opencv 
pkg-config --modversion opencv4 : ```4.2.0```
pkg-config --cflags opencv4: ```-I/usr/include/opencv4/opencv -I/usr/include/opencv4```
pkg-config --libs opencv4: ```(should show up libs file)```
check Cmake variable: 1) find it ```dpkg -L libopencv-dev | grep cmake``` 2) take a look
ref:
https://answers.ros.org/question/369316/finding-opencv-paths-in-ros-builds/
https://answers.ros.org/question/237494/fatal-error-rosrosh-no-such-file-or-directory/
```
**ROS-opencv**
dependency
```
sudo apt-get install ros-noetic-image-transport
sudo apt-get install ros-noetic-cv-bridge
```
## Web image view(for ipad)
install
```
sudo apt-get install ros-noetic-async-web-server-cpp
git clone https://github.com/RobotWebTools/web_video_server
catkin build web_video_server
```
usage-rpi
```
#plugin usb, check device with :v4l2-ctl --list-devices
roslaunch uav_nav usb_cam_test_video1.launch
rosrun web_video_server web_video_server
```
usage-client
```
ssh -L 8080:localhost:8080 pi4 #host ip
http://localhost:8080/stream?topic=/usb_cam/image_raw
```
