#include <iostream>
#include "ArvBin.h"
#include "NoArv.h"
#include <random>

using namespace std;

ArvBin::ArvBin(){
    raiz = NULL;
}

int ArvBin::numAleatorio(){
    static random_device rd; // static para criar apenas uma vez
    static mt19937 gen(rd()); // gerador aleatorio
    static uniform_int_distribution <int> dist(10, 100); // faixa de valores
    return dist(gen);
}

ArvBin::~ArvBin(){
    libera(raiz);
}

int ArvBin::getRaiz(){
    if(raiz != NULL){
        return raiz->getInfo();
    } else{
        cout << "Arvore Vazia" << endl;
        exit(1);
    }
}

bool ArvBin::vazia(){
    return raiz == NULL;
}

void ArvBin::cria(int val, ArvBin *sae, ArvBin *sad){
    NoArv *p = new NoArv();
    p->setInfo(val);
    p->setEsq(sae->raiz);
    p->setDir(sad->raiz);
    raiz = p;
}

void ArvBin::imprime(){
    auxImprime(raiz);
}

//funcao privada
void ArvBin::auxImprime(NoArv *p){
    //preOrder

    if(p == NULL) return;
    cout << p->getInfo() << endl;
    auxImprime(p->getEsq());
    auxImprime(p->getDir());
}

bool ArvBin::auxBusca(NoArv *p, int val){
    if(p == NULL){ // base
        return false;
    } else if (p->getInfo() == val){
        return true;
    } else if(auxBusca(p->getEsq(), val)){
        return true;
    } else return auxBusca(p->getDir(), val);
}

bool ArvBin::busca(int val){
    return auxBusca(raiz, val);
}

NoArv* ArvBin::libera(NoArv *p){
    if (p != NULL){
        p->setEsq( libera(p->getEsq()));
        p->setDir( libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return NULL;
}

/*
ArvBin* ArvBin::arvAleatoria(int numNo){
    ArvBin *arv = new ArvBin();
    
    for(int i = 0; i < numNo; i++){
        ArvBin* sae = new ArvBin();
        ArvBin* sad = new ArvBin();
        arv->cria(numAleatorio(), sae, sad);
    }
    return arv;
}
*/

void ArvBin::criaArvAleatoria(int altura){
    raiz = criaSubArvAleatoria(altura);
}

NoArv* ArvBin::criaSubArvAleatoria(int altura){
    // funcao para subarvore
    if(altura <= 0){
        return NULL;
    }

    NoArv* novoNo = new NoArv();
    novoNo->setInfo(numAleatorio());


    if(altura > 1){
        novoNo->setEsq(criaSubArvAleatoria(altura - 1));
        novoNo->setDir(criaSubArvAleatoria(altura - 1));

    }
    
    return novoNo;

}


