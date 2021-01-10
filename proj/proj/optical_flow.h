#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>



namespace MyProject
{
	class optical_flow
	{
	public:
		static void optical_flow_alg(cv::VideoCapture capture);
	};

}

