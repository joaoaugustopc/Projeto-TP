#include "Arvore.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

Arvore::Arvore(int tam)
{
    max = tam;
    n = 0;
    vet = new No[max];
}
Arvore::~Arvore()
{
    delete[] vet;
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

char Arvore::gerarNumeroAleatorio()
{
    return '0' + rand() % 10;
}
char Arvore::gerarOperadorAleatorio()
{
    char operadores[4] = {'+', '-', '*', '/'};
    return operadores[rand() % 4];
}

char Arvore::valAleatorio()
{
    int x = 0 + rand() % 2;
    if (x == 0)
    {
        return gerarNumeroAleatorio();
    }
    else
    {

        return gerarOperadorAleatorio();
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

    if (n != max)
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
