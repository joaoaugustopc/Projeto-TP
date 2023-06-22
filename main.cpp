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

    teste.resolverExpressao();

    return 0;
}