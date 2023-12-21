#!/bin/bash

echo "Compilando e executando randSeeds.cpp..."
g++ randSeeds.cpp -o randSeeds && ./randSeeds

echo "Escolha uma árvore (1-21):"
read arvore

echo "Digite o número de dados:"
read dados

if [[ $arvore -ge 1 && $arvore -le 21 ]]; then
    echo "Você escolheu a árvore $arvore e $dados dados."

    # Lê as sementes do arquivo seeds.txt
    mapfile -t seeds < seeds.txt

    for seed in "${seeds[@]}"
    do
        echo "Executando com a semente $seed"
        # Compila todos os arquivos .cpp exceto randSeeds.cpp e executa com o nome do arquivo e a semente como argumentos
        g++ $(find . -name "*.cpp" ! -name "randSeeds.cpp") -o main && ./main dados/funcao$arvore/funcao$arvore\_$dados.csv $seed
    done
else
    echo "Opção inválida."
fi
