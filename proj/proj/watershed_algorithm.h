#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "canny_alg.h"

using namespace cv;

namespace MyProject
{
	// This class contains methods for watershed algorhitm.
	class watershed
	{
	public:
		// Add set of points
		static void set_points(std::vector<Point2f> points);
		
		// Watershed algorhitm.
		static void watershed_alg(Mat img);
	};
}


