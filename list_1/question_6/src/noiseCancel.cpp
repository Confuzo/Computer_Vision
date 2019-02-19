#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
int main(int argc, char** argv){

    Mat a[9];

    for(int i = 1; i <= 9; i++){
        std::cout << argv[i] << std::endl;
        a[i-1] = imread(argv[i]);
    }
    
    Mat aux(a[0].rows, a[0].cols, CV_8UC1);
    for(int x = 0; x < a[0].rows; x++){
        for(int y = 0; y < a[0].cols; y++){
            aux.at<uchar>(x,y) = 0;
            for(int k = 0; k < 9; k++){
                aux.at<uchar>(x,y) += a[k].at<uchar>(x, y);
            }
        }
    }

    for(int x = 0; x < a[0].rows; x++){
        for(int y = 0; y < a[0].cols; y++){
            aux.at<uchar>(x,y) /= 9;
        }
    }

    imshow("noise cancel", aux);
    waitKey(0);
}