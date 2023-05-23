#include "NoArv.h"
#include<iostream>
using namespace std;

class Arv
{
private:
NoArv *raiz; 
NoArv* auxcria(NoArv *p, char val);
bool auxbusca(NoArv *p, char val);
NoArv*libera(NoArv*p);
void auxImprime(NoArv *p);
void auxaltera(NoArv*p);

public:
Arv();
~Arv();
int getRaiz();
void cria(char val);
bool vazia(); 
void imprime();
bool busca (char val); 
bool isoperator( char c);
int altura(NoArv*p);
void altera();
char valaleatorio(char a, char b);
};