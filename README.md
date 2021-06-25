# UAV_nav
UAV pixhawk4-ROS-Ardupilot navigation

## Install
dependency
- ROS-noetic
- Cartographer
- Robot pose publisher
```
git clone https://github.com/GT-RAIL/robot_pose_publisher.git
cd $HOME/ros_ws/src/robot_pose_publisher/src
vi robot_pose_publisher.cpp
# modify line 40 to look like below ("false" has been changed to "true")
# line40: nh_priv.param<bool>("is_stamped", is_stamped, true);

```
- ROS package
```
sudo apt-get install ros-noetic-move-base
sudo apt-get install ros-noetic-amcl

# check if installed: ls /opt/ros/noetic/lib/{find your package}
```
**Build this**  
- git clone to your ROS workspace
- catkin build uav_sim

## Usage
### Cartographer
1) Online SLAM with TG15
```
roslaunch uav_nav TG_base.launch 
roslaunch uav_nav online_cortographer_XXX.launch

//one button version
roslaunch l_online_cartographer
//with ardupilot
roslaunch mavros apm.launch fcu_url:=/dev/ttyAMA0:57600  

rosbag record -a -O XXX.bag

```
2) Offline SLAM with bag
```
- offline-cartographer slam
roslaunch uav_nav old_palyback_cartographer.launch bag_filename:=${HOME}/Document/bagfiles/(laser_frame).bag
roslaunch uav_nav palyback_cartographer.launch bag_filename:=${HOME}/Document/bagfiles/(base_link).bag 

- pbstream save
rosservice call /finish_trajectory 0
rosservice call /write_state "{filename: '${HOME}/Document/map/bime_4f.pbstream', include_unfinished_submaps: "true"}"
```
```
- pbstream to rosmap
//1)only save map
rosrun cartographer_ros cartographer_pbstream_to_ros_map -map_filestem=/home/ubuntu/Document/map/bime_4fmap  -pbstream_filename=/home/ubuntu/Document/map/bime_4f.pbstream
#沒確定儲存完之前 cartographer 不能關掉

//2)constum save map and save png/ply also
roslaunch uav_nav assets_writer_ros_map.launch bag_filename:=${HOME}/Document/bag/home-20210623_shorttest.bag pose_graph_filename:=${HOME}/Document/bag/home-20210623_shorttest.pbstream
```
3) localization
```
roslaunch uav_nav l_online_cartographer.launch
//inspect the position
rostopic echo /robot_pose
//out put to UAV
roslaunch mavros apm.launch fcu_url:=/dev/ttyAMA0:57600 
```

### Aruco Detect
1) Usb cam with web_video_server
```
roslaunch uav_nav usb_cam_test_video0.launch
rosrun uav_nav aruco_detect
rosrun web_video_server web_video_server
```
### MavROS
connection
```
roslaunch mavros apm.launch fcu_url:=/dev/ttyAMA0:57600  
roslaunch mavros apm.launch fcu_url:=udp://:14855@
```

### Tools
urdf check
```
roslaunch urdf_tutorial display.launch model:='$(find cartographer_ros)/urdf/backpack_2d.urdf'
```
tf tree
```
rosrun tf2_tools view_frames.py
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
- Aruco - detect (todo: ros topic 10Hz,camera calibration )

### Opencv
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
