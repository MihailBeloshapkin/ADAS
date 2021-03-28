#include "optical_flow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>

using namespace cv;
using namespace std;

namespace adas
{
    vector<Point2f> optical_flow::p0;
    vector<Point2f> optical_flow::p1;
    vector<Point2f> optical_flow::added;



    void optical_flow::add_point(Point2f new_point)
    {
        added.push_back(new_point);
    }

	void optical_flow::optical_flow_alg(cv::Mat prev_frame, cv::Mat current_frame, vector<cv::Point2f> points)
	{   
        Mat prev_frame_gray;
        Mat current_frame_gray;

        cvtColor(prev_frame, prev_frame_gray, COLOR_BGR2GRAY);
        cvtColor(current_frame, current_frame_gray, COLOR_BGR2GRAY);

               
     //   p0 = added;
        // Create a mask image for drawing purposes
        Mat mask = Mat::zeros(prev_frame.size(), prev_frame.type());
        
        vector<uchar> status;
        vector<float> err;

        TermCriteria criteria = TermCriteria((TermCriteria::COUNT) + (TermCriteria::EPS), 10, 0.03);
        calcOpticalFlowPyrLK(prev_frame_gray, current_frame_gray, points, points, status, err, Size(15, 15), 2, criteria);
	}

    void optical_flow::tretch_points(VideoCapture capture, vector<cv::Point2f> points)
    {
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
    //    old_frame = old_frame(cv::Range(old_frame.rows / 2, old_frame.rows), cv::Range(0, old_frame.cols));
        cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
     //   goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
        p0 = points;
        // Create a mask image for drawing purposes
        Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
        while (true) {
            Mat frame, frame_gray;
            capture >> frame;
        //    frame = frame(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols));
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
}