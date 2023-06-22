#ifndef ARVBIN_H
#define ARVBIN_H
#include "NoArv.h"

class ArvBin{

    private:
    NoArv *raiz;
    void auxImprime(NoArv *p);
    bool auxBusca(NoArv *p, int val);
    NoArv* libera(NoArv *p);
    int numAleatorio();
    NoArv* criaSubArvAleatoria(int altura);

    public:
    ArvBin();
    ~ArvBin();
    int getRaiz();
    void cria(int val, ArvBin *sae, ArvBin *sad);
    bool vazia();
    void imprime();
    bool busca(int val);
    void criaArvAleatoria(int altura);
};

#endif
/*

void preOrder(NoArv *p){
    if(p == NULL) return;
    cout << p->getInfo();
    preOrder(p->getEsq());
    preOrder(p->getDir());
}

void inOrder(NoArv *p){
    if(p == NULL) return;

    inOrder(p->getEsq());
    cout << p->getInfo() << endl;
    inOrder(p->getDir());
}

void posOrder(NoArv *p){
    if(p == NULL) return;
    posOrder(p->getEsq());
    posOrder(p->getDir());
    cout << p->getInfo() << endl;
}

*/