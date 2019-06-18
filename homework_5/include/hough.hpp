#ifndef _HOUGH_
#define _HOUGH_
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
class Hough{

public:

    Hough(std::string filename){
        Mat img = imread(filename, 0);
        straight(img);
    }

private:

    void straight(Mat & img){
        Mat src = img;
        blur( src, src, Size(3,3) );
        adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,13,4);
        Canny(src, src, 127, 255, 3);
        for(int x = 0; x < src.rows; x++){
            for(int y = 0; y < src.cols; y++){
                
            }
        }
        imshow("teste", src);
        waitKey(0);
    }
};

#endif