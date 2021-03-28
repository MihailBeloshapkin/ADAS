#include "process.h"

namespace adas
{
	template <class T>
	process<T>::process(T data)
	{
		this->data = data;
	}

	template <class T>
	void process<T>::run()
	{
		
			filters current_filter(1, 3);
			current_filter.binary_filter(data, data, 170, 170, 170);
			current_filter.canny_algorithm(data, data);
			vector<Vec4i> lines = hough_transformation::get_lines(data);
			vector<Vec4i> correct_lines = line_transfer::sort_by_tan(lines, 0.2);
			Mat result;
			data.copyTo(result);
			for (int iter = 0; iter < correct_lines.size(); iter++)
			{
				Vec4i l = correct_lines[iter];
				cv::line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 3, LINE_AA);
			}
			imshow("result", result);

		
	}
}
