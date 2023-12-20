#!/bin/bash

echo "Escolha uma árvore (1-21):"
read arvore

echo "Digite o número de dados:"
read dados

if [[ $arvore -ge 1 && $arvore -le 21 ]]; then
    echo "Você escolheu a árvore $arvore e $dados dados."
    # Compila o programa C++ e executa com o nome do arquivo como argumento
    g++ *.cpp && ./a.out dados/funcao$arvore/funcao$arvore\_$dados.csv
else
    echo "Opção inválida."
fi