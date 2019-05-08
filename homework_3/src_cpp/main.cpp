#include "noiseReduction.hpp"

int main()
{

    Mat ibirapuera = imread("data2/ibirapuera.jpg");
    Mat ruidoGaussiano = imread("data2/ruidoGaussiano.jpg");
    Mat ruidoGaussianoSalPimenta = imread("data2/ruidoGaussianoSalPimenta.jpg");
    Mat ruidoPimenta = imread("data2/ruidoPimenta.jpg");
    Mat ruidoSal = imread("data2/ruidoSal.jpg");
    Mat ruidoSalPimenta = imread("data2/ruidoSalPimenta.jpg");

    Mat dst[9]; 
    dst[0] = aritmetic(ruidoSalPimenta, 3, 3);
    imshow("teste1", dst[0]);
    dst[1] = geometric(ruidoSalPimenta, 3, 3);
    imshow("test2", dst[1]);
    dst[2] = harmonic(ruidoSalPimenta, 3, 3);
    imshow("teste3", dst[2]);
    dst[3] = contraharmonic(ruidoSalPimenta, 3, 3, 2);
    imshow("teste4", dst[3]);
    dst[4] = minpoint(ruidoSalPimenta, 3, 3);
    imshow("teste5", dst[4]);  
    dst[5] = maxpoint(ruidoSalPimenta, 3, 3);
    imshow("teste6", dst[5]);
    dst[6] = midpoint(ruidoSalPimenta, 3, 3);
    imshow("teste7", dst[6]);
    dst[7] = median(ruidoSalPimenta, 3, 3);
    imshow("test8", dst[7]);
    dst[8] = alphacut(ruidoSalPimenta, 3, 3, 2);
    imshow("teste9", dst[8]);

    double rmse_results[9];

    for(int i = 0; i < 9; i++){
        rmse_results[i] = rmse(dst[i], ibirapuera, 3);
        std::cout << rmse_results[i] << std::endl;
    
    }

    waitKey(0);

    return 0;
}