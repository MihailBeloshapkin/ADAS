#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include "filters.h"
#include "line_transfer.h"
#include "hough_transformation.h"

using namespace cv;


namespace adas
{
	class process
	{
	private:
	public:
		// Apply detection to the image.
		static void run(cv::Mat image);

		// Apply detection to the video.
		static void run(cv::VideoCapture capture);


		// Apply detection to the set of images.
		static void run(std::vector<cv::Mat> set_of_images);
	};
}

