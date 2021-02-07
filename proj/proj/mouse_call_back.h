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
	// This class contains mouse call back function to react on the mouse clicks.
	class mouse_call_back
	{
	private:
		cv::Mat src;

	public:
		mouse_call_back(cv::Mat frame);

		// right and left button reaction. 
		// left: cpprdinates of the clicked poiint on the image.
		// right: rgb values.
		void mouse_call_back_function(int event, int x, int y, int flags, void* userdata);
	};
}

