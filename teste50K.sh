#!/bin/bash

echo "Escolha uma funcao (1-21):"
read funcao

echo "Digite o número de dados:"
read dados

#if [[ $funcao -ge 1 && $funcao -le 21 ]]; then

    #echo "Você escolheu a árvore $funcao e $dados dados."

    # Lê as sementes do arquivo seeds.txt
    #mapfile -t seeds < seeds.txt

    #for seed in "${seeds[@]}"
    #do
        #echo "===================================="
        #echo "Executando com a semente $seed"
        #g++ *.cpp && ./a.out dados/funcao$funcao/funcao$funcao\_$dados.csv $seed $funcao $dados
    #done
#else
    #echo "Opção inválida."
#fi

cd TESTE_POP
echo "===================================="
echo "Executando testes das melhores árvores..."
echo "===================================="
echo "Resultados:"

testFile=Arquivos_Testes/funcao$funcao\_teste50k.csv
treeFile=Arquivos_Arvores/funcao$funcao/avaliacaoFuncao$funcao\_arvores$dados.csv
g++ *.cpp && ./a.out $testFile $treeFile

   