#include "canny_alg.h"

namespace MyProject
{
    static const int lowThreshold = 0;
    static const int max_lowThreshold = 100;
    static const int ratio = 3;
    static const int kernel_size = 3;

    void canny_alg::canny_algorithm(Mat frame, Mat detected_edges)
    {
        Mat gray;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        imshow("gray", gray);
        GaussianBlur(gray, detected_edges, Size(5, 5), 0);
        Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, kernel_size);
        imshow("canny", detected_edges);
    }

}
