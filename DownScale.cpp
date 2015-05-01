#include "DownScale.h"

DownScale::DownScale(){};

DownScale::~DownScale(){};

int DownScale::setImage(cv::Mat in, int s) {
	int col, row;
	scale = s;
	col = in.cols;
	row = in.rows;

	if (col==0 && row==0)	return 1;
	img.create(row, col, CV_8UC1);
	cv::cvtColor(in, img, CV_BGR2GRAY);
	
	return 0;
}

int DownScale::downscale(cv::Mat out, unsigned char color) {
	int col, row;
	int x,y;
	int flag=0;
	int pos=0;
	col = out.cols;
	row = out.rows;

	if (col != img.cols/scale || row != img.rows/scale)	return 1;

	for (int i=0; i<row; i++) {
		y = i*scale*img.cols;
		for (int j=0; j<col; j++) {
			x = j*scale;
			flag=0;
			for(int k=0; k<scale; k++) {
				for (int l=0; l<scale; l++) {
					if ( (unsigned char)img.data[x+y+l+k*img.cols] > color) {
						flag=1;
						pos =x+y+l+k*img.cols;
						break;
					}
				}
				if (flag)	break;
			}
			out.data[j+i*col] = flag ? (unsigned char)img.data[pos] : 0;
		}
	}
	return 0;
}

