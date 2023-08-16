#include <iostream>
#include "Arvore.h"
#include <random>
#include <ctime>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Avaliacao.h"

using namespace std;

char *cabecalho(vector<vector<string>> &matriz, int *tam)  // funcao para retornar um vetor contendo o cabecalho do arquivo 
{
    *tam = matriz[0].size();
    char *vet = new char[*tam];
    for (int i = 0; i < *tam; i++)
    {
        istringstream ent(matriz[0][i]); // tratar string como char
        ent >> vet[i]; // guardar os caracteres no vetor
    }

    return vet;
}

vector<vector<string>> learquivo() //funcao para ler e retornar o arquivo em forma de uma matriz 
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
    } else {
        cout << "Could not open the file\n";
    }
    return content; // retornar matriz com os valores da tabela
}

void opera(Arv *x, vector<vector<string>> matriz)
{
    stack<NoArv *> pilha; 
    Avaliacao op; // classe para realizar a operacao
    x->preenchePilhaAux(pilha); //Funcao no MI para preencher a pilha com os nós da arvore
    for (int i = 1; i < 6; i++) //Laço para realizar as operacoes com os valores de cada linha do arquivo ( o contador é oque define a linha para ser considerada na operacao)
    {
        cout << "Resultado da operacao da linha " << i + 1 << " --> " << op.Operacao(pilha, i, matriz) << endl;
    }
}

int main()
{

    srand(time(NULL));
    vector<vector<string>> matriz = learquivo();
    int tam;
    char *vet = cabecalho(matriz, &tam);  // função para extrair somente o cabecalho do arquivo
    Arv *teste = new Arv(vet, tam); // passa um vetor guardando o cabecalho e o seu tamnho no construtor da arvore
    Arv *teste2 = new Arv(vet, tam);

    teste->criaArvAleatoria(5); // Preeche a arvore com valores aleatorios com altura maxima de 5
    teste2->criaArvAleatoria(5);
    cout << "Arvore 1 -- > ";
    teste->imprime();
    cout << "Arvore 2 --> ";
    teste2->imprime();



    // Recombinação
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    teste->Recombina(teste2); // funcao de recombinação
    cout << "--------------------------------------" << endl;
    cout << "Arvore 1 -- > ";
    teste->imprime();
    cout << "Arvore 2 --> ";
    teste2->imprime();

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



    //Mutação
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    /*teste->Muta(teste2); // Muta a arvore teste substituindo um nó aleatorio com a arvore teste2 gerada aleatoriamente
    cout<<"Arvore evoluida --> ";
    teste->imprime();
    cout<<"Nos-->"<<teste->getNos()<<endl;*/
    
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //operação
    //opera(teste, matriz); // chama a função opera para realizar as operações substituindo as variaveis pelos valores correspondentes do arquivo fornecido

    return 0;
}

// C:\Users\joaoa\Documents\dados.csv (x,y,z)
// C:\Users\joaoa\Downloads\csv.csv   (f,j,b)
