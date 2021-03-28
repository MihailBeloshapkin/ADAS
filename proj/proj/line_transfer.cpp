#include <math.h>
#include "line_transfer.h"

namespace adas
{
    // Shif line in correct direction.
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

    // Calculate tangens.
    float line_transfer::tan(Vec4i line)
    {
        return (float)(line[1] - line[3]) / (float)(line[2] - line[0]);
    }

    // Sort vector of lines by tangens.
    vector<Vec4i> line_transfer::sort_by_tan(vector<Vec4i> lines, float tan)
    {
        vector<Vec4i> result;

        for (int iter = 0; iter < lines.size(); iter++)
        {
            auto current_tan = line_transfer::tan(lines[iter]);
            if (current_tan > abs(tan) && current_tan < -abs(tan))
            {
                result.push_back(lines[iter]);
            }
            
        }

        return result;
    }
}
