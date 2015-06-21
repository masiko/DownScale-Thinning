#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat thinning(cv::Mat input, int threshold, int* num) {
	cv::Mat output;
	*num = 0;
	int col, row;
	int ix, iy;
	col = input.cols;
	row = input.rows;
	output.create(row, col, CV_8UC1);

	if ( input.type() == CV_8UC3) cv::cvtColor(input, input, CV_BGR2GRAY);
	
//	for (;;) {
	for (int i=1; i<row-1; i++) {
		iy = i*col;
		for (int j=1; j<col-1; j++) {
			if ( input.data[j + iy] > threshold ) {
				if ( input.data[j + iy-col] < threshold || input.data[j+1 + iy] < threshold) {
					if ( (input.data[j+1 + iy] > threshold && input.data[j + iy+col] > threshold && input.data[j+1 + iy+col] < threshold) ||
					 (input.data[j-1 + iy] > threshold && input.data[j + iy-col] > threshold && input.data[j-1 + iy-col] < threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy+col] > threshold && input.data[j+1 + iy] > threshold) ||
					 (input.data[j-1 + iy] > threshold && input.data[j + iy-col] < threshold && input.data[j + iy+col] < threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy-col] > threshold && input.data[j+1 + iy] < threshold) ||
					 (input.data[j + iy-col] < threshold && input.data[j + iy+col] < threshold && input.data[j+1 + iy] > threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy+col] < threshold && input.data[j-1 + iy+col] > threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy-col] < threshold && input.data[j-1 + iy-col] > threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy-col] < threshold && input.data[j+1 + iy-col] > threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy+col] < threshold && input.data[j+1 + iy+col] > threshold) )
							output.data[j + iy] = 255;
					else	output.data[j + iy] = 0, *num+=1;
				}
				else output.data[j + iy] = 255;
			}
			else output.data[j + iy] = 0;
		}
	}
	
	output.copyTo(input);
	
	for (int i=row-2; i>=1; i--) {
		iy = i*col;
		for (int j=col-2; j>=1; j--) {
			if ( input.data[j + iy] > threshold ) {
				if ( input.data[j + iy+col] < threshold || input.data[j-1 + iy] < threshold) {
					if ( (input.data[j-1 + iy] > threshold && input.data[j + iy-col] > threshold && input.data[j-1 + iy-col] < threshold) ||
					 (input.data[j+1 + iy] > threshold && input.data[j + iy+col] > threshold && input.data[j+1 + iy+col] < threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy-col] > threshold && input.data[j-1 + iy] > threshold) ||
					 (input.data[j+1 + iy] > threshold && input.data[j + iy+col] < threshold && input.data[j + iy-col] < threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy+col] > threshold && input.data[j-1 + iy] < threshold) ||
					 (input.data[j + iy+col] < threshold && input.data[j + iy-col] < threshold && input.data[j-1 + iy] > threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy-col] < threshold && input.data[j+1 + iy-col] > threshold) ||
					 (input.data[j+1 + iy] < threshold && input.data[j + iy+col] < threshold && input.data[j+1 + iy+col] > threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy+col] < threshold && input.data[j-1 + iy+col] > threshold) ||
					 (input.data[j-1 + iy] < threshold && input.data[j + iy-col] < threshold && input.data[j-1 + iy-col] > threshold) )
							output.data[j + iy] = 255;
					else	output.data[j + iy] = 0, *num+=1;
				}
				else output.data[j + iy] = 255;
			}
			else output.data[j + iy] = 0;
		}
	}
	output.copyTo(input);
//	}

	return output;
}

