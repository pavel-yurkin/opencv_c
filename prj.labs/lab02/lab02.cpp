#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main()
{
	//Картинка 
	Mat img = imread("C:/yurkin_p_o/prj.labs/lab02/data_cross_0256x0256.png");
	//Картинки для сохранения
	Mat img1, img2, img3;
	Mat img1c, img2c, img3c;
	//сохранение jpeg 25%
	vector<int> comp;
	comp.push_back(IMWRITE_JPEG_QUALITY);
	comp.push_back(25);
	imwrite("C:/yurkin_p_o/prj.labs/lab02/cross_0256x0256_025.jpg", img, comp);
	Mat imgc = imread("C:/yurkin_p_o/prj.labs/lab02/cross_0256x0256_025.jpg");
	//разбить на каналы
	//диаграмы изображений
	//обычное
	Mat res(256, 512, CV_8U, 255);
	std::vector<int> vect(256);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			vect[img.at<uchar>(j, i)]++;
		}
	}
	int max = *max_element(vect.begin(), vect.end());
	for (int i = 0; i < 256; i++) {
		int h = vect[i] * 255 / max;
		Point p1(i * 2, 255 - h);
		Point p2(i * 2 + 1, 255);
		rectangle(res, p1, p2, 0);
	}
	//сжатое
	Mat res2(256, 512, CV_8U, 255);
	std::vector<int> vect2(256);
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			vect2[imgc.at<uchar>(j, i)]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		int h = vect2[i] * 255 / max;
		Point p1(i * 2, 255 - h);
		Point p2(i * 2 + 1, 255);
		rectangle(res2, p1, p2, 0);
	}
	hconcat(res, res2, res);
	//cross_0256x0256_hists.png
	imwrite("C:/yurkin_p_o/prj.labs/lab02/cross_0256x0256_hists.png", res);

	vector<Mat> rgb(3);
	split(img, rgb);
	//соеденить
	//добавить пустое изображение и канал
	Mat g = Mat::zeros(Size(img.cols, img.rows), CV_8UC1);
	vector<Mat> unrgb;
	unrgb.push_back(g);
	unrgb.push_back(g);
	unrgb.push_back(rgb[2]);
	merge(unrgb, img1);
	unrgb.clear();
	unrgb.push_back(g);
	unrgb.push_back(rgb[1]);
	unrgb.push_back(g);
	merge(unrgb, img2);
	unrgb.clear();
	unrgb.push_back(rgb[0]);
	unrgb.push_back(g);
	unrgb.push_back(g);
	merge(unrgb, img3);
	hconcat(img, img1, img);
	hconcat(img2, img3, img2);
	vconcat(img, img2, img);
	imwrite("C:/yurkin_p_o/prj.labs/lab02/cross_0256x0256_png_channels.png", img);
	//разбить на каналы
	vector<Mat> rgbс(3);
	split(imgc, rgbс);
	//соеденить
	vector<Mat> unrgbс;
	unrgbс.push_back(g);
	unrgbс.push_back(g);
	unrgbс.push_back(rgbс[2]); 
	merge(unrgbс, img1c);
	unrgbс.clear();
	unrgbс.push_back(g);
	unrgbс.push_back(rgbс[1]);
	unrgbс.push_back(g);
	merge(unrgbс, img2c);
	unrgbс.clear();
	unrgbс.push_back(rgbс[0]);
	unrgbс.push_back(g);
	unrgbс.push_back(g);
	merge(unrgbс, img3c);
	hconcat(imgc, img1c, imgc);
	hconcat(img2c, img3c, img2c);
	vconcat(imgc, img2c, imgc);
	imwrite("C:/yurkin_p_o/prj.labs/lab02/cross_0256x0256_jpg_channels.png", imgc);
	waitKey(0);
	return 0;
}