#ifndef _HOUGH_CIRC_
#define _HOUGH_CIRC_
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
class Hough_circ{

public:
    Mat img;

    Hough_circ(std::string filename, int c, int rmin, int rmax){
        img = imread(filename);
        coeficient = c;
        radius_max = rmax;
        radius_min = rmin;
        detectCircles();
    }

private:

    int coeficient, radius_max = 0, radius_min = 0;
    void detectCircles(){
        Mat src = img.clone();
        cvtColor(src, src, cv::COLOR_RGB2GRAY);
        blur( src, src, Size(3,3) );
        //adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,13,4);
        Canny(src, src, 50, 150, 3);
        imshow("teste1", src);
        int diag = hypot(src.rows, src.cols);
        int rho, theta, a, b;

        std::vector<std::vector<std::vector<int>>> votes(src.rows, std::vector<std::vector<int>>(src.cols, std::vector<int>(radius_max, 0)));
        for(int x = radius_min; x < src.rows - radius_min; x++){
            for(int y = radius_min; y < src.cols - radius_min; y++){
                if(src.at<uchar>(x,y) == 255){
                    for(int r  = radius_min; r <= radius_max; r++){
                        for(theta = 0; theta <= 360; theta++){
                            a = x - r * cos((theta * M_PI) / 180);
                            b = y - r * sin((theta * M_PI) / 180);
                            if(a >= src.rows - radius_min || b >= src.cols -radius_min || a < 0 || b < 0){
                                continue;
                            }
                            votes[a][b][r] += 1;
                        }
                    }
                }
            }
        }

        drawCircles(votes, diag);

        imshow("lines drawned", img);
        waitKey();
    }

    void drawCircles(std::vector<std::vector<std::vector<int>>> & votes, int const & diag){
        
        for(int i = radius_min; i < votes.size(); i++){
            for(int j = radius_min; j < votes[i].size(); j++){
                for(int r = radius_min; r <= radius_max; r++){
                    if(votes[i][j][r] > coeficient){
                        Point p1;
                        p1.x = i;
                        p1.y = j;
                        circle(img, p1, r, Scalar(0, 0, 255));
                    }
                }
            }
        }


    }
};

#endif