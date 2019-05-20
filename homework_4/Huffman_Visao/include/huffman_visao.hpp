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
#include <map>
#include <opencv2/opencv.hpp>

struct Node_V{
    int value;
    int frequency;
    std::string code;
    Node_V * left;
    Node_V * right;
    Node_V(){
        left = NULL;
        right = NULL;
    }

    friend std::ostream & operator<<( std::ostream& os_, const Node_V & p){
        os_ << p.value << " " << p.code << std::endl;
        return os_;
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
        Huffman(std::string file_in){
            in_name = file_in;
            out_name = "";

            for (int i = 0; i < 256; i++){
                array[i] = new Node_V;
                array[i]->value = i;
                array[i]->frequency = 0;
            }

        }

        Huffman(std::string file_in, std::string file_out){
            in_name = file_in;
            out_name = file_out;

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
            out_name = "binario.bin";
            std::ofstream output(out_name, std::ios::binary);

            int aux;
            char * ptr;

            for(int i = 0; i < code_nodes.size(); i++){
                //output << *code_nodes[i];
                ptr = (char *)&(code_nodes[i]->value);
                output.write(ptr, sizeof(int));
                
                std::bitset<16> code(code_nodes[i]->code);
                aux =  code.to_ulong();
                ptr = (char *)&(aux);
                output.write(ptr, sizeof(int)); 
                /*std::bitset<16> code(code_nodes[i]->code);
                output << static_cast<uint_fast16_t>(code.to_ulong());
            */
            }

            //output << img.rows << " " << img.cols << std::endl;
            output.close();

            /*std::ofstream arquivo("compactado.bin", std::ios::binary);
            
            for(int x = 0; x < img.rows; x++){
                for(int y = 0; y < img.cols; y++){
                    aux = img.at<uchar>(x,y);
                    for(int i = 0; i < code_nodes.size(); i++){
                        if(code_nodes[i]->value == aux){
                            code_ = (code_nodes[i]->code);
                            break;
                        }
                    }
                    std::bitset<16> value(code_);
                    arquivo << static_cast
                    /*if(code_.size() > 8){
                        for(int i = 0, k = 7; i < 8; i++, k--){
                            value[k] = code_[i];
                        }
                        code_.erase(0,8);
                        arquivo << static_cast<uint_fast8_t>(value.to_ulong());
                    }
                    std::bitset<8> rest(code_);
                    char *ptr = (char *)&code_;
                    arquivo.write(ptr, sizeof(int));
                    //arquivo << static_cast<uint_fast16_t>(value.to_ulong());
                }
            }*/

            //arquivo.close();
            
        }

        void decoding(){
            /*std::ifstream input(in_name, std::ifstream::in);
            std::string line;
            std::map<std::string, int> header;
            std::string values [2];
            int i;

            while(std::getline(input, line)){
                std::istringstream ss(line);

                do{ 
                    ss >> values[i];
                    i++; 
                } while (ss);

                i = 0;
                std::cout << values[0] << " " << values[1] << std::endl;
                std::bitset<8> convert(values[1]);
                header[values[0]] = convert.to_ulong();    
            }*/

            std::ifstream arq;
            arq.open(in_name, std::ios::binary);
            arq.seekg(0, arq.end);
            auto fileSize = arq.tellg();
            arq.seekg(0, arq.beg);
            //auto buffer = new char[fileSize];
            int buffer;
            int i = 0;
            while(!arq.eof()){
                arq.read((char *) &buffer, 4);
                std::cout << (int)buffer << " ";
                i++;
                if(i == 2){
                    i = 0;
                    std::cout << std::endl;
                }
            }

        }
};
#endif