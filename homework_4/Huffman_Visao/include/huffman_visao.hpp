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
        os_ << p.value << "\n" << p.code << std::endl;
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
            img = imread(in_name, 0);
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
            out_name = "header.txt";
            std::ofstream output(out_name);

            int aux;
            output << img.rows << std::endl;
            output << img.cols << std::endl;
            for(int i = 0; i < code_nodes.size(); i++){
                output << *code_nodes[i];
            }

            output.close();

            std::ofstream archive("file.txt");
            //std::string code_ = "";
            
            for(int x = 0; x < img.rows; x++){
                for(int y = 0; y < img.cols; y++){
                    aux = img.at<uchar>(x,y);
                    for(int i = 0; i < code_nodes.size(); i++){
                        if(code_nodes[i]->value == aux){
                            archive << (code_nodes[i]->code);
                            i = code_nodes.size();
                        }
                    }
                }
            }

            /*for(int x = 0; x < img.rows; x++){
                for(int y = 0; y < img.cols; y++){
                    aux = img.at<uchar>(x,y);
                    for(int i = 0; i < code_nodes.size(); i++){
                        if(code_nodes[i]->value == aux){
                            code_ += (code_nodes[i]->code);
                            i = code_nodes.size();
                        }
                    }
                }
            }
            
            std::cout << code_ << std::endl;
            std::bitset<8> value;
            while(code_.size() > 0){
                if(code_.size() >= 8){
                    for(int i = 0; i < 8; i++){
                        if(code_[i] == '1'){
                            value[i] = false;
                        } else {
                            value[i] = true;
                        }
                    }
                    aux = value.to_ulong();
                    char * ptr5 = (char *)&(aux);
                    archive.write(ptr5, sizeof(char));
                    code_.erase(0,8);
                    value.reset(); 
                } else {
                    for(int i = 0; i < code_.size(); i++){
                        value[i] = code_[i];
                    }
                    aux = value.to_ulong();
                    char * ptr6 = (char *)&(aux);
                    archive.write(ptr6, sizeof(char));
                    code_ = "";
                }
            }*/

            archive.close();
            
        }

        void decoding(){

            std::ifstream arq;
            arq.open(in_name);
            std::string line;
            int i = 0, k = 0;
            std::map<std::string , int> header;
            int values [2];
            int aux1;

            while(std::getline(arq, line)){
                if(k < 2){
                    values[k] = stoi(line);
                    k++;
                } else {
                    if(i == 0){
                        aux1 = stoi(line);
                        i++;
                    } else if (i == 1){
                        i = 0;
                        header[line] = aux1;
                    } 
                }
            }
            arq.close();
            
            std::ifstream out;
            out.open(out_name);
            std::string code = "";
            while(std::getline(out, line)){
                code += line;
            }

            /*out.open(out_name, std::ios::binary);
            out.seekg(0, out.end);
            out.seekg(0, out.beg);
            int buffer_;
            std::string code = "";
            while(!out.eof()){
                out.read((char *) &buffer_, 1);
                code += std::bitset<8>(buffer_).to_string();      
            }
            */

            Mat src = Mat::zeros(values[0], values[1], CV_8UC1);
            
            int val = 0;
            for(int x = 0; x < src.rows; x++){
                for(int y = 0; y < src.cols; y++){
                    val = search(code, header);
                    src.at<uchar>(x,y) = (char) val;
                }
            }

            imshow("teste", src);
            waitKey(0);
        }

        int search(std::string &code, std::map<std::string, int> header){
            int c = 1;
            int aux;
            for(int i = 1; i < code.size(); i++){
                if(header[code.substr(0,i)]){
                    aux = header.find(code.substr(0,i))->second;
                    code.erase(0,i);
                    return aux;
                }
            }
            return 0;
        }
};
#endif