# Issues i've met 
## [1] Can't successfully catkin build 

### OPENCV can't find (sloved) 
:ok_hand:solution:  
> right Cmakelist and package.xml file 
 
- install opencv  
found out that opencv was installed with ros noetic
ref:  
https://answers.ros.org/question/362202/best-opencv-version-for-ros-noetic/
https://blog.csdn.net/weixin_42584917/article/details/111308873
http://wiki.ros.org/vision_opencv
https://shenxiaohai.me/2018/08/29/ros-opencv/#OpenCV%E7%9A%84ROS%E6%8E%A5%E5%8F%A3

- find opencv   
pkg-config --modversion opencv4 : 4.2.0 
pkg-config --cflags opencv4: -I/usr/include/opencv4/opencv -I/usr/include/opencv4 
pkg-config --libs opencv4: (should show up libs file) 

- check Cmake variable  
find it dpkg -L libopencv-dev | grep cmake 
take a look 

### Python version was wrong (solved)
:ok_hand:solution:
> purge python2 (maybe not a good way)  
> switch to python3

- switch python version
```
sudo update-alternatives --list python
sudo update-alternatives --install /usr/bin/python python /usr/bin/python2 1
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 2
sudo update-alternatives --config python
```
check 
```
python --version
```
ref:  
https://www.fosslinux.com/39384/switching-between-python-2-and-3-versions-on-ubuntu-20-04.htm 
https://stackoverflow.com/questions/15291500/i-have-2-versions-of-python-installed-but-cmake-is-using-older-version-how-do

## [2]OPENCV and ROS
### ROS image topic convert (solved)
:ok_hand:solution:
> use cv_bridge

ref:  
https://blog.csdn.net/bigdog_1027/article/details/79090571

### Aruco 
:hammer:progressing  
ref:  
https://github.com/UbiquityRobotics/fiducials/blob/kinetic-devel/aruco_detect/src/aruco_detect.cpp
https://github.com/sturkmen72/opencv_samples/blob/master/14188-calc-eucliadian-distance-between-two-single-point.cpp
https://github.com/warp1337/ros_aruco/blob/master/src/ros_aruco.cpp

## [3]Cartographer
### Tunigng
:hammer:progressing  

--warning message-- 
```
Dropped 25 earlier points
```

ref:
https://blog.csdn.net/tiancailx/article/details/92959451
https://blog.csdn.net/xmy306538517/article/details/86609497
https://github.com/cartographer-project/cartographer_ros/issues/1303

### Transform 
:ok_hand:solution:
> add urdf
> edit ydlidar node (remove tf publish)  

--warning message--
```
no transform from map to base_link
ould not compute submap fading: Could not find a connection between 'map' and 'base_link' because they are not part of the same tree.Tf has two or more unconnected trees.
```
- urdf: uav_lalala  
validation  
```
apt-get install liburdfdom-tools
check_urdf my_robot.urdf
roslaunch urdf_tutorial display.launch model:='$(find cartographer_ros)/urdf/backpack_2d.urdf'

```
- tf tree inspect  
```
sudo apt-get install ros-noetic-tf2-tools
rosrun tf2_tools view_frames.py //or: rosrun tf tf_monitor
```

ref: 
https://blog.csdn.net/tiancailx/article/details/78910317
http://fugjo16.blogspot.com/2017/06/ros-urdf.html
https://github.com/cartographer-project/cartographer_ros/blob/master/cartographer_ros/launch/backpack_2d.launch
https://github.com/YDLIDAR/ydlidar_ros
