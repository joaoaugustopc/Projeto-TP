#include <iostream>
#include "Arvore.h"
#include <random>
#include <ctime>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<string>> f1()
{
    string fname;
    cout << "Enter the file name: ";
    cin >> fname;

    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else
    {

        cout << "Could not open the file\n";
    }
    return content;
}

float AUXoperacao(stack<char> &pilhaCopia)
{

    // operacoes

    std::stack<float> pilhaResultado;
    while (!pilhaCopia.empty())
    {
        if (pilhaCopia.top() == '+' || pilhaCopia.top() == '-' || pilhaCopia.top() == '*' || pilhaCopia.top() == '/')
        {
            char operacao = pilhaCopia.top();
            pilhaCopia.pop();

            if (pilhaResultado.size() < 2)
            {
                cout << "erro de tamanho" << endl;
                exit(1);
            }

            float val2 = pilhaResultado.top();
            pilhaResultado.pop();
            float val1 = pilhaResultado.top();
            pilhaResultado.pop();

            float resultado;

            switch (operacao)
            {
            case '+':
                resultado = val1 + val2;
                break;
            case '-':
                resultado = val1 - val2;
                break;
            case '*':
                resultado = val1 * val2;
                break;
            case '/':
                if (val2 == 0)
                {
                    cout << "Impossível dividir 0 por um número!" << endl;
                    exit(1);
                }
                resultado = val1 / val2;
                break;
            default:
                std::cout << "Operador inválido!" << std::endl;
                exit(1);
            }

            pilhaResultado.push(resultado);
        }
        else if (isdigit(pilhaCopia.top()))
        {
            pilhaResultado.push(pilhaCopia.top() - '0');
            pilhaCopia.pop();
        }
        else
        {
            cout << "operacao invalida" << endl;
            exit(1);
        }
    }

    return pilhaResultado.top();
}

float operacao(stack<char> &pilha, int i, vector<vector<string>> matriz)
{
    // criar copia da pilha original
    stack<char> pilhaTemp;
    stack<char> pilhaCopia;
    stack<char> pilhaCSV;
    stack<char> pilhaaux;

    while (!pilha.empty())
    {
        pilhaCopia.push(pilha.top());
        pilhaTemp.push(pilha.top());
        pilha.pop();
    }

    while (!pilhaTemp.empty())
    {
        pilha.push(pilhaTemp.top());
        pilhaTemp.pop();
    }

    while (!pilhaCopia.empty())
    {
        if (pilhaCopia.top() == 'x')
        {
            istringstream ent(matriz[i][0]);
            char val;
            ent >> val;
            pilhaCSV.push(val);
            pilhaCopia.pop();
        }
        else if (pilhaCopia.top() == 'y')
        {
            istringstream ent(matriz[i][1]);
            char val;
            ent >> val;
            pilhaCSV.push(val);
            pilhaCopia.pop();
        }
        else if (pilhaCopia.top() == 'z')
        {
            istringstream ent(matriz[i][2]);
            char val;
            ent >> val;
            pilhaCSV.push(val);
            pilhaCopia.pop();
        }
        else
        {
            pilhaCSV.push(pilhaCopia.top());
            pilhaCopia.pop();
        }
    }
    while (!pilhaCSV.empty())
    {
        pilhaaux.push(pilhaCSV.top());
        pilhaCSV.pop();
    }

    return AUXoperacao(pilhaaux);
}

void pilha(Arv *x)
{
    stack<char> pilha;
    x->preenchePilhaAux(pilha);
    vector<vector<string>> matriz = f1();
    for (int i = 1; i < 6; i++)
    {
        cout << "Resultado da operacao da linha " << i << " --> " << operacao(pilha, i, matriz) << endl;
    }
}

int main()
{

    srand(time(NULL));
    Arv *teste = new Arv;

    teste->criaArvAleatoria(5);

    teste->imprime();

    cout << endl;
    // cout << teste.resolverExpressao() << endl;
    pilha(teste);

    return 0;
}