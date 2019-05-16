#include "../include/huffman.hpp"
int main(int argc, char const *argv[])
{
	// Realiza uma verificação se a formatação de entrada está correta.
	if(argc <= 1){
		std::cout << "O formato inserido está errado!\nFORMATO: './main data/arquivo_entrada.txt data/arquivo_saida.txt' ou './main data/arquivo_entrada,txt" << std::endl;
		return 0;
	}

	std::string entrada;
	std::string saida;

	entrada =  argv[1];
	// Verifica se o arquivo de saída é válido.
	if(argv[2] == NULL)
		saida = " ";
	else
		saida = argv[2];

    Huffman h(entrada, saida);

    int escolha = 0;

    // Faz com que o usuário possa realizar entre codificar e decodificar o arquivo.
    while( escolha != 1 and escolha != 2 ){

    	std::cout << "Digite o número da operação desejada:\n1 - Codificar\n2 - Descodificar" << std::endl;
    	std::cin >> escolha;

    	if(escolha == 1){

				int tam = entrada.size();

				std::string val = entrada.substr(tam-3,tam);
				if(!val.compare("bin")){
					std::cout << "Tipo de arquivo inválido!" << std::endl;
					return 0;
				}
			
            h.createTree();
    		h.encodingSave();
    		std::cout << "Arquivo codificado com sucesso!" << std::endl;

    	} else if(escolha == 2){

				int tam = entrada.size();

				std::string val = entrada.substr(tam-3,tam);
				if(val.compare("bin")){
					std::cout << "Tipo de arquivo inválido!" << std::endl;
					return 0;
				
			}	

    		h.readHeader();
            h.decipherer();
    		std::cout << "Arquivo descodificado com sucesso!" << std::endl;

    	} else{
    		std::cout << "Opção inválida!";
    	}
    }
    return 0;
}