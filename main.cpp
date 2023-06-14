#include <iostream>
#include "Arvore.h"
#include <random>
#include <ctime>

using namespace std;

int main()
{

    srand(time(NULL));
    Arv teste;

    teste.criaArvAleatoria(5);

    teste.imprime();

    return 0;
}