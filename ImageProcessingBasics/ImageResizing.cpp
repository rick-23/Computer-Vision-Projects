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
	Mat imgResize;
	cout << img.size() << endl;
	// Image Resizing
	resize(img, imgResize, Size(), 0.5, 0.5);
	// Image Cropping
	Rect regionOfInterest(100, 100, 300, 250);
	Mat imgCropped = img(regionOfInterest);

	// Plotting the images
	imshow("Test Image", img);
	imshow("Resize Image", imgResize);
	imshow("Cropped Image", imgCropped);


	waitKey(0);
}
