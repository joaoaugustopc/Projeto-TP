#include<iostream>
#include"Arvore.h"
#include <cstdlib> 
#include <ctime> 
#define NUMNOS 7

using namespace std;

char numaleatorio(char a, char b){
    return a + rand()%(b-a + 1);
}

int main(){
    srand(time(NULL));
    Arvore l(NUMNOS);
    cout<<"Inserindo valores: ";
    for(int i=0;i<NUMNOS;i++){
    char val = numaleatorio('0','9');
    l.insere(val);
    cout<<val<<", ";
}
cout<<endl;
l.imprime();
cout<<"\n------------------------------\n";
l.altera();
l.imprime();

}