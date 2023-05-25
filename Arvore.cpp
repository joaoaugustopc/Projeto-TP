#include"Arvore.h"
#include<ctime>
#include<cstdlib>
#include <random>

using namespace std;

Arv::Arv()
{
raiz =NULL;
}

Arv::~Arv(){
    raiz=libera(raiz);
}
int Arv::numAleatorio(){
    static random_device rd; // static para criar apenas uma vez
    static mt19937 gen(rd()); // gerador aleatorio
    static uniform_int_distribution <int> dist(10, 100); // faixa de valores
    return dist(gen);
}

int Arv::getRaiz()
{
if(raiz != NULL) 
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

bool Arv::isoperator(char c){
    return (c=='+'||c=='-'||c=='/'||c=='*');
}


void Arv::cria(char val)
{
raiz = auxcria(raiz, val);
}


NoArv* Arv::auxcria(NoArv *p, char val)
{
if(p == NULL)
{
p = new NoArv();
p->setInfo(val);
p->setEsq(NULL);
p->setDir(NULL);
}
else if(val < p->getInfo())
p->setEsq(auxcria(p->getEsq(), val));
else
p->setDir(auxcria(p->getDir(), val));
return p;
}

NoArv* Arv::libera(NoArv *p)
{
if (p != NULL)
{
p->setEsq( libera(p->getEsq()));
p->setDir( libera(p->getDir()));
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

void Arv :: auxImprime(NoArv *p)
{
if(p != NULL)
{
auxImprime(p->getEsq());
auxImprime(p->getDir());
cout << p->getInfo() <<", ";
}
}

char Arv::valaleatorio(char a,char b){
    
    return a + rand()%(b-a + 1);
}

void Arv ::altera(){
    auxaltera(raiz);
}
void Arv::auxaltera(NoArv *p){
    srand(time(NULL));
    char vet[4]={'+','-','*','/'};
    if(p!=NULL){
        auxaltera(p->getEsq());
        auxaltera(p->getDir());
        if(altura(p)!=0){
            
            p->setInfo(vet[valaleatorio(0,3)]);
            }
        }
}
void Arv::criaArvAleatoria(int altura){
    raiz = criaSubArvAleatoria(altura);
}
NoArv* Arv::criaSubArvAleatoria(int altura){
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