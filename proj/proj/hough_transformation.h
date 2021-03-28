#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

//This class contaion Huogh kine transformation.
namespace adas
{
	class hough_transformation
	{
	public:
		// apply hough tramsformation to the image.
		static void apply_line_transformation(Mat image, Mat& result);

		// get lines.
		static std::vector<cv::Vec4i> get_lines(cv::Mat image);
	};
}

