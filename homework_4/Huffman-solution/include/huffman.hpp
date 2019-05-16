#ifndef _HUFFMAN_
#define _HUFFMAN_
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>

/**
 * Struct representando cada nó da árvore.
 */
struct Node{
    char value;
    int frequency;      // frequencia que aparece
    std::string code;   // representação
    Node * left;        // nó a esquerda
    Node * right;       // nó a direita
    Node(){             // construtor padrão da struct.
        left = NULL;
        right = NULL;
    }
};

// Aliás
typedef Node* ptr;

/**
 * Classe Huffman que realiza as ações da codificação e decodificação.
 */
class Huffman{

    private:
        //Array para todos os 128 caracteres.
        Node * array[128];
        // Nó raiz.
        Node * root;
        // Vetor com todos os códigos dos nós.
        std::vector<Node *> code_nodes;
        // Nomes dos arquivos de entrada e saída informados pelo usuário.
        std::string in_name, out_name;
        // Classe comparadora entre dois nós.
        class Compare{
            public:
                bool operator()(const ptr& a, const ptr& b) const{
                    return a->frequency > b->frequency;
                }
        };
        // Lista de prioridade para os nós.
        std::priority_queue< Node*, std::vector<Node*>, Compare> pq;
        
        // Método que realiza a leitura do arquivo de entrada e cria a lista de prioridades.
        void readFile(){
            // Abre o arquivo.
            std::fstream reader(in_name, std::fstream::in);
            std::string line;
            char c;
            int pos;
            // Percorre o arquivo e realiza uma análise da frequência dele.
            while(reader.get(c)){
                pos = c;
                array[pos]->frequency++;
            }

            // Adiciona na lista de prioridades cada simbolo.
            for(auto i = 0u; i < 128; i++){
                if(array[i]->frequency){
                    pq.push(array[i]);
                }
            }
            // Fecha o arquivo.
            reader.close();
        }

        // Imprime o valor do vetor de nós dos 128 caracteres.
        void printArray(){
            for(int i = 0; i < 128; i++){
                std::cout << array[i]->value << std::endl;
            }
        }
      
    public:
        /**
         * Construtor padrão para a classe.
         * @param file_in nome do arquivo de entrada.
         * @param file_out nome do arquivo de saída.
         */
        Huffman(std::string file_in, std::string file_out){
            in_name = file_in;
            out_name = file_out;
            
            //Completa o array.
            for (int i = 0; i< 128; i++){
                array[i] = new Node;
                array[i]->value = i;
                array[i]->frequency = 0;
            }
        }

        /**
         * Método para a criação da árvore como é realizada na codificação de Hoffman.
         */
        void createTree(){
            // Cria a Lista de prioridades
            createPQ();
            std::priority_queue< Node*, std::vector<Node*>, Compare> aux(pq);
            while(aux.size() > 1){
                root = new Node;
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
           // printTree(root);
        }
        
        // Cria a lista de prioridades.
        void createPQ(){
            // Realiza a leitura dos arquivos e cria a lista.
            readFile();
        }

        /** Codifica cada nó da árvore.
         * @param node nó raiz (ou de onde se deseja começar).
         * @param code código representativo da raíz.
         */
        void codify(Node* node, std::string code){
            if(node->left == nullptr and node->right == nullptr){
                node->code = code;
                code_nodes.push_back(node);
            } else{
                codify(node->left, code + '0');
                codify(node->right, code + '1');
            }
        }

        /**
         * Imprime a árcore.
         * @param node Nó que se deseja começar a impressão.
         */
        void printTree(Node * node){
            // Percorre o lado esquerdo.
            if(node->left != nullptr){
                printTree(node->left);
            }
            // Percorre o lado direito.
            if(node->right != nullptr){
                printTree(node->right);
            }

            std::cout << node->value << " " << node->frequency << " " << node->code<< std::endl;
        }

        // Salva em um arquivo a codificação do arquivo solicitado pelo usuário.
        void encodingSave(){
            std::string header;
            // Verifica se há um arquivo de saída válido.
            if(out_name.compare(" ") == 0){
                out_name = "data/binary.bin";
            }
            // Abre o arquivo de saída
            std::ofstream output(out_name,std::ios::binary);
            /* Realiza a leitura, a conversão para bit e escreve no arquivo de saída o resultado.
             * gerando um padrão a ser interpretado na leitura pelo descompactador.
             */
            for(auto i = 0u; i < code_nodes.size(); i++){
                header = std::string(1,code_nodes[i]->value) + code_nodes[i]->code;
                for(auto j = 0u; j < header.size(); j++){
                    std::bitset<8> first(header[j]);
                    unsigned long n = first.to_ulong();
                    output.write( reinterpret_cast<const char*>(&n), sizeof(n) );
                }

                std::bitset<8> space("00000010");
                unsigned long space_n = space.to_ulong();
                output.write( reinterpret_cast<const char*>(&space_n), sizeof(space_n));

                 std::bitset<8> spacef(code_nodes[i]->frequency);
                unsigned long space_nf = spacef.to_ulong();
                output.write( reinterpret_cast<const char*>(&space_nf), sizeof(space_nf));

            }

            // Indica o fim do cabeçalho.
            std::bitset<8> end ("00000011");
            unsigned long l = end.to_ulong();
            output.write( reinterpret_cast<const char*>(&l), sizeof(l));


            std::fstream reader(in_name, std::fstream::in);
            std::string line;
            char c;
            int pos;
            std::string code;
            while(reader.get(c)){
                pos = c;
                code = array[pos]->code;
                for(auto i = 0u; i < code.size(); i++){
                    std::bitset<1> first("0");
                    if(code[i] == '1'){
                        first[0] = 1;
                    }
                    unsigned long n = first.to_ulong();
                    output.write( reinterpret_cast<const char*>(&n), sizeof(n) ) ;
                }
            }
            // Fecha o arquivo.
            output.close();
        }

        // Realiza a leitura do cabeçalho para realizar a decodificação.
        void readHeader(){
            std::bitset<8> first;
            std::ifstream input(in_name,std::ios::binary);
            unsigned long n ;
            
            bool freq_bool = false;
            bool value = true;
            bool end;
            std::string code_aux = "";
            char value_aux;
            /** Percorre o arquivo de entrada e interpreta o cabeçalho, a partir do padrão
             * estabelecido no encodingSave.
             */
            while(!input.eof()){
                input.read( reinterpret_cast<char*>(&n), sizeof(n) ) ;
                char a = n;
                if(n == 3 and !freq_bool){
                    break;
                }else {
                    if(value){
                        value_aux = a;
                        value = false;
                        end = false;
                    } else {
                        code_aux += a;
                    }
                    if(freq_bool){
                        Node * aux = new Node;
                        aux->value = value_aux;
                        aux->code = code_aux;
                        aux->frequency = n; 
                        code_aux = "";
                        value = true;
                        freq_bool = false;
                        end = true;
                        code_nodes.push_back(aux);
                    }
                    if(n == 2 and !end){
                        freq_bool = true;
                    }
                } 
            }
            //printCodes();
            createTreeDecode();
            input.close();
        }

        // Imprime os códigos dos nós (realização de testes).
        void printCodes(){
            // Realiza a impressão dos códigos a fim de testes para verificar se a árvore está criada corretamente.
            for(auto it = code_nodes.begin(); it != code_nodes.end(); it++){
                std::cout <<(*it)->value << (*it)->code << " " << (*it)->frequency<< std::endl;
            }
        }

        // Cria uma árvore de decodificação.
        void createTreeDecode(){
            // Cria a lista de prioridades para a decoficação do arquivo binário.
            createPQDecode();
            std::priority_queue< Node*, std::vector<Node*>, Compare> aux(pq);
            // Cria os nós a partir da lista de prioridades.
            while(aux.size() > 1){
                root = new Node;
                root->frequency = 0;
                root->left = aux.top();
                root->frequency += aux.top()->frequency;
                aux.pop();
                root->right = aux.top();
                root->frequency += aux.top()->frequency;
                aux.pop();
                aux.push(root);
            }
            // Codifica a partir da raiz.
            codify(root, "");
           // printTree(root);
        }

        // Cria uma lista de prioridades para a árvore de decodificação.
        void createPQDecode(){
            for(auto it = code_nodes.begin(); it != code_nodes.end(); it++){
                int pos = (*it)->value;
                array[pos]->frequency = (*it)->frequency;
            }

            // Preenche a fila com o array de caracteres.
            for(auto i = 0u; i < 128; i++){
                if(array[i]->frequency){
                    pq.push(array[i]);
                }
            }
        }

        // Realiza a decodificação de um arquivo binário.
        void decipherer(){
            std::bitset<8> first;
            // Abre o arquivo de entrada.
            std::ifstream input(in_name,std::ios::binary);
            std::ofstream output;
            // Valida de forma a ser uma saída valida.
            if(out_name == " "){
                out_name = "data/saida.txt";
            }
            // Abre o arquivo de saída.
            output.open(out_name);
            unsigned long n ;
            
            bool header = true;
            //bool value = true;
            //bool end;
            std::string code_aux = "";
            //char value_aux;
            Node * aux = root;
            // Percorre o arquivo de forma a gerar o arquivo decodificado.
            while(!input.eof()){
                input.read( reinterpret_cast<char*>(&n), sizeof(n) ) ;
                //char a = n;
                if(!header){
                    if(n == 1){
                        aux = aux->right;
                        if(aux->left == nullptr and aux->right == nullptr){
                            output << aux->value;
                            aux = root;
                        }
                    }
                    if(n == 0){
                        aux = aux->left;
                        if(aux->left == nullptr and aux->right == nullptr){
                            output << aux->value;
                            aux = root;
                        }
                    }
                }
                if(n == 3 and header){
                    header = false;
                }
            }
            // Fecha o arquivo de entrada.
            input.close();
            // Fecha o arquivo de saída.
            output.close();
        }

};
#endif