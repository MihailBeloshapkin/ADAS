#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace std;

class process
{
private:
	cv::VideoCapture capture;
public:
	process(cv::VideoCapture capture);

	// Run the process
	void run();

	// Show filters.
	void get_filters();

	// Get points.
	vector<cv::Vec2i> get_points();

	// Get lines.
	vector<cv::Vec4i> get_lines();
};

