#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;

namespace MyProject
{
	// This class contains methods to move lines on the image.
	class line_transfer
	{
	public:
		// This method applies parallel transfer of the image. 
		static void shift_line_down(cv::Vec4i& line);
	};
}

