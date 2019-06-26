# Tranformada de Hough

## Compilar

Antes de compilar o algoritmo é necessário que você certifique-se de ter o g++ e openCV instalados.
Para compilar o algoritmo basta abrir a pasta do repositório no terminal do linux e executar:

```g++ -Wall -std=c++11 'pkg-config --libs -cflags opencv' src/main.cpp -o Visao```

## Executar

Para aplicar a função de hough para achar linhas e retas:

```./Visao 1 data/arquivo_entrada coeficiente```

- 1 é a opção para executar a tranformada para linhas.
- arquivo_entrada é a imagem que se deseja aplicar a função, o arquivo a ser compactado pode estar na pasta data (Opcional).
- coeficiente é o valor de pontuação que deve ser atendido pela matriz de votação.

Para aplicar a função de hough para achar círculos:

```./Visao 2 data/bola.jpg coeficiente raio_minimo raio_maximo```


- 2 é a opção para executar a transformada para círculos
- arquivo_entrada é a imagem que se deseja aplicar a função, o arquivo a ser compactado pode estar na pasta data (Opcional).
- coeficiente é o valor de pontuação que deve ser atendido pela matriz de votação.
- raio_minimo é o menor valor de raio, onde será aplicada a função
- raio_maximo é o maior valor de raio, onde será aplicada a função


## Autor

Abraao Vitor L. Dantas (abraaovld@gmail.com)
