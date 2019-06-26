#include "../include/hough.hpp"
#include "../include/hough_circ.hpp"

int main(int argc, char *argv[]){
    
    int choice = std::stoi(argv[1]);
    if(choice == 1){
        Hough * h  = new Hough(argv[2], std::stoi(argv[3]));
    } else {
        Hough_circ * h = new Hough_circ(argv[2], std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
    }
    return 0;
}
