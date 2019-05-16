#ifndef _HUFFMAN_
#define _HUFFMAN_
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <opencv2/opencv.hpp>

struct Node_V{
    char value;
    int frequency;
    std::string code;
    Node_V * left;
    Node_V * right;
    Node_V(){
        left = NULL;
        right = NULL;
    }
};

typedef Node_V* ptr;
using namespace cv;

class Huffman{

    private:
        //array for all the 256 pixel values
        Node_V * array[256];
        Node_V * root;
        std::vector<Node_V *> code_nodes;
        std::string in_name, out_name;
        class Compare{
            public:
                bool operator()(const ptr& a, const ptr& b) const{
                    return a->frequency > b->frequency;
                }
        };
        std::priority_queue< Node_V*, std::vector<Node_V*>, Compare> pq;

        void readFile(){
            Mat img = imread(in_name, 1);
            int aux;
            if(!img.empty()){
                for (int x = 0; x < img.rows; x++){
                    for(int y = 0; y < img.cols; y++){
                        aux = (int) img.at<uchar>(x,y);
                        array[aux]->frequency++;
                    }
                }
            } 
        }

        void printTree(){
            for(int i = 0; i < 256; i++){
                std::cout << array[i]->value << " " << array[i]->frequency << std::endl;
            }
        }
    public:
        Huffman(std::string file_in, std::string file_out){
            in_name = file_in;
            out_name = file_out;

            for (int i = 0; i < 256; i++){
                array[i] = new Node_V;
                array[i]->value = i;
                array[i]->frequency = 0;
            }

        }
        void createTree(){
            createPQ();
            std::priority_queue< Node_V*, std::vector<Node_V*>, Compare> aux(pq);
            while(aux.size() > 1){
                root = new Node_V;
                root->frequency = 0;
                root->left = aux.top();
                root->frequency += aux.top()->frequency;
                aux.pop();
                root->right = aux.top();
                root->frequency += aux.top()->frequency;
                aux.pop();
                aux.push(root);
            }

            codify(root, "");
            printTree(root);
        }

        void createPQ(){
            readFile();
            for(auto i = 0; i < 256; i++){
                if(array[i]->frequency){
                    pq.push(array[i]);
                }
            }
        }

        void codify(Node_V * node, std::string code){
            if(node->left == nullptr and node->right == nullptr){
                node->code = code;
                code_nodes.push_back(node);
            } else{
                codify(node->left, code + '0');
                codify(node->right, code + '1');
            }
        }

        void printTree(Node_V * node){
            if(node->left != nullptr){
                printTree(node->left);
            }
            if(node->right != nullptr){
                printTree(node->right);
            }
            std::cout << node->value << " " << node->frequency << " " << node->code<< std::endl;
            //std::cout << node->value << " " << node->frequency << std::endl;
        }
};
#endif