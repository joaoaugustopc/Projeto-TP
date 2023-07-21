
#include "No.h"
#include <stack>
class Arvore
{
private:
    int max;
    int n;
    char *vetor;
    int tamanho;
    No *vet;
    int gerarNumeroAleatorio();
    char gerarOperadorAleatorio();
    int valAleatorio();
    bool isOperador(char c);
    void auxcria(int idx);
    void auximprime(int idx);
    void preencherPilha(int idx, std::stack<char> &pilha);

public:
    Arvore(int tam, char *cabecalho, int i);
    ~Arvore();
    char getraiz();
    void criarvorealeatoria();
    void imprime();
    void preenchePilaAux(std::stack<char> &pilha);
};