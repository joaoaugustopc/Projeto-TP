#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include "Avaliacao.h"

using namespace std;

vector<vector<string>> learquivo() // funcao para ler e retornar o arquivo em forma de uma matriz
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
    return content; // retornar matriz com os valores da tabela
}

double avalia(stack<string> pilha, vector<vector<string>> valoresFile)
{
    Avaliacao resultOperacao;
    int qtdLinhasFile = valoresFile.size();

    double diferencaValEsp = 0;

    int indiceValEsperado = valoresFile[0].size() - 1;

    for (int i = 1; i < qtdLinhasFile; i++)
    {
        istringstream ent(valoresFile[i][indiceValEsperado]);
        double valEsperado;
        ent >> valEsperado;
        diferencaValEsp += pow(valEsperado - resultOperacao.Operacao(pilha, i, valoresFile), 2);
    }

    return (double)diferencaValEsp / qtdLinhasFile - 1; // erro quadratico medio
}

double *getAptidoes(vector<vector<string>> dados, vector<vector<string>> Arvs)
{

    double *listaResultados = new double[Arvs.size()]; // vetor para armazenar os resultados das expressoes

    for (unsigned int i = 0; i < Arvs.size(); i++)
    {
        stack<string> pilha;
        for (unsigned int j = 0; j < Arvs[i].size(); j++)
        {
            pilha.push(Arvs[i][j]);
        }
        listaResultados[i] = avalia(pilha, dados);
    }

    return listaResultados;
}

int main()
{
    cout << "Digite o arquivo com o(s) teste(s)" << endl;
    vector<vector<string>> dados = learquivo();
    cout << "Digite o arquivo com a(s) arvore(s)" << endl;
    vector<vector<string>> Arvs = learquivo();
    double *aptidoes = getAptidoes(dados, Arvs);
    for (int i = 0; i < Arvs.size(); i++)
    {
        cout << aptidoes[i] << endl;
    }
    return 0;
}
