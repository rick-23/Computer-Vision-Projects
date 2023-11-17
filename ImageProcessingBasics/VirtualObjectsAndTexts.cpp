#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// Image
/// </summary>
void main()
{

	// CV_8UC3 -> 8bit Unsigned Integer image with 3 Color Channels
	Mat Img(640, 640, CV_8UC3, Scalar(255, 255, 255));
	circle(Img, Point(320, 320), 150, Scalar(69, 175, 54), FILLED);
	rectangle(Img, Point(130, 226), Point(382, 256), Scalar(96, 72, 24), 3);
	line(Img, Point(130, 296), Point(382, 296), Scalar(200, 186, 144), 2);

	putText(Img, "Virtually Written", Point(137, 262), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(244, 0, 122), 2);
	// Plotting the images
	imshow("Test Image", Img);

	waitKey(0);
}
