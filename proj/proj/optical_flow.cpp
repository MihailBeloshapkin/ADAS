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
    vector<Point2f> optical_flow::p0;
    vector<Point2f> optical_flow::p1;
    vector<Point2f> optical_flow::added;



    void optical_flow::add_point(Point2f new_point)
    {
        added.push_back(new_point);
    }

	void optical_flow::optical_flow_alg(cv::Mat prev_frame, cv::Mat current_frame, vector<cv::Point2f> points)
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
}