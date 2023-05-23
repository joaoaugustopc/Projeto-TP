
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
    Arv l;
cout<<"Inserindo valores: ";
for(int i=0;i<NUMNOS;i++){
    char val = numaleatorio(32,126);
    l.cria(val);
    cout<<val<<", ";
}
cout<<endl;
cout<<"Iprimindo a arvore em pos ordem: ";
l.imprime();
cout<<endl;
l.altera();
l.imprime();

return 0;
    
}