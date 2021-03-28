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

namespace adas
{
    
    void watershed::watershed_alg(Mat frame, Mat&result)
    {
     //   Mat subFrame = frame(cv::Range(frame.rows / 2, frame.rows), cv::Range(0, frame.cols));
        Mat gray;
        Mat bw;

        cvtColor(frame, bw, COLOR_BGR2GRAY);
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

        for (int i = 0; i < contours.size(); i++)
        {
            drawContours(markers, contours, i, Scalar::all( + 1), -1);
        }
        circle(markers, cv::Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
        
        // Apply watershed.
        cv::watershed(frame, markers);

        vector<Vec3b> colors;

        for (int iter = 0; iter < contours.size(); iter++)
        {
            int b = RNG().uniform(0, 255);
            int g = RNG().uniform(0, 255);
            int r = RNG().uniform(0, 255);
            colors.push_back(Vec3b((unsigned char)b, (unsigned char)g, (unsigned char)r));
        }

        Mat dst = Mat::zeros(markers.size(), CV_8UC3);
        for (int iter = 0; iter < markers.rows; iter++)
        {
            for (int jiter = 0; jiter < markers.cols; jiter++)
            {
                int index = markers.at<int>(iter, jiter);
                if (index > 0 && index < contours.size())
                {
                    dst.at<Vec3b>(iter, jiter) = colors[index - 1];
                }
                else
                {
                    dst.at<Vec3b>(iter, jiter) = Vec3b(0, 0, 0);
                }
            }
        }
        imshow("watershed", dst);
    }
}