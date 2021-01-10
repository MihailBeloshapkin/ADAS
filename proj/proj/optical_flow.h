#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

namespace MyProject
{
	class optical_flow
	{
	private:
		static vector<Point2f> p0;
		static vector<Point2f> p1;
		static vector<Point2f> added;
	public:
		static void add_point(Point2f new_point);

		// Calculate optical flow according the input vector of points.
		static void optical_flow_alg(cv::VideoCapture capture);
	};

}

