#include "../include/huffman_visao.hpp"


int main(int argc, char const *argv[]){
    
    if(argc == 2){
        /*Mat img  = imread(argv[1], 0);
        imshow("teste", img);
        waitKey(0);*/

        Huffman h(argv[1]);
        h.createTree();
        h.encondingSave();
    } else if(argc == 3){
        Huffman h(argv[1], argv[2]);
        h.decoding();
    } else {

    }
    return 0;
}
