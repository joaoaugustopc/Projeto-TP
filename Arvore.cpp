#include"Arvore.h"
#include<iostream>
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
sobe(n-1);
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
    if(i<=n){
        auximprime(left(i));
        auximprime(right(i));
        cout<<vet[i]<<", ";
    }
}


