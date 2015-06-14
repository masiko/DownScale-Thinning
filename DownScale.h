#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/*
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
*/

cv::Mat downscale(cv::Mat input, int scale) {
	cv::Mat gray;
	cv::Mat output;
	int col, row;
	int ix,iy,ox,oy;

	if ( input.type() == CV_8UC3) cv::cvtColor(input, gray, CV_BGR2GRAY);
	else	gray = input.clone();
	col = input.cols/scale;
	row = input.rows/scale;
	output.create(row, col, CV_8UC1);

	for (int i=0; i<row; i++) {
		iy = i*input.cols*scale;
		oy = i*col;
		for (int j=0; j<col; j++) {
			ix = j*scale;
			ox = j;
			output.data[ox + oy] = gray.data[ix + iy];
		}
	}
	return output;
}

