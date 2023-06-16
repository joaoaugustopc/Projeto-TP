#ifndef ARV_H
#define ARV_H

class Arv{

    private:
    int max;
    int n;
    char* vet;
    void criaSubArvoreAleatoria(int indice, int altura);
    char gerarNumeroAleatorio();
    char gerarOperadorAleatorio();
    int left(int i);
    int right(int i);
    int parent(int i);
    void auxImprime(int i);
    bool isOperador(char c);
    char numAleatorio();

    public:
    Arv(int tam);
    ~Arv();
    void criaArvoreAleatoria(int altura);
    void imprime();
    int resolverOperacao();
    


};

#endif