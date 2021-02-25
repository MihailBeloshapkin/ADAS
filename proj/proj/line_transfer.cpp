#include "line_transfer.h"

namespace MyProject
{
    // This method applies parallel transfer of the image.
	void line_transfer::shift_line_down(cv::Vec4i& line)
	{
        Vec2f motion_vector;
        motion_vector[0] = line[2] - line[0];
        motion_vector[1] = line[3] - line[1];

        float length = sqrt(motion_vector[0] * motion_vector[0] + motion_vector[1] * motion_vector[1]);
        motion_vector[0] /= length;
        motion_vector[1] /= length;
        if (motion_vector[1] < 0)
        {
            motion_vector[0] *= -1;
            motion_vector[1] *= -1;
        }

        line[0] += (int)(motion_vector[0] * 70);
        line[2] += (int)(motion_vector[0] * 70);
        line[1] += (int)(motion_vector[1] * 70);
        line[3] += (int)(motion_vector[1] * 70);
	}

    bool line_transfer::is_intersection(cv::Vec4i lines)
    {
        return true;
    }
}
