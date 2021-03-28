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
	template <class T>
	class process
	{
	private:
		T data;
		cv::VideoCapture capture;
		cv::Mat img;
	public:
		process(T data);

		// Start the process
		
		void run();
	};
}

