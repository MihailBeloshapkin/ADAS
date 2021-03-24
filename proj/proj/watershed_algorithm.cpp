#include "watershed_algorithm.h"
#include "optical_flow.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>

using namespace std;

namespace MyProject
{
    
    void watershed::watershed_alg(Mat frame)
    {
        Mat subFrame = frame(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols));
    }

    /*
	void watershed::watershed_alg(Mat frame)
	{
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
	}*/
}