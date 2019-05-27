# Codificação de Huffman para compactação de Imagem

A codificação de Huffman é um método de compactação que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser 
compactado para determinar códigos de tamanho variável para cada símbolo. 

## Compilar

Antes de compilar o algoritmo é necessário que você certifique-se de ter o g++ e openCV instalados.
Para compilar o algoritmo basta abrir a pasta do repositório no terminal do linux e executar:

```g++ -Wall -std=c++11 'pkg-config --libs -cflags opencv' src/main.cpp -o Visao```

## Executar

Para codificar o arquivo basta inserir o comando no terminal, no local do arquivo:

```./Visao data/arquivo_entrada```

Para descodificar o arquivo basta inserir o comando no terminal

```./Visao header.txt file.txt```

- arquivo_entrada é o arquivo que você deseja compactar, o arquivo a ser compactado pode estar na pasta data (Opcional).
- header.txt é o arquivo de cabeçalho
- file.txt é o arquivo compactado, a saída aparecerá na tela.

## Autor

Abraao Vitor L. Dantas (abraaovld@gmail.com)
