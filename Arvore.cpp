#include "Arvore.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <random>
#include <stack>

using namespace std;

Arv::Arv(char *cabecalho, int n)
{
    raiz = NULL;
    tam = n;
    vetor = new char[tam];
    for(int i=0;i<tam;i++){
        vetor[i]=cabecalho[i];
    }

}

Arv::~Arv()
{
    raiz = libera(raiz);
    delete [] vetor;
}

int Arv::numAleatorio()
{

    int x = 0 + rand() % 3;

    if (x == 0)
    {
        return 48 + rand() % (57 - 48 + 1);
    }
    if (x == 1)
    {
        return vetor[0 + rand() % tam];
    }
    else
    {
        int vet[4] = {42, 43, 45, 47};
        return vet[0 + rand() % 4];
    }
    
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
    int val = rand() % 2;

    return 48 + rand() % (57 - 48 + 1);
}

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
    if ((novoNo->getInfo()!='+') && (novoNo->getInfo()!='-') && (novoNo->getInfo()!='/') && (novoNo->getInfo()!='*'))
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

void Arv::preencherPilha(NoArv *p, std::stack<char> &pilha)
{
    if (p == NULL)
    {
        return;
    }

    preencherPilha(p->getEsq(), pilha);
    preencherPilha(p->getDir(), pilha);
    pilha.push(p->getInfo());
}



void Arv::preenchePilhaAux(stack<char> &pilha)
{
    preencherPilha(raiz, pilha);
}
