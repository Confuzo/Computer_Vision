#ifndef _HOUGH_
#define _HOUGH_
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
class Hough{

public:
    Mat img;

    Hough(std::string filename, int c){
        img = imread(filename);
        coeficient = c;
        detectLines();
    }

private:

    int coeficient;
    void detectLines(){
        Mat src = img.clone();
        cvtColor(src, src, cv::COLOR_RGB2GRAY);
        blur( src, src, Size(3,3) );
        //adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,13,4);
        Canny(src, src, 50, 150, 3);
        //imshow("teste1", src);
        int diag = hypot(src.rows, src.cols);
        int rho, theta;

        std::vector<std::vector<int>> votes(2 * diag, std::vector<int>(180, 0));
        for(int x = 0; x < src.rows; x++){
            for(int y = 0; y < src.cols; y++){
                if(src.at<uchar>(x,y) == 255){
                    for(theta = 0; theta <= 180; theta++){
                        int rho = round(x * cos(theta - 90) + y * sin(theta - 90)) + diag;
                        votes[rho][theta]++;               
                    }
                }
            }
        }

        drawLines(votes, diag);

        imshow("lines drawned", img);
        waitKey();
    }

    void drawLines(std::vector<std::vector<int>> & votes, int const & diag){
        
        int rho, theta;
        for(int i = 0; i < votes.size(); i++){
            for(int k = 0; k < votes[i].size(); ++k){
                if(votes[i][k] > coeficient){

                    rho = i - diag;
                    theta = k - 90;

                    Point p1, p2;   
                    
                    int x0 = abs(cvRound(rho * cos(theta)));
                    int y0 = abs(cvRound(rho * sin(theta)));
                    
                    p1.x = cvRound(x0 + 1000 * (-sin(theta)));
	                p1.y = cvRound(y0 + 1000 * (cos(theta)));

	                p2.x = cvRound(x0 - 1000 * (-sin(theta)));
	                p2.y = cvRound(y0 - 1000 * (cos(theta)));

                    line(img, p1, p2, Scalar(0, 0, 255));
                }
                
            }
        }
    }
};

#endif