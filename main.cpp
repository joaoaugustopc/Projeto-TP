#include <iostream>
#include "Arvore.h"
#include <random>
#include <ctime>
#include <stack>

using namespace std;

int main()
{

    srand(time(NULL));
    Arv teste;

    teste.criaArvAleatoria(5);

    teste.imprime();

    cout << "pilha resultado: " << teste.resolverExpressao() << endl;

    return 0;
}