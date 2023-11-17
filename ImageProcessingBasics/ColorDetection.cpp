#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// Image
/// </summary>
int hue_min = 0, sat_min = 0, val_min = 0;
int hue_max = 179, val_max = 255, sat_max = 255;
void main()
{
	string path = "Resources/Shapes.jpg";
	Mat img_lamb = imread(path); //Matrix Datatype used by openCV
	Mat img_hsv, mask;

	// Converting color image to HSV color frame
	cvtColor(img_lamb, img_hsv, COLOR_BGR2HSV);

	namedWindow("HSV Trackbars", (240, 240));
	createTrackbar("Hue Min", "HSV Trackbars", &hue_min, 179);
	createTrackbar("Hue Max", "HSV Trackbars", &hue_max, 179);
	createTrackbar("Sat Min", "HSV Trackbars", &sat_min, 255);
	createTrackbar("Sat Max", "HSV Trackbars", &sat_max, 255);
	createTrackbar("Val Min", "HSV Trackbars", &val_min, 255);
	createTrackbar("Val Max", "HSV Trackbars", &val_max, 255);

	while (true)
	{
		Scalar lower(hue_min, sat_min, val_min);
		Scalar upper(hue_max, sat_max, val_max);
		inRange(img_hsv, lower, upper, mask);
		imshow("Lamb Image", img_lamb);
		imshow("Lamb HSV Image", img_hsv);
		imshow("Lamb Mask", mask);
		waitKey(1);
	}


	
}

