#include "Arvore.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <random>
#include <stack>

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

    int x = 0 + rand() % 2;

    if(x == 0){
        return 48 + rand() % (57 - 48 + 1);
        
    } else{
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

int Arv::resolverExpressao()
{
    std::stack<int> pilha;

    resolverExpressaoAux(raiz, pilha);

    if (!pilha.empty()) {
        int resultado = pilha.top();
        pilha.pop();
        return resultado;
    }

    return -1; // invalido
}

void Arv::resolverExpressaoAux(NoArv *p, std::stack<int> &pilha){
    if (p != NULL)
    {
        resolverExpressaoAux(p->getEsq(), pilha);
        resolverExpressaoAux(p->getDir(), pilha);

        char info = p->getInfo();

        if(info == '+' || info == '-' || info == '*' || info == '/'){
            if (pilha.size() < 2)
            {
                std::cout << "Expressão inválida!" << std::endl;
                return;
            }

            int val2 = pilha.top();
            pilha.pop();
            int val1 = pilha.top();
            pilha.pop();

            int resultado;

            switch (info)
            {
                case '+':
                    resultado = val1 + val2;
                    break;
                case '-':
                    resultado = val1 - val2;
                    break;
                case '*':
                    resultado = val1 * val2;
                    break;
                case '/':
                    if(val1 == 0){
                        cout << "Impossível dividir 0 por um número!" << endl;
                        exit(1);
                    }
                    resultado = val1 / val2;
                    break;
                default:
                    std::cout << "Operador inválido!" << std::endl;
                    return;
            }

            pilha.push(resultado);
        } else if(isdigit(info)){
            pilha.push(info - '0');
        } else{
            std::cout << "Caractere inválido!" << std::endl;
            return;
        }
    }
}