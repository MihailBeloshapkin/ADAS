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

void opticalFlow(VideoCapture capture)
{
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
    old_frame = old_frame(cv::Range(old_frame.rows / 2, old_frame.rows), cv::Range(0, old_frame.cols));
    cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
    // Create a mask image for drawing purposes
    Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
    while (true)
    {
        Mat frame, frame_gray;

//        for (int iter = 0; iter < video_speed.getSpeed(); iter++)
//        {
 //           capture >> frame;
 //       }

        Mat subFrame = frame(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols));
        if (frame.empty())
        {
            break;
        }

        cvtColor(subFrame, frame_gray, COLOR_BGR2GRAY);
        imshow("Gray", frame_gray);


        // calculate optical flow
        vector<uchar> status;
        vector<float> err;
        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, Size(15, 15), 2, criteria);
        vector<Point2f> good_new;
        for (uint i = 0; i < p0.size(); i++)
        {
            // Select good points
            if (status[i] == 1)
            {
                good_new.push_back(p1[i]);
                // draw the tracks
                line(mask, p1[i], p0[i], colors[i], 2);
                circle(frame, p1[i], 5, colors[i], -1);
            }
        }
        Mat img;
        add(subFrame, mask, img);
        imshow("Frame", img);
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
        // Now update the previous frame and previous points
        old_gray = frame_gray.clone();
        p0 = good_new;
    }
}


int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

/*
static void CannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}
*/

class cannyAlg {
private:
    int lowThreshold = 0;
    int nkernelSize = 0;
    
public:
    void cannyAlgorithm(Mat frame, Mat detected_edges)
    {
        Mat gray;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        imshow("gray", gray);
        GaussianBlur(gray, detected_edges, Size(5, 5), 0);
        Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, kernel_size);
        imshow("canny", detected_edges);
    }

};

void cannyAlgorithm(Mat frame, Mat detected_edges)
{
    Mat gray;

    cvtColor(frame, gray, COLOR_BGR2GRAY);
    imshow("gray", gray);
    GaussianBlur(gray, detected_edges, Size(5, 5), 0);
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, kernel_size);
    imshow("canny", detected_edges);
}

int main(int argc, char** argv)
{
    /*
    VideoCapture capture("C:\\Users\\france\\source\\repos\\MyProject\\videos\\example.avi");
    if (!capture.isOpened())
    {
        throw "Unable to open source file";
    }
    namedWindow("Video", 1);

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

        int key = waitKey(video_speed.getSpeed());
        if (key == 27)
        {
            break;
        }

    }

    capture.release();
    return 0;
    */


    VideoCapture capture("C:\\Users\\france\\source\\repos\\MyProject\\videos\\example.avi");
    if (!capture.isOpened()) {
        //error in opening the video input
        cerr << "Unable to open file!" << endl;
        return 0;
    }

 //   namedWindow("Frame", 1);
    setMouseCallback("Frame", CallBackFunction, NULL);

    Mat frame;
    capture >> frame;

    Mat subFrame = frame(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols));
    Mat gray;
    Mat bw;

    cvtColor(subFrame, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    Mat dist;

    distanceTransform(bw, dist, DIST_L2, 3);

    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    threshold(dist, dist, 0.5, 1.0, THRESH_BINARY);

    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat markers = Mat::zeros(dist.size(), CV_32S);

    for (size_t i = 0; i < contours.size(); i++)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    imshow("contours", markers);

    imshow("dilate", dist);
    imshow("frame", subFrame);
    imshow("bin", bw);
    waitKey(10000);
    cannyAlgorithm(subFrame, subFrame);

    
    waitKey(10000);
    return 1;
}

