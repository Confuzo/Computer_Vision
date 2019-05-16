# Codificação de Huffman

A codificação de Huffman é um método de compactação que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser 
compactado para determinar códigos de tamanho variável para cada símbolo. 

## Compilar

Antes de compilar o algoritmo é necessário que você certifique-se de ter o g++ instalado.
Para compilar o algoritmo basta abrir a pasta do repositório no terminal do linux e executar:

```./compile.sh```

## Executar

Para executar o arquivo basta inserir o comando no terminal, no local do arquivo:
- Compactação:
```./main data/arquivo_entrada.txt data/arquivo_saida.bin```
- Descompactação:
```./main data/arquivo_entrada.bin data/arquivo_saida.txt```

- arquivo_entrada é o arquivo que você deseja compactar ou descompactar.
- arquivo_saida é o arquivo compactado ou descompactado.

Vale salientar que todos os arquivos de saída da compactação devem ser .bin, bem como o arquivo de entrada da descompactação deve ser a saída da compactação e portanto .bin também.

Ao executar o programa surgirar um menu de duas opções:

- Codificação
- Descodificação

## Autores

Abraao Vitor L. Dantas (abraaovld@gmail.com)

Henrique David de Medeiros (henriquemed101@gmail.com)

