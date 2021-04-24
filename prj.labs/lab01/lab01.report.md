## Работа 1. Исследование гамма-коррекции
автор: Юркин П.О.
дата: 2021-02-26

<https://mysvn.ru/Maxim_Kaverin/anime/yurkin_p_o/prj.labs/lab01/>

### Задание
1. Сгенерировать серое тестовое изображение $I_1$ в виде прямоугольника размером 768х60 пикселя с плавным изменение пикселей от черного к белому, одна градация серого занимает 3 пикселя по горизонтали.
2. Применить  к изображению $I_1$ гамма-коррекцию с коэффициентом из интервала 2.2-2.4 и получить изображение $G_1$ при помощи функции pow.
3. Применить  к изображению $I_1$ гамма-коррекцию с коэффициентом из интервала 2.2-2.4 и получить изображение $G_2$ при помощи прямого обращения к пикселям.
4. Показать визуализацию результатов в виде одного изображения (сверху вниз $I_1$, $G_1$, $G_2$).
5. Сделать замер времени обработки изображений в п.2 и п.3, результаты отфиксировать в отчете.

### Результаты

![](lab01.png)
Рис. 1. Результаты работы программы (сверху вниз $I_1$, $G_1$, $G_2$)

![image-20210226232343058](C:\Users\Pavel\AppData\Roaming\Typora\typora-user-images\image-20210226232343058.png)

Рис. 2. Время обработки изображений



### Текст программы

```cpp
#include <opencv2/opencv.hpp>

#include <time.h>
using namespace cv;
using namespace std;

void gradient(const Mat& img) {
	for (int i = 0; i < img.size().width; i++) {
		Point p1(i, 0);
		Point p2(i, img.size().height - 1);
		line(img, p1, p2, Scalar(i / (img.size().width - 1.0)), 1, 4);
	}
}

Mat gc_pow(Mat img, double gamma) {
	pow(img, gamma, img);
	return img;
}

Mat gc_pixel(Mat& img, double gamma) {
	for (int i = 0; i < img.size().width; ++i) {
		for (int j = 0; j < img.size().height; ++j) {
			img.at<float>(j, i) = pow(img.at<float>(j, i), gamma);
		}
	}
	return img;
}


int main()
{
	Mat img(60, 768, CV_32FC1, Scalar(0, 0, 0));
	Mat img42(60, 768, CV_32FC1, Scalar(0, 0, 0));
	Mat img1, img2;

	gradient(img);
	gradient(img42);
	clock_t start = clock();
	img1 = gc_pow(img, 2.3);
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "pow: " << seconds << " sec.\n";

	start = clock();
	img2 = gc_pixel(img, 2.3);
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "pixel: " << seconds << " sec.\n";

	vconcat(img42, img1, img42);
	vconcat(img42, img2, img42);
	imshow("image", img42);
	waitKey(0);

	imwrite("C:/yurkin_p_o/prj.labs/lab01/lab01.png", 255 * img42);
	return 0;
}
```

