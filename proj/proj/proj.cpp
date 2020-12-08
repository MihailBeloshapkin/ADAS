#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

#include <iostream>
#include "Speed.h"

using namespace cv;
using namespace std;

Point point1;
Point point2;

Speed video_speed;

void CallBackFunction(int event, int x, int y, int flags, void *userdata)
{
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "Left button pressed on position:" << x <<  " " << y << endl;
		point1 = point2;
		point2 = Point(x, y);
		break;
	case EVENT_RBUTTONDOWN:
		video_speed.changeSpeed();
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	/*
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

		int key = waitKey(video_speed.getSpeed());
		if (key == 27)
		{
			break;
		}

	}

	capture.release();

	return 0;
	*/


    const string about =
        "This sample demonstrates Lucas-Kanade Optical Flow calculation.\n"
        "The example file can be downloaded from:\n"
        "  https://www.bogotobogo.com/python/OpenCV_Python/images/mean_shift_tracking/slow_traffic_small.mp4";
    const string keys =
        "{ h help |      | print this help message }"
        "{ @image | vtest.avi | path to image file }";
    CommandLineParser parser(argc, argv, keys);
    parser.about(about);
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    VideoCapture capture("IMG_8168.avi");
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }
    // Create some random colors
    vector<Scalar> colors;
    RNG rng;
    for (int i = 0; i < 100; i++)
    {
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(Scalar(r, g, b));
    }
    Mat old_frame, old_gray;
    vector<Point2f> p0, p1;
    // Take first frame and find corners in it
    capture >> old_frame;
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
    // Create a mask image for drawing purposes
    Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
    while (true) 
    {
        Mat frame, frame_gray;
        capture >> frame;
        if (frame.empty())
            break;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        // calculate optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15, 15), 2, criteria);
        vector<Point2f> good_new;
        for (uint i = 0; i < p0.size(); i++)
        {
            // Select good points
            if (status[i] == 1) {
                good_new.push_back(p1[i]);
                // draw the tracks
                line(mask, p1[i], p0[i], colors[i], 2);
                circle(frame, p1[i], 5, colors[i], -1);
            }
        }
        Mat img;
        add(frame, mask, img);
        imshow("Frame", img);
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
        // Now update the previous frame and previous points
        old_gray = frame_gray.clone();
        p0 = good_new;
    }
}