#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv ){
    if(argc < 2){
        std::cout << "Invalid output\n";
        return -1;
    }

    Mat image = imread(argv[1]);
    if( !image.data){
        std::cout << "No image data\n";
    }

    Mat bgr [3];
    split(image, bgr);

    //namedWindow("Image", WINDOW_AUTOSIZE);
    imshow("Image", image);;

    //namedWindow("Blue", WINDOW_AUTOSIZE );
    imshow("Blue", bgr[0]);

    //namedWindow("Green", WINDOW_AUTOSIZE );
    imshow("Green", bgr[1]);

    //namedWindow("Red", WINDOW_AUTOSIZE );
    imshow("Red", bgr[2]);

    waitKey(0);

    return 0;
}
