#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace cv;

Mat aritmetic(Mat & image, int m, int n);
Mat geometric(Mat & image, int m, int n);
Mat harmonic(Mat & image, int m, int n);
Mat contraharmonic(Mat & image, int m, int n, int order);
Mat minpoint(Mat & image, int m, int n);
Mat maxpoint(Mat & image, int m, int n);
Mat midpoint(Mat & image, int m, int n);
Mat median(Mat & image, int m, int n);
Vec3b minfunc(std::deque<Vec3b>);
Vec3b maxfunc(std::deque<Vec3b>);
bool isMin(Vec3b a, Vec3b b);
Mat alphacut(Mat & image, int m, int n, int d);
double rmse(Mat & image1, Mat & image2, int m);

Mat aritmetic(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    //int sum_border[3] =  {0,0,0};
    int sum_border;
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    /*for(int i = 0; i < 3; i++){
                        sum_border[i] += image.at<Vec3b>(x + a - 1, y + b - 1)[i];
                    }*/
                    sum_border += image.at<Vec3b>(x + a - 1, y + b - 1)[0];
                }
            }
            for(int i(0); i < 3; i++){
                dst.at<Vec3b>(x,y)[i] = (int)(sum_border/factor);
            }
            sum_border = 0;
            

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

Mat harmonic(Mat & image, int m, int n){
    
    Mat dst = Mat::zeros(image.size(), image.type());

    double sum_border[3] =  {0.0,0.0,0.0};
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    for(int i = 0; i < 3; i++){
                        if(image.at<Vec3b>(x + a - 1, y + b -1)[1] == 0){
                            sum_border[i] += 0;
                        } else {
                            sum_border[i] += 1.0/(image.at<Vec3b>(x + a - 1, y + b - 1)[i]);
                        }
                    }
                }
            }
            for(int i(0); i < 3; i++){
                
                dst.at<Vec3b>(x,y)[i] = (int) (factor/sum_border[i]);
                sum_border[i] = 0;
            }
            

        }
    }
    return dst;
}

Mat contraharmonic(Mat & image, int m, int n, int order){

    Mat dst = Mat::zeros(image.size(), image.type());

    int numerator[3] =  {0,0,0};
    int denominator[3] = {0,0,0};
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    for(int i = 0; i < 3; i++){
                       numerator[i] += pow(image.at<Vec3b>(x + a - 1, y + b - 1)[i], order + 1);
                       denominator[i] += pow(image.at<Vec3b>(x + a - 1, y + b - 1)[i], order);
                    }
                }
            }
            for(int i(0); i < 3; i++){
                if(denominator[i] == 0){
                    dst.at<Vec3b>(x,y)[i] = 0;
                } else {
                    dst.at<Vec3b>(x,y)[i] = (int) (numerator[i]/denominator[i]);
                }
                numerator[i] = 0;
                denominator[i] = 0;
            }
            

        }
    }
    return dst;

}

Mat minpoint(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    std::deque<Vec3b> border;
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    border.push_back(image.at<Vec3b>(x + a - 1, y + b - 1));
                }
            }
            dst.at<Vec3b>(x,y) = minfunc(border);
            border.clear();
        }
    }
    return dst;
}

Mat maxpoint(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    std::deque<Vec3b> border;
    int factor = m*n;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    border.push_back(image.at<Vec3b>(x + a - 1, y + b - 1));
                }
            }
            dst.at<Vec3b>(x,y) = maxfunc(border);
            border.clear();
        }
    }
    return dst;
}

Mat midpoint(Mat & image, int m, int n){
    Mat dst = Mat::zeros(image.size(), image.type());

    std::deque<Vec3b> border;
    int factor = m*n;
    Vec3b aux, max, min;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    border.push_back(image.at<Vec3b>(x + a - 1, y + b - 1));
                }
            }

            max = maxfunc(border);
            min = minfunc(border);
            
            for(int i = 0; i < 3; i++){
                aux[i] = (max[i] + min[i])/2;
            }
            //std::cout << max << " " << min << " " << aux << std::endl;
            //dst.at<Vec3b>(x,y) =  ((maxfunc(border) + minfunc(border))/2);
            dst.at<Vec3b>(x,y) = aux;
            border.clear();
        }
    }
    return dst;
}

Mat median(Mat & image, int m, int n){

    Mat dst = Mat::zeros(image.size(), image.type());

    std::deque<Vec3b> border;
    int factor = m*n;

    Vec3b aux;

    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    border.push_back(image.at<Vec3b>(x + a - 1, y + b - 1));
                }
            }

            for(int l = 0; l < border.size() - 1; l++){
                for(int k = l + 1; k < border.size(); k++){
                    if(!isMin(border[l], border[k])){
                        aux = border[l];
                        border[l] = border[k];
                        border[k] = aux;
                    }
                }
            }

            /*std::copy( border.begin(), border.end(), std::ostream_iterator<Vec3b>( std::cout, " "));
            std::cout <<std::endl;
            std::cout << border[border.size()/2] << std::endl;*/
            dst.at<Vec3b>(x,y) = border[(border.size()/2)];
            border.clear();
            //return dst;
        }
    }
    return dst;
}

Vec3b minfunc(std::deque<Vec3b> deq){
    Vec3b min = *(deq.begin());
    for(auto it = deq.begin() + 1; it < deq.end(); it++){
       if(isMin(*it, min)){
           min = *it;
       }
    }
    return min;
}

Vec3b maxfunc(std::deque<Vec3b> deq){
    Vec3b max = *(deq.begin());
    for(auto it = deq.begin() + 1; it < deq.end(); it++){
       if(!isMin(*it, max)){
           max = *it;
       }
    }
    return max;
}

bool isMin(Vec3b a, Vec3b b){
    int sum_a = a[0] + a[1] + a[2];
    int sum_b = b[0] + b[1] + b[2];
    if(sum_a < sum_b){
        return true;
    }
    return false;
}

Mat alphacut(Mat & image, int m, int n, int d){
    
    Mat dst = Mat::zeros(image.size(), image.type());

    int sum_border[3] =  {0,0,0};
    std::deque<Vec3b> border;
    int factor = m*n;
    Vec3b aux;
    for(int x = m/2; x < image.rows - m/2; x++){
        for(int y = n/2; y < image.cols - n/2; y++){
            for(int a = 0; a < m; a++){
                for(int b = 0; b < n; b++){
                    /*for(int i = 0; i < 3; i++){
                        border[i] += image.at<Vec3b>(x + a - 1, y + b - 1)[i];
                    }*/
                    border.push_back(image.at<Vec3b>(x + a - 1, y + b - 1));
                }
            }
            
            for(int l = 0; l < border.size() - 1; l++){
                for(int k = l + 1; k < border.size(); k++){
                    if(!isMin(border[l], border[k])){
                        aux = border[l];
                        border[l] = border[k];
                        border[k] = aux;
                    }
                }
            }
            for(int i = d; i < border.size() - d; i++){
                for(int k = 0; k < 3; k++){
                    sum_border[k] += border[i][k];
                }
            }
            for(int i(0); i < 3; i++){
                dst.at<Vec3b>(x,y)[i] = (int)(sum_border[i]/(factor-d));
                sum_border[i] = 0;
            }
            border.clear();

        }
    }
    return dst;
}

double rmse(Mat & image1, Mat & image2, int m){

    double result = 0.0;
    for(int x = 0; x < image1.rows; x++){
        for(int y = 0; y < image1.cols; y++){
            result += pow((int)(image1.at<Vec3b>(x,y)[0] - image2.at<Vec3b>(x,y)[0]), 2);
        }
    }


    return sqrt(result/(m*m));
}