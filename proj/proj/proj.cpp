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

    namedWindow("Get_RGB_values");
    
    setMouseCallback("Get_RGB_values", CallBackFunction, nullptr);

    frame.copyTo(src);

    imshow("Get_RGB_values", src);

    for (int y = 0; y < frame.rows; y++)
    {
        for (int x = 0; x < frame.cols; x++)
        {
            int rgb[3];
            rgb[0] = static_cast<int>(src.at<Vec3b>(y, x)[0]);
            rgb[1] = static_cast<int>(src.at<Vec3b>(y, x)[1]);
            rgb[2] = static_cast<int>(src.at<Vec3b>(y, x)[2]);

            if (rgb[0] > 170 && rgb[1] > 170 && rgb[2] > 170 && y > frame.rows / 2)
            {
                frame.at<Vec3b>(y, x)[0] = 255;
                frame.at<Vec3b>(y, x)[1] = 255;
                frame.at<Vec3b>(y, x)[2] = 255;
            }
            else
            {
                frame.at<Vec3b>(y, x)[0] = 0;
                frame.at<Vec3b>(y, x)[1] = 0;
                frame.at<Vec3b>(y, x)[2] = 0;
            }
        }
    }

    
    canny_alg::canny_algorithm(frame, frame);
    
    vector<Vec4i> lines;

    
    HoughLinesP(frame, lines, 1, CV_PI / 180, 50, 30, 350);
    cvtColor(frame, frame, CV_8U);
  
    vector<float> tangs;

    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        int coord1 = l[1];
        int coord2 = l[3];

        float tan = (float)(l[1] - l[3]) / (float)(l[2] - l[0]);
        
        tangs.push_back(tan);
        
        
        if (tan > 0.3 || tan < -0.3)
        {
            line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
        }
    }

    for (int i = 0; i < tangs.size(); i++)
    {
        cout << tangs[i] << endl;
    }

    imshow("result", frame);

    imshow("result_src", src);

    //    imshow("frame", frame);
    /*
    //Get hsv array from the origin image.
    Mat hsv = Mat(frame.cols, frame.rows, 8, 3);
    vector<Mat> splited_hsv = vector<Mat>();
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    split(hsv, splited_hsv);
    
    Mat src;
    frame.copyTo(src);
    for (int y = 0; y < hsv.cols; y++)
    {
        for (int x = 0; x < hsv.rows; x++)
        {
            int H = static_cast<int>(splited_hsv[0].at<unsigned char>(x, y));
            if (H < 50 || H > 100)
            {
                src.at<Vec3b>(x, y)[0] = 255;
                src.at<Vec3b>(x, y)[1] = 255;
                src.at<Vec3b>(x, y)[2] = 255;
            }
        }
    }

    imshow("src", src);
    */
//    imshow("1", splited_hsv[0]);
//    imshow("2", splited_hsv[1]);
//    imshow("3", splited_hsv[2]);

    // Get road
    // Mat hsv = Mat(frame.cols, frame.rows, 8, 3);

//    canny_alg::canny_algorithm(frame, frame);
//    imshow("Result", frame);
//    waitKey(100000);
//    alg.add_point(Point2f(509, 412));
//   alg.add_point(Point2f(473, 569));
//    alg.optical_flow_alg(capture);
//    setMouseCallback("Frame", CallBackFunction, NULL);
   // canny_alg::canny_algorithm(frame, frame);

    waitKey(1000000);
    return 1;
}

