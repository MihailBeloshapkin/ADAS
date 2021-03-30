#include "process.h"

namespace adas
{
	// Apply detection to the image.
	void process::run(cv::Mat image)
	{
		filters current_filter(1, 3);
		current_filter.binary_filter(image, image, 170, 170, 170);
		current_filter.canny_algorithm(image, image);
		vector<Vec4i> lines = hough_transformation::get_lines(image);
		vector<Vec4i> correct_lines = line_transfer::sort_by_tan(lines, 0.2);
		Mat result;
		image.copyTo(result);
		for (int iter = 0; iter < correct_lines.size(); iter++)
		{
			Vec4i l = correct_lines[iter];
			cv::line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
		}
		imshow("result", result);
	}

	// Apply detection to the video.
	void process::run(cv::VideoCapture capture)
	{

	}

	// Apply detection to the set of images.
	void process::run(std::vector<cv::Mat> set_of_images)
	{
		for (int i = 0; i < set_of_images.size(); i++)
		{
			process::run(set_of_images[i]);
		}
	}
}
