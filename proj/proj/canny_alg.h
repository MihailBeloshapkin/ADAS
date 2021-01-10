#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

using namespace cv;

namespace MyProject
{
    //Canny algorithm class.
    class canny_alg
    {
    private:
        //   canny_alg() {}

        static const int lowThreshold = 0;
        static const int max_lowThreshold = 100;
        static const int ratio = 3;
        static const int kernel_size = 3;

    public:
        static void canny_algorithm(Mat frame, Mat detected_edges);

    
    };

}

