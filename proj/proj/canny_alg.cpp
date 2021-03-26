#include "canny_alg.h"

namespace MyProject
{
    canny_alg::canny_alg(int _low_threashold, int _kernel_size) : low_threshold(_low_threashold), kernel_size(_kernel_size)
    {}

    void canny_alg::canny_algorithm(Mat frame, Mat& detected_edges)
    {
        Mat gray;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, detected_edges, Size(5, 5), 0);
        Canny(detected_edges, detected_edges, low_threshold, low_threshold * 3, kernel_size);
        imshow("canny", detected_edges);
    }

}
