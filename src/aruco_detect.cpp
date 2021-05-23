#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <iostream>
#include <cstdlib>

#ifdef ROS_NOETIC
#include <opencv4/opencv2/imgproc/imgproc.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/aruco.hpp>
#else 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#endif

//namespace {
//const char* about = "Pose estimation of ArUco marker images";
/*const char* keys  =
        "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
        "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
        "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
        "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
        "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
        "{h        |false | Print help }"
        "{l        |      | Actual marker length in meter }"
        "{v        |<none>| Custom video source, otherwise '0' }"
        "{h        |false | Print help }"
        "{l        |      | Actual marker length in meter }"
        "{v        |<none>| Custom video source, otherwise '0' }"
        ;
}*/

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/usb_cam/image_raw", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

   //cv::namedWindow("source");
   //cv::namedWindow("canny");
  }

  ~ImageConverter()
  {
   // cv::destroyWindow("source");
   // cv::destroyWindow("canny");
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // ----- Run Aruco detector on image ----- 
    cv::Mat src = cv_ptr->image;
    cv::Mat dst;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    src.copyTo(dst);
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners;
    cv::aruco::detectMarkers(src, dictionary, corners, ids);
    // if at least one marker detected
    // corners structure: vector of dtected markers < vector of points >
    // id0 : points1, point2, point3, point4
    // id1 : points1, point2, point3, point4 ...

    if (ids.size() > 0){
        cv::aruco::drawDetectedMarkers(dst, corners, ids);

        for(int i=0;i<ids.size();i++){
	  float dist1,dist2;
	  cv::Point2f diff1= corners[i][0]-corners[i][1];
	  cv::Point2f diff2= corners[i][1]-corners[i][2];
	  dist1= cv::sqrt(diff1.x*diff1.x + diff1.y*diff1.y);
          dist2= cv::sqrt(diff2.x*diff2.x + diff2.y*diff2.y); 

	  std::string label = "d1:" + std::to_string(dist1) + "d2:"+ std::to_string(dist2);
	  float res=dist1/dist2;
	  if(res>0.9&&res<1.1){
	    cv::putText(dst,label,cv::Point(10, 15),cv::FONT_HERSHEY_SIMPLEX,0.5, cv::Scalar(0, 255, 0));
	  }
	  else{
	    cv::putText(dst,label,cv::Point(10, 15),cv::FONT_HERSHEY_SIMPLEX,0.5, cv::Scalar(255, 0, 0));
	  }
	}
    }

    // ----- Aruco end ----

    // Update GUI Window
    //cv::imshow("source", src);
    //cv::imshow("canny", dst);
    //cv::waitKey(3);

    sensor_msgs::ImagePtr msg_out = cv_bridge::CvImage(std_msgs::Header(), "bgr8", dst).toImageMsg();
    // Output modified video stream
    image_pub_.publish(msg_out);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}
