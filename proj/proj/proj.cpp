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

Point2f point;

optical_flow alg;

int count_of_added_points = 0;

// Speed video_speed;

void CallBackFunction(int event, int x, int y, int flags, void* userdata)
{
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        cout << "Left button pressed on position:" << x << " " << y << endl;
        point = Point2f(x, y);
        alg.add_point(point);
        count_of_added_points++;
        break;
    case EVENT_RBUTTONDOWN:
  //      video_speed.changeSpeed();
    default:
        break;
    }
}


int main(int argc, char** argv)
{  
    VideoCapture capture("C:\\videos\\example_2.avi");
    if (!capture.isOpened()) 
    {
        cerr << "Unable to open file!" << endl;
        return 0;
    }

    Mat frame;
    capture >> frame;

//    canny_alg::canny_algorithm(frame, frame);
//    imshow("Result", frame);
//    waitKey(100000);
//    alg.add_point(Point2f(509, 412));
//   alg.add_point(Point2f(473, 569));
//    alg.optical_flow_alg(capture);
//    setMouseCallback("Frame", CallBackFunction, NULL);
    canny_alg::canny_algorithm(frame, frame);

    imshow("canny", frame);
 
    vector<Vec4i> lines;

    HoughLinesP(frame, lines, 1, CV_PI/180, 500, 10, 250);
    
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
    }

    imshow("frame", frame);
    waitKey(10000);
    return 1;
}

