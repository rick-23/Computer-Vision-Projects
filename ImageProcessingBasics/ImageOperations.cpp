#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

///// <summary>
///// Image
///// </summary>
//void main()
//{
//	string path = "Resources/lena512.bmp";
//	Mat img_lena = imread(path); //Matrix Datatype used by openCV
//	imshow("Lena Image", img_lena);
//	waitKey(0);
//}

/// <summary>
/// Webcam
/// </summary>
void main()
{
	VideoCapture cap(0);
	Mat img; //Matrix Datatype used by openCV
	while (true)
	{
		cap.read(img);
		imshow("Webcam Test", img);
		waitKey(1);
	}
}