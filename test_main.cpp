#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "DownScale.h"
#include "Thinning.h"
#include "FT.h"

int main() {
	char sw = 'a';
	int thr, sca, num;
	cv::Mat output;
	std::cout<<"Select input(Video or test.png): ";
//	std::cin>>sw;
	if (sw=='V' || sw=='v')	{
		cv::VideoCapture cap(0);
		if (!cap.isOpened())	return -1;
		cap >> output;
        cv::cvtColor(output, output, CV_BGR2GRAY);
		cap.release();
	}
	else	output = cv::imread("test.png");
	
	if (output.empty()) {	
		std::cout<<"empty";
		return -1;
	}
	thr = 128;
	sca = 2;
//	std::cin>>thr;
//	std::cin>>sca;
	if ( output.type() != CV_8UC1) cv::cvtColor(output, output, CV_BGR2GRAY);

	int count = 1;
	for (;;) {
		for (int i=0; i<5; i++) {
			output = thinning(output, thr, &num);
			if (num==0)	break;
		}
		if (num==0)	{
			output = downscale_avg(output, sca);
			output = thinning(output, thr, &num);
			count*=2;
			break;
		}
		output = downscale_avg(output, sca);
		count*=2;
	}
	std::cout<<"\nscale="<<count<<"\n";
	cv::namedWindow("dst");
//	cv::imshow("dst", output);
	cv::imwrite("dst.png", output);
//	cv::waitKey();
	
	cv::Mat fimg = FT(output, 100);
//	cv::imshow("dst", fimg);
	cv::imwrite("fimg.png", fimg);
//	cv::waitKey();

	output = cv::imread("test.png");
    cv::cvtColor(output, output, CV_BGR2GRAY);
	for (int i=1; i<count; i*=2)	output = downscale_avg(output, 2);
	cv::imwrite("input_o.png", output);
//	cv::waitKey();
	
	fimg = FT(output, 100);
//	cv::imshow("dst", fimg);
	cv::imwrite("fimg_o.png", fimg);
//	cv::waitKey();

	return 0;
}
