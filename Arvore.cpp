#include"Arvore.h"
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

Arvore::Arvore(int tam){
    max=tam;
    n=0;
    vet=new char[max];
}
Arvore::~Arvore(){
    delete [] vet;
}
char Arvore::getraiz(){
    if(n>0){
        return vet[0];
    }
    else{
        cout<<"Arvore Vazia!\n";

    }
}
void Arvore::insere(char val)
{
if(n < max)
{
vet[n] = val;
n++;
//sobe(n-1);
}
else
{
cout << "Heap cheia!" << endl;

}
}
void Arvore::sobe(int filho)
{
int pai = (filho - 1)/2;
if(vet[filho] < vet[pai])
{

float aux = vet[filho];
vet[filho] = vet[pai];
vet[pai] = aux;
sobe(pai);
}
}

int Arvore::left(int i){
    return 2*i+1;
}

int Arvore::right(int i){
    return 2*(i+1);
}

int Arvore::pai(int i){
    return (i-1)/2;
}

void Arvore::imprime(){
    auximprime(0);
}

void Arvore::auximprime(int i){
    if(i<n){
        auximprime(left(i));
        auximprime(right(i));
        cout<<vet[i]<<", ";
    }
}

int Arvore::altura(int p){
    int he, hd;
    if (p>=n)
        return -1;
    else{
        he = altura(left(p));
        hd = altura(right(p));
        return 1 + (he > hd ? he : hd);
    }
}

char Arvore::valaleatorio(char a,char b){    
    return a + rand()%(b-a + 1);
}
void Arvore ::altera(){
    auxaltera(0);
}

void Arvore::auxaltera(int p){
    srand(time(NULL));
    char op[4]={'+','-','*','/'};
    if(p<n){
        auxaltera(left(p));
        auxaltera(right(p));
        if(altura(p)!=0){            
            vet[p]=op[valaleatorio(0,3)];
        }
    }
}



