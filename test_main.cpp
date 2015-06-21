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
	if ( output.type() == CV_8UC3) cv::cvtColor(output, output, CV_BGR2GRAY);

	for (;;) {
		for (int i=0; i<4; i++) {
			output = thinning(output, thr, &num);
			if (num==0)	break;
		}
		output = downscale(output, sca);
		if (num==0)	break;
	}

	cv::namedWindow("dst");
	cv::imshow("dst", output);
	cv::imwrite("dst.png", output);
	cv::waitKey();
	
	return 0;
}
