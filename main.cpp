#include "Arv.h"
#include <iostream>
#include <time.h>
#include <stack>

using namespace std;

int main() {
    srand(time(NULL));

    int maxNodes = 20;
    Arv arvore(maxNodes);
    int altura = 4;

    arvore.criaArvoreAleatoria(altura);

    std::cout << "Árvore gerada aleatoriamente (altura " << altura << "): ";
    arvore.imprime();
    std::cout << std::endl;
    /*cout << "Resultado da operacao: " << arvore.resolverOperacao() << endl;*/

    return 0;
}