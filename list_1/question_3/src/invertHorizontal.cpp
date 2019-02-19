#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv){

    if(argc < 2){
        std::cout << "Invalid output\n";
        return -1;
    }

    Mat image = imread(argv[1]);
    if( !image.data){
        std::cout << "No image data\n";
    }

    imshow("Normal image", image);
    flip(image, image, 1);

    imshow("Flipped image", image);

    waitKey(0);
    return 0;
}