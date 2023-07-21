#include "Arvore.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <stack>

using namespace std;

Arvore::Arvore(int tam, char *cabecalho, int i)
{
    max = tam;
    n = 0;
    vet = new No[max];
    tamanho = i;
    vetor = new char[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        vetor[i] = cabecalho[i];
    }
}
Arvore::~Arvore()
{
    delete[] vet;
    delete[] vetor;
}
char Arvore::getraiz()
{
    if (n > 0)
    {
        return vet[0].getInfo();
    }
    else
    {
        cout << "Arvore Vazia!\n";
    }
}

int Arvore::gerarNumeroAleatorio()
{
    return 48 + rand() % (57 - 48 + 1);
}
char Arvore::gerarOperadorAleatorio()
{
    char operadores[4] = {'+', '-', '*', '/'};
    return operadores[rand() % 4];
}

int Arvore::valAleatorio()
{
    int x = 0 + rand() % 3;

    if (x == 0)
    {
        return 48 + rand() % (57 - 48 + 1);
    }
    if (x == 1)
    {
        return vetor[rand() % tamanho];
    }
    else
    {
        int vet[4] = {42, 43, 45, 47};
        return vet[0 + rand() % 4];
    }
}
bool Arvore::isOperador(char c)
{
    char operadores[4] = {'+', '-', '*', '/'};
    for (int i = 0; i < 4; i++)
    {
        if (c == operadores[i])
        {
            return true;
        }
    }
    return false;
}

void Arvore::criarvorealeatoria()
{
    auxcria(0);
}

void Arvore::auxcria(int idx)
{
    if (idx == max - 1)
    {
        vet[idx].setinfo(gerarNumeroAleatorio());
        vet[idx].setEsq(-1);
        vet[idx].setDir(-1);
        n++;
        return;
    }

    if (n < max)
    {

        char val = valAleatorio();
        vet[idx].setinfo(val);
        vet[idx].setEsq(-1);
        vet[idx].setDir(-1);
        n++;

        if (isOperador(vet[idx].getInfo()))
        {
            vet[idx].setEsq(n);
            auxcria(n);
            vet[idx].setDir(n);
            auxcria(n);
        }
    }
    return;
}

void Arvore::imprime()
{
    auximprime(0);
}

void Arvore::auximprime(int idx)
{
    if (idx == -1 || idx == max)
    {
        return;
    }
    auximprime(vet[idx].getEsq());
    auximprime(vet[idx].getDir());
    cout << vet[idx].getInfo() << ", ";
}

void Arvore ::preencherPilha(int idx, std::stack<char> &pilha)
{
    if (idx == -1 || idx == max)
    {
        return;
    }
    preencherPilha(vet[idx].getEsq(), pilha);
    preencherPilha(vet[idx].getDir(), pilha);
    pilha.push(vet[idx].getInfo());
}

void Arvore ::preenchePilaAux(std::stack<char> &pilha)
{
    preencherPilha(0, pilha);
}
