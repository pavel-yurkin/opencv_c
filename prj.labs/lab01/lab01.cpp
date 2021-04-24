#include <opencv2/opencv.hpp>
#include <time.h>
using namespace cv;
using namespace std;

int main()
{
	//������ ������
	const int height = 60;
	const int width = 768;
	//������ � ������ ��������
	Mat I_1(height, width, CV_8U);
	Mat G_1(height, width, CV_8U);
	Mat G_2(height, width, CV_8U);
	//����� �������� �����������
	for (int i = 0; i < width; i++) {
		line(I_1, Point(i, 0), Point(i, height), Scalar(i/(width/256), i/(width/256), i/(width/256)), 1);
	}
	//����� �������
	//������ ����� pow
	TickMeter tm;
	tm.start();
	//����������� 2.2
	//����������� float
	I_1.convertTo(G_1, CV_64F);
	G_1 /= 255;
	pow(G_1, 2.2, G_1);
	G_1 *= 255;
	G_1.convertTo(G_1, CV_8U);
	tm.stop();
	cout << "pow time: " << tm.getTimeSec();
	cout << endl;
	//����� �������
	tm.start();
	//����������� float
	I_1.convertTo(G_2, CV_64FC1);
	for (int i = 0; i < G_2.rows; ++i) {
		for (int j = 0; j < G_2.cols; ++j) {
			G_2.at<double>(i, j) = (pow(G_2.at<double>(i, j) / 255.0, 2.2)) * 255.0;
		}
	}
	G_2.convertTo(G_2, CV_8U);
	tm.stop();
	cout << "pixel time: " << tm.getTimeSec();
	cout << endl;
	//����������
	vconcat(I_1, G_1, I_1);
	vconcat(I_1, G_2, I_1);
	imshow("image", I_1);
	waitKey(0);
	//����������
	imwrite("lab01.png", I_1);
	return 0;
}