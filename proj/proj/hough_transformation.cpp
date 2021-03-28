#include "hough_transformation.h"

namespace adas
{
	void hough_transformation::apply_line_transformation(Mat image, Mat& result)
	{
		vector<Vec4i> lines;
		HoughLinesP(image, lines, 1, CV_PI / 180, 500, 10, 200);

		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
		}
	}

	std::vector<cv::Vec4i> hough_transformation::get_lines(cv::Mat image)
	{
		vector<Vec4i> lines;
		HoughLinesP(image, lines, 1, CV_PI / 180, 500, 10, 200);
		return lines;
	}
}
