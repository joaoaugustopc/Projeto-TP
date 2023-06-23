
#include "No.h"
#include <stack>
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
    void preencherPilha(int idx, std::stack<char> &pilha);

public:
    Arvore(int tam);
    ~Arvore();
    char getraiz();
    void criarvorealeatoria();
    void imprime();
    void preenchePilaAux(std::stack<char> &pilha);
};