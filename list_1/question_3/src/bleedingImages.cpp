#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv){

    if(argc < 3){
        std::cout << "Invalid output\n";
        return -1;
    }

    Mat image1 = imread(argv[1]);
    Mat image2 = imread(argv[2]);
    Mat dst;
    if( !image1.data or !image2.data){
        std::cout << "No image data\n";
        return -1;
    }

    if(image1.rows == image2.rows and image1.cols == image2.cols){
        addWeighted(image1, 0.5, image2, 0.5, 0, dst);
    }
    
    imshow( "Linear Blend", dst );
    
    waitKey(0);
    
    return 0;
}