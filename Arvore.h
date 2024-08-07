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
    int no;
    double Aptidao;
    bool auxbusca(NoArv *p, char val);
    NoArv *libera(NoArv *p);
    void auxImprime(NoArv *p);
    void auxaltera(NoArv *p);
    double numAleatorio(char *type);
    NoArv *criaSubArvAleatoria(int altura);
    void preencherPilha(NoArv *p, std::stack<NoArv *> *pilha);
    int retornarResultadoExpressao(std::stack<char> &pilha);
    NoArv *auxMuta(NoArv *p, NoArv *sub, int val, int *cont);
    NoArv *noh(NoArv *p, int val, int *cont);
    NoArv *auxRecombina(NoArv *p, NoArv *sub, int val, int *cont);
    NoArv *auxClona(NoArv *p);
    int contaNos(NoArv *p);
    void auxImprimeOrdem(NoArv *p);
    string returnPosOrdAux(NoArv *p);

public:
    Arv(char *cabecalho, int tam);
    ~Arv();
    bool vazia();
    NoArv *getRaiz();
    void imprime();
    void imprimeOrdem();
    bool busca(char val);
    bool isoperator(char c);
    int altura(NoArv *p);
    void altera();
    double valaleatorio(char *type);
    void criaArvAleatoria(int altura);
    int resolverExpressao();
    void preenchePilhaAux(stack<NoArv *> *pilha);
    void Muta(Arv *subarv);
    int getNos();
    void Recombina(Arv *arvore2);
    void setAptidao(double val);
    double getAptidao();
    void clona(Arv *p);
    void liberar();
    string returnArv();
};

#endif