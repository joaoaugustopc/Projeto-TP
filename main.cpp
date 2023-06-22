#include <iostream>
#include "Arvore.h"
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
    srand(time(NULL));
    Arvore a(20);
    a.criarvorealeatoria();
    a.imprime();
}