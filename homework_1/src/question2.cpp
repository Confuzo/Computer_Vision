#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Mat sobel(Mat& image);
Mat gauss(Mat& image, Mat& sobel);

int main(){

    Mat image = imread("data/image.jpeg", IMREAD_GRAYSCALE);
    Mat sobel_img = sobel(image);
    
    
    Mat aux = imread("data/image.jpeg");

    Mat dst = gauss(aux, sobel_img);

    image.release();
    sobel_img.release();
    aux.release();

   
    imshow("data/dst.jpeg", dst);
    waitKey(0);

    return 0;
}

Mat sobel(Mat &image){
    Mat dst = Mat::zeros(image.size(), image.type());

    int x_mask [3][3] = {{-1,0,1},
                        {-2,0,2},
                        {-1,0,1}};

    int y_mask [3][3] = {{-1, -2, -1},
                         {0, 0, 0}, 
                         {1, 2, 1}};
    
    int x_der[3] = {0, 0, 0};
    int y_der[3] = {0, 0, 0};
    int gradient_mag[3] = {0, 0, 0};
    int normalize = 8;

    for(int x = 1; x < image.rows -1; x++){
        for(int y = 1; y < image.cols - 1; y++){
            for(int a = 0; a < 3; a++){
                for(int b = 0; b < 3; b++){
                    for(int i = 0; i < 3; i++){
                        x_der[i] += image.at<Vec3b>(x + a - 1, y + b - 1)[i] * x_mask[a][b];
                        y_der[i] += image.at<Vec3b>(x + a - 1, y + b - 1)[i] * y_mask[a][b];
                    }
                }
            }
            for(int j = 0; j < 3; j++){
                gradient_mag[j] = ((int) sqrt(pow(x_der[j],2) + pow(y_der[j],2)))/normalize;
                if (gradient_mag[j] > 255 or gradient_mag[j] >= 50){
                    gradient_mag[j] = 255;
                } else {
                    gradient_mag[j] = 0;
                }
            }
            for(int k = 0; k < 3; k++){
                dst.at<Vec3b>(x,y)[k] = gradient_mag[k];
                gradient_mag[k] = 0;
                x_der[k] = 0;
                y_der[k] = 0;
            }

        }
        
    }

    return dst;
}

Mat gauss(Mat &image, Mat &sobel){
    Mat dst = Mat::zeros(image.size(), image.type());

    int gauss_mask [3][3] = {{1,2,1},
                        {2,4,2},
                        {1,2,1}};
    int gauss_mask_stronger [3][3] = {{2, 4, 2}, 
                             {4, 8, 4}, 
                             {2, 4, 2}};
    int normalize = 16;
    
    int rgb[3] = {0,0,0};
    for(int x = 1; x < image.rows -1; x++){
        for(int y = 1; y < image.cols - 1; y++){
            for(int a = 0; a < 3; a++){
                for(int b = 0; b < 3; b++){
                    for(int i = 0; i < 3; i++){
                        if(sobel.at<Vec3b>(x + a - 1, y + b - 1)[i] == 255){
                            rgb[i] += (image.at<Vec3b>(x + a - 1, y + b - 1)[i] * gauss_mask[a][b])/normalize;
                         } else {
                            rgb[i] += (image.at<Vec3b>(x + a - 1, y + b - 1)[i] * gauss_mask[a][b] * 2)/(normalize*2);
                        }
                    }
                }
            }
           
            for(int k = 0; k < 3; k++){
                dst.at<Vec3b>(x,y)[k] = rgb[k];
                rgb[k] = 0;
            }

        }
        
    }

    return dst;
}
