#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat FT(cv::Mat img,int size) {
	int u, v;
	const double CON_EXP = 2*M_PI/size;
	double real = 0,
		   imag = 0,
		   real_x = 0,
		   imag_x = 0;
	double dst;
	unsigned char y = 0;

	cv::Mat fimg;
	fimg.create(size, size, CV_8UC1);
	
	std::cout<<"FT\n";

	for (v=-size/2; v<size/2; v++){
		std::cout<<v<<",";
		for (u=-size/2; u<size/2; u++){

			for (int i=0; i<img.rows; i++) {
				for (int j=0; j<img.cols; j++) {
					y = img.data[j+i*img.cols];
					real_x += y*cos(CON_EXP*u*j);
					imag_x += y*sin(CON_EXP*u*j);
				}
				real += real_x*cos(CON_EXP*v*i);
				imag += imag_x*sin(CON_EXP*v*i);
				real_x = 0;
				imag_x = 0;
			}

			dst = (real*real + imag*imag)/(img.cols*img.rows*255);
			if (dst > 255)	dst = 255;
			else if (dst < 0) dst = 0;
			fimg.data[(u+size/2) + (v+size/2)*size] = dst;
			
			real = 0;
			imag = 0;
			real_x = 0;
			imag_x = 0;
		}
	}
	return fimg;
}

/*
void FFT(cv::Mat img, int size) {
	const double CON_EXP = 2*M_PI/size;
	double real = 0,
		   imag = 0,
		   real_x = 0,
		   imag_x = 0,
		   ans    = 0;
	unsigned char y = 0;
	
	cv::Mat dst;
	dst.create(size, size, CV_8UC1);
	
	for (int v=-dst.rows/2; v<dst.rows/2; v++) {
		for (int u=-dst.cols/2; u<dst.cols/2; u++) {

			for (int i=0; i<img.rows; i++) {
				for (int j=0; j<img.cols; j++) {
					y = img.data[j+i*img.cols];
					real_x += y*cos(CON_EXP*u*j);
					imag_x += y*sin(CON_EXP*u*j);
				}
				real += real_x*cos(CON_EXP*v*i);
				imag += imag_x*sin(CON_EXP*v*i);
				real_x = 0;
				imag_x = 0;
			}

			ans = (real*real + imag*imag)/(img.cols*img.rows*255);
			if (ans > 255)	ans = 255;
			else if (ans < 0) ans = 0;

			dst.data[(u+dst.cols/2) + (v+dst.rows/2)*dst.cols] = (unsigned char)ans;
			real = 0;
			imag = 0;
		}
	}
}
*/

