#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "DownScale.h"

int main() {
	DownScale dw;
	cv::Mat output;
	cv::Mat input = cv::imread("test.png");
	output.create(input.rows/8, input.cols/8, CV_8UC1);
	dw.setImage(input, 8);
	dw.downscale(output, 125);

	cv::namedWindow("dst");
	cv::imshow("dst", output);

	cv::waitKey();
	
	return 0;
}
