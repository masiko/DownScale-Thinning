#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "DownScale.h"
#include "Thinning.h"

int main() {
	int thr, sca, num;
//	cv::Mat output;
	cv::Mat output = cv::imread("test.png");
	std::cin>>thr;
	std::cin>>sca;
	std::cin>>num;
	if ( output.type() == CV_8UC3) cv::cvtColor(output, output, CV_BGR2GRAY);

	for (int i=0; i<num; i++)	{
		output = Thinning(output, thr);
		output = downscale(output, sca);
	}

	cv::namedWindow("dst");
	cv::imshow("dst", output);

	cv::waitKey();
	
	return 0;
}
