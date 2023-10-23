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
    no = -1;               // idx dos nos da arvore, contagem pos-ordem
    tam = n;               // tamanho do vetor
    vetor = new char[tam]; // vetor para armazenar as variaveis do arquivo lido
    Aptidao = -1;

    for (int i = 0; i < tam; i++)
    {
        vetor[i] = cabecalho[i]; // trocar o nome
    }
}

Arv::~Arv()
{
    raiz = libera(raiz);
    delete[] vetor;
}

float Arv::numAleatorio(char *type) // retornar float (pode guardar char)
{
    int x = rand() % 4;

    if (x == 0)
    {
        *type = 0;                 // guardar o tipo (numero)
        return -10 + rand() % 111; // retornar um valor aleatorio em uma faixa de valores (pode mudar essa faixa)
    }
    else if (x == 1)
    {
        *type = 1;                      // guardar o tipo (variavel)
        return vetor[0 + rand() % tam]; // retornar uma variavel válida aleatoria
    }
    else if (x == 2)
    {
        *type = 2;                         // guardar o tipo (operador)
        int vet[5] = {42, 43, 45, 47, 94}; // vetor contendo (na representacao do tipo int) os operadores
        return vet[rand() % 5];
    }
    else
    {
        *type = 3;                      // guardar o tipo (operador c/ uma entrada de parâmetro)
        int vet[4] = {101, 35, 36, 38}; // vetor contendo (na representacao do tipo int) os operadores
        return vet[rand() % 4];
    }
}

NoArv *Arv::getRaiz()
{
    if (raiz != NULL)
        return raiz;
    else
    {
        cout << "Árvora vazia!" << endl;
        return NULL;
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
        no--;
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
    cout << endl;
}

void Arv ::auxImprime(NoArv *p)
{
    if (p != NULL)
    {
        auxImprime(p->getEsq());
        auxImprime(p->getDir());
        if (p->getTipo() != 0)
        {
            char valor = ((char)p->getInfo());
            cout << valor << ", ";
        }
        else
        {
            cout << p->getInfo() << ", ";
        }
    }
}

float Arv::valaleatorio(char *type) // funcao para retornar um valor aleatorio (no caso de chegar na altura maxima)
{
    int val = rand() % 2;
    if (val == 0)
    {
        *type = 0;
        return rand() % 101;
    }
    else
    {
        *type = 1;
        return vetor[0 + rand() % tam];
    }
}

void Arv::criaArvAleatoria(int altura)
{
    raiz = criaSubArvAleatoria(altura);
}

NoArv *Arv::criaSubArvAleatoria(int altura)
{
    // funcao para subarvore
    char type;
    NoArv *novoNo = new NoArv();
    if (altura == 1) // caso chegue na altura maxima as folhas devem ser valores e nao operadores
    {
        novoNo->setInfo(valaleatorio(&type));
        novoNo->setTipo(type);
        novoNo->setEsq(NULL);
        novoNo->setDir(NULL);
        no++;
        return novoNo;
    }

    float x = numAleatorio(&type); // Passa o endereco da variavel para armezar o tipo de dado do nó
    novoNo->setInfo(x);
    novoNo->setTipo(type);

    if (novoNo->getTipo() != 2 && novoNo->getTipo() != 3)
    {
        novoNo->setEsq(NULL);
        novoNo->setDir(NULL);
        no++;
        return novoNo;
    }
    else
    {
        if (novoNo->getTipo() == 3)     // Nos casos em que o operador seja um que necessite apenas de uma entrada Ex : exponencial, seno, cosseno e raiz quadrada;
        {
            novoNo->setEsq(criaSubArvAleatoria(altura - 1));
            novoNo->setDir(NULL);
        }
        else
        {
            novoNo->setEsq(criaSubArvAleatoria(altura - 1));
            novoNo->setDir(criaSubArvAleatoria(altura - 1));
        }

        no++;
    }

    return novoNo;
}

void Arv::preencherPilha(NoArv *p, std::stack<NoArv *> *pilha)
{
    if (p == NULL)
    {
        return;
    }

    preencherPilha(p->getEsq(), pilha);
    preencherPilha(p->getDir(), pilha);
    pilha->push(p);
}

void Arv::preenchePilhaAux(stack<NoArv *> *pilha)
{
    preencherPilha(raiz, pilha);
}

void Arv::Muta(Arv *subarv)
{
    int noSorteio = rand() % (no + 1); // sorteia um idx que vai representar um nó
    int cont = 0;                      // contador

    raiz = auxMuta(raiz, subarv->raiz, noSorteio, &cont);

    no += subarv->getNos(); // atualiza o ultimo idx
    subarv->raiz = NULL;
}

NoArv *Arv::auxMuta(NoArv *p, NoArv *sub, int noMutacao, int *cont)
{

    if (p == NULL)
    {
        return NULL;
    }
    if ((*cont) == noMutacao)
    {
        (*cont)++;
        p = libera(p); // deleta toda a subarvore sorteada e retorna a raiz da outra arvore gerada aleatoriamente
        return sub;
    }
    else
    {
        (*cont)++;
        p->setEsq(auxMuta(p->getEsq(), sub, noMutacao, cont));
        p->setDir(auxMuta(p->getDir(), sub, noMutacao, cont));
    }

    return p;
}

int Arv ::getNos() // retorna a quantidade de nos, alterar nome
{
    return no + 1;
}

void Arv ::Recombina(Arv *arvore2)
{
    int no1 = rand() % (no + 1);            // sorteia um idx para representar o nó da arvore1
    int no2 = rand() % ((arvore2->no) + 1); // sorteia outro idx para representar o nó da arvore 2
    int cont = 0;

    NoArv *arv1 = noh(this->raiz, no1, &cont); // Retorna o nó da arvore 1 que corresponde ao idx sorteado (NAO CONSEGUI PASSAR O PONTEIRO PARA PONTEIRO PARA GUARDAR O PAI E REALIZAR A OPERACAO)

    cont = 0;
    NoArv *arv2 = noh(arvore2->raiz, no2, &cont); // Retorna o nó da arvore 2 que corresponde ao idx sorteado

    // percorre arvore novamente
    cont = 0;
    raiz = auxRecombina(raiz, arv2, no1, &cont); // coloca o nó sorteado da arvore 2 no local do nó sorteado da arvore 1
    cont = 0;
    arvore2->raiz = auxRecombina(arvore2->raiz, arv1, no2, &cont); // coloca o nó sorteado da arvore 1 no local do nó sorteado da arvore 2
    this->no = contaNos(raiz) - 1;
    arvore2->no = contaNos(arvore2->raiz) - 1;
}

NoArv *Arv ::auxRecombina(NoArv *p, NoArv *sub, int val, int *cont) // igual a funcao de mutar, porém esta nao deleta nenhuma subarvore
{
    if (p == NULL)
    {
        return NULL;
    }
    if (val == (*cont))
    {
        (*cont)++;
        return sub;
    }
    else
    {
        (*cont)++;
        p->setEsq(auxRecombina(p->getEsq(), sub, val, cont));
        p->setDir(auxRecombina(p->getDir(), sub, val, cont));
    }

    return p;
}

NoArv *Arv ::noh(NoArv *p, int val, int *cont) // funcao que retorna o nó de idx "val"
{
    if (p == NULL)
    {
        return NULL;
    }
    if (val == (*cont))
    {
        (*cont)++;
        return p;
    }
    else
    {
        (*cont)++;
        NoArv *result_esq = noh(p->getEsq(), val, cont);
        if (result_esq != NULL)
        {
            return result_esq;
        }
        else
        {
            return noh(p->getDir(), val, cont);
        }
    }
}

void Arv ::setAptidao(float val)
{
    Aptidao = val;
}

float Arv ::getAptidao()
{
    return Aptidao;
}

void Arv ::clona(Arv *p)
{
    raiz = libera(raiz);
    raiz = auxClona(p->getRaiz());
    Aptidao = p->Aptidao;
    no = p->no;
}

NoArv *Arv ::auxClona(NoArv *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    NoArv *novoNo = new NoArv();
    novoNo->setInfo(p->getInfo());
    novoNo->setTipo(p->getTipo());
    if (novoNo->getTipo() != 2)
    {
        novoNo->setEsq(NULL);
        novoNo->setDir(NULL);
        no++;
    }
    else
    {
        novoNo->setEsq(auxClona(p->getEsq()));
        novoNo->setDir(auxClona(p->getDir()));
        no++;
    }

    return novoNo;
}

void Arv ::liberar()
{
    raiz = libera(raiz);
    Aptidao = -1;
}

int Arv ::contaNos(NoArv *p)
{
    if (p == NULL)
    {
        return 0;
    }

    int x = contaNos(p->getEsq()) + contaNos(p->getDir());
    return x + 1;
}