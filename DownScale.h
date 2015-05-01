#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class DownScale{
private:
	cv::Mat img;
	int scale;
public:
	DownScale();
	~DownScale();
	int setImage(cv::Mat in, int scale);
	int downscale(cv::Mat out, unsigned char color);
//	int downscale(cv::Mat out, cv::Mat map, unsigned short color);
};
