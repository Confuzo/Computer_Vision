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

    imwrite("teste.jpg", image);

    waitKey(0);
}

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

void black_strips(Mat & image, int division){
    int cont = 0;
    bool strip = true;
    for (int y = 0; y < image.cols; y++){
        
        cont++;
        if(strip){
            //line(image, Point(y, 0), Point(y, image.rows -1 ), Scalar(0,0,0), 2, 4, 0);
            drawLine(image, y , image.rows-1);
        }

        if(cont == division){
            cont= 0;
            strip = !strip;
        }
        /*++cont;
        if(strip){
            for(int x = 0; x < image.rows; x++){
                for(int a = 0; a < 3; a++){
                    image.at<Vec3b>(y, x)[a] = 0;
                }
            //std::cout << x << " " << y << " " << cont << std::endl;
            }
        }
        if (cont == division){
            if(strip){
                strip = false;
            } else {
                strip = true;
            }
            cont = 0;
        }*/
    }
}

void drawLine(Mat & image, int start, int end){
    for(int i = 0; i < end; i++){
        for(int a = 0; a< 3; a++){
            image.at<Vec3b>(i, start)[a] = 0;
        }
    }
}