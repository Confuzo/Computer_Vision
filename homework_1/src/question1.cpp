#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
void bright_(Mat & image);
void black_strips(Mat & image, int division = 3);
void drawLine(Mat & image, int start, int end);

int main(){

    Mat image = imread("data/lena.png", IMREAD_GRAYSCALE);
    bright_(image);
    black_strips(image);

    imshow("image with vertical lines", image);

    waitKey(0);
}

/**
 * Increases the bright of a image 
 * @param Mat & image
 * */
void bright_(Mat & image){
    
    int alpha = 1.9, value;
    for (int x = 0; x < image.rows; x++){
        for (int y = 0; y < image.cols; y++){
            for (int a = 0; a < 3; a++){
                value = image.at<Vec3b>(x,y)[a] * alpha;
                if(value > 255){
                    value =  255;
                }
                image.at<Vec3b>(x,y)[a] = value;
            }
        }
    }

}

/**
 * Draws verticals lines in the image
 * @param Mat & image 
 * @param int division
*/
void black_strips(Mat & image, int division){
    int cont = 0;
    bool strip = true;
    for (int y = 0; y < image.cols; y++){
        
        cont++;
        if(strip){
            line(image, Point(y, 0), Point(y, image.rows -1 ), Scalar(0,0,0), 2, 4, 0);
        }

        if(cont == division){
            cont= 0;
            strip = !strip;
        }
    }
}

