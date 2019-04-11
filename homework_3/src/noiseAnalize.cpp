#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;

Mat aritmetic(Mat & image, int m, int n);
Mat geometric(Mat & image, int m, int n);

int main()
{

    Mat ibirapuera = imread("data2/ibirapuera.jpg");
    Mat ruidoGaussiano = imread("data2/ruidoGaussiano.jpg");
    Mat ruidoGaussianoSalPimenta = imread("data2/ruidoGaussianoSalPimenta.jpg");
    Mat ruidoPimenta = imread("data2/ruidoPimenta.jpg");
    Mat ruidoSal = imread("data2/ruidoSal.jpg");
    Mat ruidoSalPimenta = imread("data2/ruidoSalPimenta.jpg");

    imwrite("teste.jpg", aritmetic(ruidoSalPimenta,3,3));
    imwrite("teste1.jpg", geometric(ruidoSalPimenta,3,3));
    waitKey(0);

    return 0;
}

Mat aritmetic(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    int sum_border[3] =  {0,0,0};
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    for(int i = 0; i < 3; i++){
                        sum_border[i] += image.at<Vec3b>(x + a - 1, y + b - 1)[i];
                    }
                }
            }
            for(int i(0); i < 3; i++){
                dst.at<Vec3b>(x,y)[i] = (int)(sum_border[i]/factor);
                sum_border[i] = 0;
            }
            

        }
    }
    return dst;
}

Mat geometric(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    double prod_border[3] =  {1,1,1};
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    for(int i = 0; i < 3; i++){
                        prod_border[i] *= image.at<Vec3b>(x + a - 1, y + b - 1)[i];
                    }
                }
            }
            for(int i(0); i < 3; i++){
                dst.at<Vec3b>(x,y)[i] = (int) pow(prod_border[i],(1.0/factor));
                prod_border[i] = 1;
            }
            

        }
    }
    return dst;
}

