#include "Arvore.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;

Arv::Arv()
{
    raiz = NULL;
}

Arv::~Arv()
{
    raiz = libera(raiz);
}

int Arv::numAleatorio()
{

    int x = 0 + rand() % 3;
    if (x == 0)
    {
        return 48 + rand() % (57 - 48 + 1);
    }
    else if (x == 1)
    {
        return 97 + rand() % (122 - 97 + 1);
    }
    else
    {
        int vet[4] = {42, 43, 45, 47};
        return vet[0 + rand() % 4];
    }

    /*static random_device rd; // static para criar apenas uma vez
    static mt19937 gen(rd()); // gerador aleatorio
    static uniform_int_distribution <int> dist(48, 57); // faixa de valores
    return dist(gen);*/
}

int Arv::getRaiz()
{
    if (raiz != NULL)
        return raiz->getInfo();
    else
    {
        cout << "Árvora vazia!" << endl;
    }
}

bool Arv::vazia()
{
    return raiz == NULL;
}

NoArv *Arv::libera(NoArv *p)
{
    if (p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }

    return NULL;
}

int Arv::altura(NoArv *p)
{
    int he, hd;
    if (p == NULL)
        return -1;
    else
    {
        he = altura(p->getEsq());
        hd = altura(p->getDir());
        return 1 + (he > hd ? he : hd);
    }
}

bool Arv::busca(char val)
{
    return auxbusca(raiz, val);
}

bool Arv::auxbusca(NoArv *p, char ch)
{
    if (p == NULL)
        return false;
    else if (p->getInfo() == ch)
        return true;
    else if (auxbusca(p->getEsq(), ch))
        return true;
    else
        return auxbusca(p->getDir(), ch);
}

void Arv::imprime()
{
    auxImprime(raiz);
}

void Arv ::auxImprime(NoArv *p)
{
    if (p != NULL)
    {
        auxImprime(p->getEsq());
        auxImprime(p->getDir());
        cout << p->getInfo() << ", ";
    }
}

char Arv::valaleatorio()
{
    int val = 0 + rand() % 2;
    if (val == 0)
    {
        return 48 + rand() % (57 - 48 + 1);
    }
    else
    {
        return 97 + rand() % (122 - 97 + 1);
    }
}

/*void Arv ::altera(){
    auxaltera(raiz);
}

void Arv::auxaltera(NoArv *p){
    char vet[4]={'+','-','*','/'};
    if(p!=NULL){
        auxaltera(p->getEsq());
        auxaltera(p->getDir());
        if(altura(p)!=0){
            p->setInfo(vet[valaleatorio(0,3)]);
        }
    }
}*/

void Arv::criaArvAleatoria(int altura)
{

    raiz = criaSubArvAleatoria(altura);
}

NoArv *Arv::criaSubArvAleatoria(int altura)
{
    // funcao para subarvore
    NoArv *novoNo = new NoArv();
    if (altura == 1)
    {
        novoNo->setInfo(valaleatorio());
        novoNo->setEsq(NULL);
        novoNo->setDir(NULL);
        return novoNo;
    }

    char x = numAleatorio();
    novoNo->setInfo(x);
    if ((novoNo->getInfo() >= '0' && novoNo->getInfo() <= '9') || (novoNo->getInfo() >= 'a' && novoNo->getInfo() <= 'z'))
    {
        novoNo->setEsq(NULL);
        novoNo->setDir(NULL);
        return novoNo;
    }
    else
    {
        novoNo->setEsq(criaSubArvAleatoria(altura - 1));
        novoNo->setDir(criaSubArvAleatoria(altura - 1));
    }

    return novoNo;
}
