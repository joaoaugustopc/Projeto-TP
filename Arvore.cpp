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

int Arv::resolverExpressao(){
    std::stack<int> pilha;

    preencherPilha(raiz, pilha);

    cout << "teste" << endl;

    while(!pilha.empty()){
        cout << pilha.top() << endl;
        pilha.pop();
    }

    cout << endl;

    return 1;

   /* comentario pra teste

    if(!pilha.empty()){
        int resultado = pilha.top(); // consertar
        return resultado;
    } else return -1;
   */ 

}

void Arv::preencherPilha(NoArv* p, std::stack<int>& pilha) {
    // corrigir
    if (p == nullptr) {
        return;
    }

    preencherPilha(p->getEsq(), pilha);
    pilha.push(p->getInfo());
    preencherPilha(p->getDir(), pilha);
}

 int Arv::retornarResultadoExpressao(std::stack<int> &pilha){
    //criar copia da pilha original
    std::stack<char> pilhaTemp;
    std::stack<char> pilhaCopia;

    while(!pilha.empty()){
        pilhaTemp.push(pilha.top());
        pilha.pop();
    }

    while(!pilhaTemp.empty()){
        pilhaCopia.push(pilhaTemp.top());
        pilha.push(pilhaTemp.top());
        pilhaTemp.pop();
    }

    //operacoes

    while(!pilhaCopia.empty()){
        if(pilhaCopia.top() == '+' || pilhaCopia.top() == '-' || pilhaCopia.top() == '/' || pilhaCopia.top() == '*'){
            if(pilhaCopia.size() < 2){
                cout << "Expressao invalida" << endl;
                return;
            }

            char operacao = pilhaCopia.top();
            pilhaCopia.pop();

            int val2 = pilhaCopia.top();
            pilhaCopia.pop();
            int val1 = pilhaCopia.top();
            pilhaCopia.pop();

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

            pilhaCopia.push(resultado);
        } else{
            cout << "Operacao invalida" << endl;
            return;
        }
    }

 }