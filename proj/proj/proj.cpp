#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "Speed.h"
#include "canny_alg.h"
#include "optical_flow.h"
#include "watershed_algorithm.h"

using namespace cv;
using namespace std;
using namespace MyProject;

Point point1;
Point point2;

//Speed video_speed;

void CallBackFunction(int event, int x, int y, int flags, void* userdata)
{
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        cout << "Left button pressed on position:" << x << " " << y << endl;
        point1 = point2;
        point2 = Point(x, y);
        break;
    case EVENT_RBUTTONDOWN:
  //      video_speed.changeSpeed();
    default:
        break;
    }
}


int main(int argc, char** argv)
{
    /*
    VideoCapture capture("C:\\Users\\france\\source\\MyProject\\videos\\example_2.AVI");
    if (!capture.isOpened())
    {
        throw "Unable to open source file";
    }
    namedWindow("Video");

    setMouseCallback("Video", CallBackFunction, NULL);

    Mat frame;
    capture >> frame;
    imshow("Video", frame);
    waitKey(1000);
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

        int key = waitKey();
        if (key == 27)
        {
            break;
        }

    }

    capture.release();
    return 0;
  */
   
    VideoCapture capture("C:\\Users\\france\\source\\MyProject\\videos\\example_2.avi");
    if (!capture.isOpened()) {
        cerr << "Unable to open file!" << endl;
        return 0;
    }

 //   setMouseCallback("Frame", CallBackFunction, NULL);

    optical_flow::optical_flow_alg(capture);

    return 1;
}

