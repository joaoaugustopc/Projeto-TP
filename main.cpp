#include <iostream>
#include "Arvore.h"
#include <cstdlib>
#include <ctime>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Avaliacao.h"

using namespace std;

char *cabecalho(vector<vector<string>> &matriz, int *tam)
{
    *tam = matriz[0].size();
    char *vet = new char[*tam];
    for (int i = 0; i < *tam; i++)
    {
        istringstream ent(matriz[0][i]);
        ent >> vet[i];
    }

    return vet;
}

vector<vector<string>> learquivo()
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

void opera(Arvore *x, vector<vector<string>> matriz)
{
    stack<char> pilha;
    Avaliacao op;
    x->preenchePilaAux(pilha);
    for (int i = 1; i < 6; i++)
    {
        cout << "Resultado da operacao da linha " << i << " --> " << op.Operacao(pilha, i, matriz) << endl;
    }
}

int main()
{
    srand(time(NULL));
    vector<vector<string>> matriz = learquivo();
    int tamanho;
    char *vet = cabecalho(matriz, &tamanho);
    Arvore *a = new Arvore(20, vet, tamanho);
    a->criarvorealeatoria();
    a->imprime();
    cout << endl;

    opera(a, matriz);
}

// C:\Users\joaoa\Documents\dados.csv (x,y,z)
// C:\Users\joaoa\Downloads\csv.csv   (f,j,b)