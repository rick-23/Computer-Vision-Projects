#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

/// <summary>
/// Image
/// </summary>
Mat img_gray, img_blur, img_canny, img_dilated;
void getContours(Mat img_dil, Mat img_shapes) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> contour_poly(contours.size());
	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;
		if (area > 1000) {
			float perimeter = arcLength(contours[i], true);
			approxPolyDP(contours[i], contour_poly[i], 0.02 * perimeter, true);
			drawContours(img_shapes, contour_poly, i, Scalar(255, 0, 255), 2);
			cout << contour_poly[i] << endl;
			boundRect[i] = boundingRect(contour_poly[i]);
			int object_contours = (int)contour_poly[i].size();
			if (object_contours == 3) { objectType = "Triangle"; }
			else if (object_contours == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rectangle"; }
			}
			else if (object_contours == 5) { objectType = "Pentagon"; }
			else if (object_contours == 6) { objectType = "Hexagon"; }
			else if (object_contours > 6) { objectType = "Circle"; }

			drawContours(img_shapes, contour_poly, i, Scalar(255, 0, 255), 2);
			rectangle(img_shapes, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img_shapes, objectType, { boundRect[i].x,boundRect[i].y }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
}
void main()
{
	string path = "Resources/Shapes.jpg";
	Mat img_shapes = imread(path); //Matrix Datatype used by openCV
	
	cvtColor(img_shapes, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_blur, Size(3, 3), 3, 0);
	Canny(img_blur, img_canny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dilated, kernel);
	getContours(img_dilated, img_shapes);
	imshow("Original Image", img_shapes);
	imshow("Gray Image", img_gray);
	imshow("Blur Image", img_blur);
	imshow("Canny Image", img_canny);
	imshow("Dilated Image", img_dilated);
	waitKey(0);
}

