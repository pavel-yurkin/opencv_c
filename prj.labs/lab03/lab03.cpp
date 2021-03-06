#include <opencv2/opencv.hpp>
using namespace cv;

//### ???????
//1. ? ???????? ????????? ???????????? ??????????? data / cross_0256x0256.png

float F(const float& x, const int& imageSize) {
	return sin((CV_PI * 1.3 * x / 3) / (imageSize - 1)) * (imageSize - 1);
}

Mat Plot() {
	Mat output(512, 512, CV_8U, 255);
	for (int i = 0; i < 512; ++i) {
		output.at<uchar>(511 - F(i, 512), i) = 0;
	}
	return output;
}

Mat MakeBright(const Mat& img) {
	Mat output;
	std::vector<uchar> lookUpTable(256);
	for (int i = 0; i < 256; ++i) {
		lookUpTable[i] = F(i, 256);
	}
	LUT(img, lookUpTable, output);
	return output;
}

int main() {
	Mat img = imread("C:/yurkin_p_o/prj.labs/lab03/data_cross_0256x0256.png");
	Mat brite_img = MakeBright(img);
	Mat gray_img;
	cvtColor(img, gray_img, COLOR_BGR2GRAY);
	Mat brite_gray_img = MakeBright(gray_img);
	Mat plot = Plot();

	imwrite("lab03_rgb.png", img);
	imwrite("lab03_gre.png", gray_img);
	imwrite("lab03_rgb_res.png", brite_img);
	imwrite("lab03_gre_res.png", brite_gray_img);
	imwrite("lab03_viz_func.png", plot);
	vconcat(img, gray_img, img);
	vconcat(img, brite_img, img);
	vconcat(img, brite_img, img);
	vconcat(img, brite_gray_img, img);
	vconcat(img, plot, img);
	imshow("one", img);	
	waitKey(0);
	return 0;
}