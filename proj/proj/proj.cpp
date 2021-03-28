#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "filters.h"
#include "optical_flow.h"
#include "watershed_algorithm.h"
#include "line_transfer.h"
#include "process.h"

using namespace cv;
using namespace std;
using namespace adas;

Point2f point;

optical_flow alg;

int count_of_added_points = 0;

// Speed video_speed;

vector<Mat> splited_hsv = vector<Mat>();

Mat src;

typedef unsigned char uchar;

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
        int rgb[3];
        rgb[0] = static_cast<int>(src.at<Vec3b>(y, x)[0]);
        rgb[1] = static_cast<int>(src.at<Vec3b>(y, x)[1]);
        rgb[2] = static_cast<int>(src.at<Vec3b>(y, x)[2]);
        cout << "R " << rgb[0]
             << ";G " << rgb[1]
             << ";B " << rgb[2] << endl;
        if (rgb[0] > 170 && rgb[1] > 170 && rgb[2] > 170)
        {
            cout << "snow" << endl;
        }
        else
        {
            cout << "road" << endl;
        }
        break;
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
    
    process<Mat> detection(frame);
    detection.run();
    waitKey(10000);
    /*
    imshow("src", frame);
    
 //   watershed::watershed_alg(frame, frame);
    namedWindow("Get_RGB_values");
    
    setMouseCallback("Get_RGB_values", CallBackFunction, nullptr);

    frame.copyTo(src);

    imshow("Get_RGB_values", src);

    Mat result;
    
    filters current_filter(1, 3);
    current_filter.binary_filter(frame, frame, 170, 170, 170);
    imshow("Binary filter", frame);
    current_filter.canny_algorithm(frame, frame);
    imshow("Canny", frame);

    vector<Vec4i> lines;

    HoughLinesP(frame, lines, 1, CV_PI / 180, 50, 30, 350);
    cvtColor(frame, frame, CV_8U);
  
    vector<float> tangs;

    vector<Point2f> points;

    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        int coord1 = l[1];
        int coord2 = l[3];

        float tan = (float)(l[1] - l[3]) / (float)(l[2] - l[0]);
        
        tangs.push_back(tan);
        
     //   line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 69, 255), 3, LINE_AA);
        if (tan > 0.2 || tan < -0.2)
        {
            line_transfer::shift_line_down(l);
            points.push_back(Point2f(l[0], l[1]));
            points.push_back(Point2f(l[2], l[3]));
            line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 69, 255), 1, LINE_AA);
        }
    }



    vector<Point2f> points_for_tretch;
    
    optical_flow::tretch_points(capture, points);

    for (int i = 0; i < tangs.size(); i++)
    {
        cout << tangs[i] << endl;
    }

    imshow("result_src", src);


    Mat current_frame;
    Mat prev_frame;
    frame.copyTo(prev_frame);

    waitKey(100000);

    while (true)
    {
        capture >> current_frame;
        optical_flow::optical_flow_alg(frame, current_frame, points);
        
        current_frame.copyTo(current_frame);

        Mat result_frame;
        current_frame.copyTo(result_frame);

        for (int i = 0; i < points.size() / 2; i++)
        {
            line(result_frame, points[i], points[i + 1], Scalar(0, 0, 255), 1, LINE_AA);
        }

        imshow("result_frame", result_frame);

        int key = waitKey(33);
        
        if (key == 27)
        {
            break;
        }
    }
    */
    return 1;
}
