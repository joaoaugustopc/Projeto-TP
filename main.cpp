#include <iostream>
#include "Arvore.h"
#include <random>

using namespace std;


int main(){
    
    Arv teste;

    teste.criaArvAleatoria(3);

    teste.imprime();
    teste.altera();
    cout<<endl;
    teste.imprime();


    return 0;
}