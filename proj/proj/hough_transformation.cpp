#include "hough_transformation.h"

namespace ADAS
{
	// Contaions lines for the source image.
	vector<Vec4i> hough_transformation::lines;

	void hough_transformation::line_transformation(Mat image, Mat& result)
	{
		HoughLinesP(image, lines, 1, CV_PI / 180, 500, 10, 200);

		for (size_t i = 0; i < lines.size(); i++)
		{
			Vec4i l = lines[i];
			line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
		}
	}

	vector<Vec4i> hough_transformation::get_lines()
	{
		return this->lines;
	}
}
