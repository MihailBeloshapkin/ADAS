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
namespace ADAS
{
	class hough_transformation
	{
	private:
		static vector<Vec4i> lines;
	public:
		void line_transformation(Mat image, Mat& result);

		vector<Vec4i> get_lines();
	};
}

