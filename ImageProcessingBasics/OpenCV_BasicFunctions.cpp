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
	string path = "Resources/test.jpg";
	Mat img = imread(path); //Matrix Datatype used by openCV
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

	// Color to GrayScale Conversion
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	// Gaussian Blur Filtering
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	// Canny's Edge Detection Algorithm
	Canny(imgBlur, imgCanny, 25, 75);
	// Dilate the image edges for thickness of the edges
	Mat kernel_element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDilate, kernel_element);
	// Eroding the image edges for thickness of the edges
	erode(imgDilate, imgErode, kernel_element);

	// Plotting the images
	imshow("Test Image", img);
	//imshow("Gray Image", imgGray);
	//imshow("Blur Image", imgBlur);
	imshow("Canny Image", imgCanny);
	imshow("Dilated Image", imgDilate);
	imshow("Eroded Image", imgErode);
	waitKey(0);
}
