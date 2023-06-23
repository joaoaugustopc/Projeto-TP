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

    int x = 0 + rand() % 3;

    if (x == 0)
    {
        return 48 + rand() % (57 - 48 + 1);
    }
    if (x == 1)
    {
        return 'x' + rand() % ('z' - 'x' + 1);
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

// variar o codigo de acordo com o arquivo
// arquivo vai alterar a geração de arvore (conjunto de variáveis)
// construtor da pilha para copiar
// divisao protegida

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
    if ((novoNo->getInfo() >= '0' && novoNo->getInfo() <= '9') || (novoNo->getInfo() >= 'x' && novoNo->getInfo() <= 'z'))
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
    std::stack<char> pilha;

    preencherPilha(raiz, pilha);

    return retornarResultadoExpressao(pilha);
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

int Arv::retornarResultadoExpressao(std::stack<char> &pilha)
{
    // criar copia da pilha original
    std::stack<char> pilhaTemp;
    std::stack<char> pilhaCopia;

    while (!pilha.empty())
    {
        pilhaCopia.push(pilha.top());
        pilhaTemp.push(pilha.top());
        pilha.pop();
    }

    cout << "teste" << endl;

    while(!pilhaTemp.empty()){
        cout << pilhaTemp.top() << endl;
        pilhaTemp.pop();
    }

    while (!pilhaTemp.empty())
    {
        pilha.push(pilhaTemp.top());
        pilhaTemp.pop();
    }

    // operacoes

    std::stack<int> pilhaResultado;
    while (!pilhaCopia.empty())
    {
        if (pilhaCopia.top() == '+' || pilhaCopia.top() == '-' || pilhaCopia.top() == '*' || pilhaCopia.top() == '/')
        {
            char operacao = pilhaCopia.top(); // colocar em cima
            pilhaCopia.pop();

            if (pilhaResultado.size() < 2)
            {
                cout << "erro de tamanho" << endl;
                exit(1);
            }

            int val2 = pilhaResultado.top();
            pilhaResultado.pop();
            int val1 = pilhaResultado.top();
            pilhaResultado.pop();

            int resultado;

            switch (operacao)
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
                if (val2 == 0)
                {
                    cout << "Impossível dividir 0 por um número!" << endl; //pensar em divisao protegida
                    // colocar um if para retornar um valor para essas contas  
                    exit(1);
                }
                resultado = val1 / val2;
                break;
            default:
                std::cout << "Operador inválido!" << std::endl;
                exit(1);
            }

            pilhaResultado.push(resultado);
        }
        else if (isdigit(pilhaCopia.top()))
        {
            pilhaResultado.push(pilhaCopia.top() - '0');
            pilhaCopia.pop();
        }
        else
        {
            cout << "operacao invalida" << endl;
            exit(1);
        }
    }

    return pilhaResultado.top();
}

void Arv::preenchePilhaAux(stack<char> &pilha)
{
    preencherPilha(raiz, pilha);
}


// fazer o sorteio do nó para incluir uma subarvore
// a subarvore vai depender do nó sorteado na árvore
// criar uma classe para fazer avaliação da arvore, usando o arquivo e as operações

//lembrar de algo do operação 