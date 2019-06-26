#include "../include/hough.hpp"

int main(int argc, char *argv[]){
    
    Hough * h  = new Hough(argv[1], std::stoi(argv[2]));
    return 0;
}
