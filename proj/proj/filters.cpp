#include <opencv2/core/core.hpp>
#include "filters.h"

using namespace cv;

namespace adas
{
    filters::filters(int _low_threashold, int _kernel_size) : low_threshold(_low_threashold), kernel_size(_kernel_size)
    {}

    // Special filter.
    void filters::binary_filter(Mat frame, Mat& result, unsigned char border_r, unsigned char border_g, unsigned char border_b)
    {
        frame.copyTo(result);

        for (int y = 0; y < result.rows; y++)
        {
            for (int x = 0; x < result.cols; x++)
            {
                int rgb[3];
                rgb[0] = static_cast<int>(result.at<Vec3b>(y, x)[0]);
                rgb[1] = static_cast<int>(result.at<Vec3b>(y, x)[1]);
                rgb[2] = static_cast<int>(result.at<Vec3b>(y, x)[2]);

                if (rgb[0] > border_r && rgb[1] > border_g && rgb[2] > border_b && y > frame.rows / 2)
                {
                    result.at<Vec3b>(y, x)[0] = 255;
                    result.at<Vec3b>(y, x)[1] = 255;
                    result.at<Vec3b>(y, x)[2] = 255;
                }
                else
                {
                    result.at<Vec3b>(y, x)[0] = 0;
                    result.at<Vec3b>(y, x)[1] = 0;
                    result.at<Vec3b>(y, x)[2] = 0;
                }
            }
        }
    }

    // Canny.
    void filters::canny_algorithm(Mat frame, Mat& detected_edges)
    {
        Mat gray;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, detected_edges, Size(5, 5), 0);
        Canny(detected_edges, detected_edges, low_threshold, low_threshold * 3, kernel_size);
        imshow("canny", detected_edges);
    }

}
