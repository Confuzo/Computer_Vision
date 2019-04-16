#include "noiseReduction.hpp"

int main()
{

    Mat ibirapuera = imread("data2/ibirapuera.jpg");
    Mat ruidoGaussiano = imread("data2/ruidoGaussiano.jpg");
    Mat ruidoGaussianoSalPimenta = imread("data2/ruidoGaussianoSalPimenta.jpg");
    Mat ruidoPimenta = imread("data2/ruidoPimenta.jpg");
    Mat ruidoSal = imread("data2/ruidoSal.jpg");
    Mat ruidoSalPimenta = imread("data2/ruidoSalPimenta.jpg");

    //imshow("teste", aritmetic(ruidoSalPimenta,5,5));
    //imshow("teste1", geometric(ruidoSalPimenta,3,3));
    Mat dst = contraharmonic(ruidoPimenta, 3, 3, 2);
    imshow("teste1", ruidoPimenta);
    imshow("teste2", dst);
    
    std::cout<< rmse(ruidoPimenta, dst, 3) << std::endl;
    
    waitKey(0);

    return 0;
}