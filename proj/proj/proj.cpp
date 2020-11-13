#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Point point1;
Point point2;

void CallBackFunction(int event, int x, int y, int flags, void *userdata)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "Left button pressed on position:" << x <<  " " << y << endl;
		point1 = point2;
		point2 = Point(x, y);
		break;
	default:
		break;
	}
}

int main()
{
	VideoCapture capture("IMG_8168.avi");
	if (!capture.isOpened())
	{
		throw "Unable to open source file";
	}
	namedWindow("Video", 1);

	setMouseCallback("Video", CallBackFunction, NULL);

	while (true)
	{
		Mat frame;
		capture >> frame;
		
		if (frame.empty())
		{
			break;
		}
		line(frame, point1, point2, Scalar(0.5, 0.7, 0.3), 2, LINE_8);
		imshow("Video", frame);

		waitKey(33);
	}

	capture.release();

	return 0;
}