#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include "Avaliacao.h"

using namespace std;

vector<vector<string>> learquivo(string fname) // funcao para ler e retornar o arquivo em forma de uma matriz
{
    /*
    string fname;
    cout << "Enter the file name: ";
    cin >> fname;
    */

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

double avalia(stack<Elemento> pilha, vector<vector<string>> &valoresFile)
{
    cout << "Avalia a arvore" << endl;
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
    cout << "Erro quadratico medio: " << diferencaValEsp / (qtdLinhasFile - 1) << endl;
    return (double)diferencaValEsp / (qtdLinhasFile - 1); // erro quadratico medio
}

double *getAptidoes(vector<vector<string>> dados, vector<vector<string>> Arvs)
{

    double *listaResultados = new double[Arvs.size()]; // vetor para armazenar os resultados das expressoes

    for (unsigned int i = 0; i < Arvs.size(); i++)
    {
        stack<Elemento> pilha;
        for (unsigned int j = 0; j < Arvs[i].size(); j++)
        {
            Elemento aux;
            aux.setInfo(Arvs[i][j]);
            pilha.push(aux);
        }

        listaResultados[i] = avalia(pilha, dados);
    }

    return listaResultados;
}

double medianaAptidoes(double *aptidoes, int tam)
{
    std::sort(aptidoes, aptidoes + tam);

    double mediana;
    if (tam % 2 == 0)
    {
        mediana = (aptidoes[(tam / 2) - 1] + aptidoes[tam / 2]) / 2.0;
    }
    else
    {
        mediana = aptidoes[tam / 2];
    }
    return mediana;
}

double IQRaptidoes(double *aptidoes, int tam)
{
    std::sort(aptidoes, aptidoes + tam);
    double Q1 = medianaAptidoes(aptidoes, tam / 2);
    double Q3 = medianaAptidoes(aptidoes + (tam + 1) / 2, tam / 2);
    return Q3 - Q1;
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <test_file> <tree_file>\n";
        return 1;
    }

    string testFile = argv[1];
    string treeFile = argv[2];

    double time_spent = 0;

    cout << "Lendo o arquivo com o(s) teste(s): " << testFile << endl;
    vector<vector<string>> dados = learquivo(testFile);
    cout << "Lendo o arquivo com a(s) arvore(s): " << treeFile << endl;
    vector<vector<string>> Arvs = learquivo(treeFile);

    // vetor de aptidoes de cada arvore
    clock_t begin = clock();

    double *aptidoes = getAptidoes(dados, Arvs);

    for (int i = 0; i < Arvs.size(); i++)
    {
        cout << "aptidao da arvore " << i << ": " << aptidoes[i] << endl;
        cout << aptidoes[i] << endl;
    }

    cout << "mediana dos testes: " << medianaAptidoes(aptidoes, Arvs.size()) << endl;
    cout << "iqr dos testes: " << IQRaptidoes(aptidoes, Arvs.size()) << endl;

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << endl
         << "Tempo do programa: " << time_spent << "segundos.";

    return 0;
}
