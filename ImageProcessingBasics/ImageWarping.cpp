#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// Image
/// </summary>
float w = 250, h = 350;
void main()
{
	
	string path = "Resources/cards.png";
	Mat img = imread(path); //Matrix Datatype used by openCV
	Mat imgWarp;
	// Point 2 -> 2d f -> floating point
	Point2f src[4] = { {363, 171}, {437,136}, {482, 239}, {556, 201} };
	Point2f dest[4] = { {0.0f,0.0f}, {w, 0.0f}, {0.0f, h}, {w,h} };
	Mat transformMatrix = getPerspectiveTransform(src, dest);
	warpPerspective(img, imgWarp, transformMatrix, Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 10, Scalar(0, 255, 0), 2);
	}
	// Plotting the images
	imshow("Main Image", img);
	imshow("Warped Image", imgWarp);
	waitKey(0);
}
