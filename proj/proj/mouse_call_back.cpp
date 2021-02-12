#include "mouse_call_back.h"

namespace MyProject
{
	static cv::Mat src;

	mouse_call_back::mouse_call_back(cv::Mat frame)
	{
		frame.copyTo(src);
	}

	// right and left button reaction. 
	// left: cpprdinates of the clicked poiint on the image.
    // right: rgb values.
	void mouse_call_back::mouse_call_back_function(int event, int x, int y, int flags, void* userdata)
	{
        switch (event)
        {
        case EVENT_LBUTTONDOWN:
            cout << "Left button pressed on position:" << x << " " << y << std::endl;
            break;
        case EVENT_RBUTTONDOWN:
            int rgb[3];
            rgb[0] = static_cast<int>(src.at<Vec3b>(y, x)[0]);
            rgb[1] = static_cast<int>(src.at<Vec3b>(y, x)[1]);
            rgb[2] = static_cast<int>(src.at<Vec3b>(y, x)[2]);
            std::cout << "R " << rgb[0]
                << ";G " << rgb[1]
                << ";B " << rgb[2] << endl;
            if (rgb[0] > 170 && rgb[1] > 170 && rgb[2] > 170)
            {
                cout << "snow" << endl;
            }
            else
            {
                cout << "road" << endl;
            }
            break;
        default:
            break;
        }
	}
	
}