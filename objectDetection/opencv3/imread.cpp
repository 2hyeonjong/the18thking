#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main()
{
	Mat image;
	image = imread("lena.jpg", IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);

	waitKey(0);

}
