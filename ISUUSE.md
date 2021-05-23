# Issues i've met 
## Can't successfully catkin build 

### OPENCV can't find (sloved) 
solution: 
``` 
right Cmakelist and package.xml file 
``` 
- Opencv version and installed path 

**install opencv**
found out that opencv was installed with ros noetic
ref:  
https://answers.ros.org/question/362202/best-opencv-version-for-ros-noetic/
https://blog.csdn.net/weixin_42584917/article/details/111308873
http://wiki.ros.org/vision_opencv
https://shenxiaohai.me/2018/08/29/ros-opencv/#OpenCV%E7%9A%84ROS%E6%8E%A5%E5%8F%A3

**find opencv** 
pkg-config --modversion opencv4 : 4.2.0 
pkg-config --cflags opencv4: -I/usr/include/opencv4/opencv -I/usr/include/opencv4 
pkg-config --libs opencv4: (should show up libs file) 

**check Cmake variable**
find it dpkg -L libopencv-dev | grep cmake 
take a look 

### Python version was wrong (solved)
solution:
```
purge python2 (maybe not a good way)
switch to python3
```
**switch python version**
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

