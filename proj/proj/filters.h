#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;

namespace ADAS
{
    //Canny algorithm class.
    class filters
    {
    private:
        const int low_threshold = 0;
        const int kernel_size = 3;

    public:
        filters(int _low_threashold, int _kernel_size);

        // Canny.
        void canny_algorithm(Mat frame, Mat& detected_edges);

        // Special binary filter.
        void binary_filter(Mat frame, Mat& result, unsigned char border_r, unsigned char border_g, unsigned char border_b);
    };

}

