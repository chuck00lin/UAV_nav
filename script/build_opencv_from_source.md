##Opencv 4.5.2
my_env

- ~~python 2.7.18~~ (purged)
- python 3.8.5
- pip 21.1 (python3.8) depencency
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
cv2.__version__
```
```
pkg-config --cflags opencv4
```

REF:
https://medium.com/ching-i/%E6%A8%B9%E8%8E%93%E6%B4%BE%E5%AE%89%E8%A3%9D-opencv-4-4-0-606900caf370

