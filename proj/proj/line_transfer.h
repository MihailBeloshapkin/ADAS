#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

namespace ADAS
{
	// This class contains methods to move lines on the image.
	class line_transfer
	{
	public:
		// This method applies parallel transfer of the image. 
		static void shift_line_down(cv::Vec4i& line);

		// Calculate tan.
		static float tan(Vec4i line);

		// Sort vector of lines by tangens.
		static vector<Vec4i> sort_by_tan(vector<Vec4i> lines, float tan);
	};
}

