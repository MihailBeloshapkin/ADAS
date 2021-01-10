#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "Speed.h"
#include "canny_alg.h"

using namespace cv;

namespace MyProject
{
	class watershed
	{
	public:
		static void set_points(std::vector<Point2f> points);
		static void watershed_alg(Mat img);
	};
}


