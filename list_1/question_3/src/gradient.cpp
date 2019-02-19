#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(){

    int rows  = 400, cols = 400;
    Mat a(rows, cols, CV_8S);

    double alpha  = 0.6375;

    std::cout << alpha << std::endl;
    for(int i = 0; i < 400; i++){
        for(int j =0; j < 400; j++){
            a.at<uchar>(i, j) = alpha;
        }
        std::cout << alpha << std::endl;
        alpha += 0.6375;
    }

    imshow("linear gradient", a);
    waitKey(0);
}