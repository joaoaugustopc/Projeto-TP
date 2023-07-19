#ifndef ARVORE_H
#define ARVORE_H
#include "NoArv.h"
#include <iostream>
#include <stack>

using namespace std;

class Arv
{
private:
    NoArv *raiz;
    char *vetor;
    int tam;
    int nos;
    bool auxbusca(NoArv *p, char val);
    NoArv *libera(NoArv *p);
    void auxImprime(NoArv *p);
    void auxaltera(NoArv *p);
    int numAleatorio();
    NoArv *criaSubArvAleatoria(int altura);
    void preencherPilha(NoArv *p, std::stack<char> &pilha);
    int retornarResultadoExpressao(std::stack<char> &pilha);
    NoArv* auxevolui(NoArv*p, NoArv*sub, int val, int* cont);

public:
    Arv(char *cabecalho, int tam);
    ~Arv();
    bool vazia();
    NoArv* getRaiz();
    void imprime();
    bool busca(char val);
    bool isoperator(char c);
    int altura(NoArv *p);
    void altera();
    char valaleatorio();
    void criaArvAleatoria(int altura);
    int resolverExpressao();
    void preenchePilhaAux(stack<char> &pilha);
    void evolui(Arv*subarv);
    int getNos();
    

};

#endif