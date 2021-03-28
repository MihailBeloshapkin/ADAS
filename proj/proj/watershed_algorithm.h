#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <iostream>
#include "filters.h"

using namespace cv;

namespace adas
{
	// This class contains methods for watershed algorhitm.
	class watershed
	{
	public:
		
		// Watershed algorhitm.
		static void watershed_alg(Mat frame, Mat& result);
	};
}


