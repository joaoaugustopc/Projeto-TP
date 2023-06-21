
#include "No.h"
class Arvore
{
private:
    int max;
    int n;
    No *vet;
    char gerarNumeroAleatorio();
    char gerarOperadorAleatorio();
    char valAleatorio();
    bool isOperador(char c);
    void auxcria(int idx);
    void auximprime(int idx);

public:
    Arvore(int tam);
    ~Arvore();
    char getraiz();
    void criarvorealeatoria();

    void imprime();
};