#ifndef _HUFFMAN_
#define _HUFFMAN_
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <vector>
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
        Mat img;

        void readFile(){
            img = imread(in_name, 1);
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
            //printTree(root);
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
        }

        void encondingSave(){
            out_name = "binary.bin";
            std::ofstream output(out_name, std::ios::binary);

            std::string header, size_image, code;
            std::stringstream ss;
            unsigned long n;
            int aux;

            std::vector<char> codes_char;

            for(int i = 0; i < code_nodes.size(); i++){
                if(code_nodes[i]-> value >= 0){
                    std::cout << (int)code_nodes[i]->value << " " << code_nodes[i]->code << std::endl;
                    std::bitset<8> first(code_nodes[i]->value);
                    n = first.to_ulong();
                    output.write( reinterpret_cast<const char*>(&n), sizeof(n) );

                    header = code_nodes[i]->code;
                    for(int j = 0; j < header.size(); j++){
                        std::bitset<1> codes(header[j]);
                        n = codes.to_ulong();
                        output.write( reinterpret_cast<const char*>(&n), sizeof(n));
                    }

                    //8192
                    std::bitset<14> space("10000000000000");
                    n = space.to_ulong();
                    output.write( reinterpret_cast<const char*>(&n), sizeof(n));
                }
            }

            //8193
            std::bitset<14> end_codes("10000000000001");
            n = end_codes.to_ulong();
            output.write( reinterpret_cast<const char*>(&n), sizeof(n));

            ss << img.rows;
            size_image =  ss.str();
            std::bitset<12> image_rows(img.rows);
            n = image_rows.to_ulong();
            output.write( reinterpret_cast<const char*>(&n), sizeof(n));

            std::bitset<14> space("10000000000000");
            n = space.to_ulong();
            output.write( reinterpret_cast<const char*>(&n), sizeof(n));

            ss << img.cols;
            size_image =  ss.str();
            std::bitset<12> image_cols(img.cols);
            n = image_cols.to_ulong();
            output.write( reinterpret_cast<const char*>(&n), sizeof(n));

            //8194
            std::bitset<14> end_header("10000000000010");
            n = end_codes.to_ulong();
            output.write( reinterpret_cast<const char*>(&n), sizeof(n));

            for (int x = 0; x < img.rows; x++){
                for(int y = 0; y < img.cols; y++){
                    aux = (int) img.at<uchar>(x,y);
                    code =  array[aux]->code;
                    for(int i = 0; i < code.size(); i++){
                        codes_char.push_back(code[i]);
                    }
                }
            }

            
            code = "";
            for(int i = 0; i < codes_char.size(); i++){
                code += codes_char[i];
                if(code.size() == 8){
                    std::bitset<8> first(code);
                    n = first.to_ulong();
                    output.write( reinterpret_cast<const char*>(&n), sizeof(n));
                    code = "";
                }
            }
            
        }
};
#endif