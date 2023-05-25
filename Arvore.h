#ifndef ARVORE_H
#define ARVORE_H
#include "NoArv.h"
#include<iostream>
using namespace std;

class Arv
{
    private:
    NoArv *raiz; 
    bool auxbusca(NoArv *p, char val);
    NoArv*libera(NoArv*p);
    void auxImprime(NoArv *p);
    void auxaltera(NoArv*p);
    int numAleatorio();
    NoArv* criaSubArvAleatoria(int altura);

    public:
    Arv();
    ~Arv();
    int getRaiz();
    bool vazia(); 
    void imprime();
    bool busca (char val); 
    bool isoperator( char c);
    int altura(NoArv*p);
    void altera();
    char valaleatorio(char a, char b);
    void criaArvAleatoria(int altura);
};

#endif