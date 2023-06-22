#include "Arv.h"
#include <iostream>
#include <time.h>
#include <stack>

using namespace std;

Arv::Arv(int tam) {
    max = tam;
    n = 0;
    vet = new char[max];
}

Arv::~Arv() {
    delete[] vet;
}

void Arv::criaArvoreAleatoria(int altura) {
    if (altura <= 0) {
        std::cout << "Altura inválida!" << std::endl;
        return;
    }

    criaSubArvoreAleatoria(0, altura);
}

void Arv::criaSubArvoreAleatoria(int indice, int altura) {
    if (indice >= max || altura <= 0) {
        return;
    }

    if (altura == 1) {
        vet[indice] = gerarNumeroAleatorio();
        n++;
    } else {
        if (rand() % 2 == 0) {
            vet[indice] = gerarOperadorAleatorio();
            n++;
            criaSubArvoreAleatoria(left(indice), altura - 1);
            criaSubArvoreAleatoria(right(indice), altura - 1);
        } else {
            vet[indice] = gerarNumeroAleatorio();
            n++;
        }
    }
}

char Arv::gerarNumeroAleatorio() {
    return '0' + rand() % 10;
}

char Arv::gerarOperadorAleatorio() {
    char operadores[4] = {'+', '-', '*', '/'};
    return operadores[rand() % 4];
}

int Arv::left(int i) {
    return 2 * i + 1;
}

int Arv::right(int i) {
    return 2 * (i + 1);
}

int Arv::parent(int i) {
    return (i - 1) / 2;
}

void Arv::imprime() {
    auxImprime(0);
    cout << endl;
}

void Arv::auxImprime(int i) {
    if (i < n) {
        auxImprime(left(i));
        auxImprime(right(i));
        std::cout << vet[i] << ", ";
    }
}

/*

int Arv::resolverOperacao() {
    stack<int> pilha;
    int resultado = 0;
    
    for (int i = 0; i < n; i++) {
        if (isdigit(vet[i])) {
            pilha.push(vet[i] - '0');
        } else {
            int b = pilha.top();
            pilha.pop();
            int a = pilha.top();
            pilha.pop();
            
            switch (vet[i]) {
                case '+':
                    pilha.push(a + b);
                    break;
                case '-':
                    pilha.push(a - b);
                    break;
                case '*':
                    pilha.push(a * b);
                    break;
                case '/':
                    pilha.push(a / b);
                    if (a == 0) {
                        cout << "Impossível realizar a operação: 0/0" << endl;
                        exit(1);
                    }
                    break;
                default:
                    cout << "Operador inválido: " << vet[i] << endl;
                    return 0;
            }
        }
    }
    
    if (!pilha.empty()) {
        resultado = pilha.top();
        pilha.pop();
    }
    
    if (!pilha.empty()) {
        cout << "Erro: operação inválida!" << endl;
        return 0;
    }
    
    return resultado;
}

*/