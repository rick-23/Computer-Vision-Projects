#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// Image
/// </summary>
void main()
{
	string path = "Resources/rk.jpg";
	Mat img_rk = imread(path); //Matrix Datatype used by openCV
	
	CascadeClassifier facial_cascade;
	facial_cascade.load("Resources/haarcascade_frontalface_default.xml");
	if (facial_cascade.empty()) { cout << "XML File Not Loaded" << endl; }

	vector<Rect> faces;
	facial_cascade.detectMultiScale(img_rk, faces, 1.1, 10);

	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img_rk, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}

	imshow("Rick's Image", img_rk);
	waitKey(0);
}
