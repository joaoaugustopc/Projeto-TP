#!/bin/bash

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
        echo "===================================="
        echo "Executando com a semente $seed"
        g++ *.cpp && ./a.out dados/funcao$arvore/funcao$arvore\_$dados.csv $seed $arvore $dados
    done
else
    echo "Opção inválida."
fi

cd TESTE_POP
echo "===================================="
echo "Executando testes das melhores árvores..."
echo "===================================="
echo "Resultados:"

testFile=Arquivos_Testes/funcao$arvore\_teste50k.csv
treeFile=Arquivos_Arvores/avaliacaoFuncao$arvore\_arvores$dados.csv
g++ *.cpp && ./a.out $testFile $treeFile

   