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

namespace MyProject
{
    

	void optical_flow::optical_flow_alg(VideoCapture capture)
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
        vector<cv::Point2f> p0;
        vector<cv::Point2f> p1;

        Mat old_frame, old_gray;
        // Take first frame and find corners in it
        capture >> old_frame;
    //    old_frame = old_frame(cv::Range(old_frame.rows / 2, old_frame.rows), cv::Range(0, old_frame.cols));
        cvtColor(old_frame, old_gray, COLOR_BGR2GRAY);
        goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, Mat(), 7, false, 0.04);
        p0.push_back(Point2f(509, 412));
        // Create a mask image for drawing purposes
        Mat mask = Mat::zeros(old_frame.size(), old_frame.type());
        while (true)
        {
            Mat frame, frame_gray;

            capture >> frame;

            Mat subFrame = frame; /*(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols))*/
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
}