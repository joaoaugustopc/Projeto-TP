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
#include <math.h>
#include <time.h>
#include "OrdenaVet.h"

// #define TAM 50s
#define GERACAO 50
#define FAMILIA 500

using namespace std;

int gerarNumAleatorio(int a, int b) // Retornar um Numero dentro de uma faixa de valores
{
    return a + rand() % (b - a + 1);
}

char *cabecalho(vector<vector<string>> &matriz, int *tam) // funcao para retornar um vetor contendo o cabecalho do arquivo
{
    *tam = matriz[0].size();
    char *vet = new char[*tam];
    for (int i = 0; i < *tam; i++)
    {
        istringstream ent(matriz[0][i]); // tratar string como char
        ent >> vet[i];                   // guardar os caracteres no vetor
    }

    return vet;
}

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

/*void opera(Arv *x, vector<vector<string>> valoresFile) // função com nenhuma utilidade (antiga)
{
    stack<NoArv *> pilha;
    Avaliacao op;               // classe para realizar a operacao
    x->preenchePilhaAux(&pilha); // Funcao no MI para preencher a pilha com os nós da arvore
    for (int i = 1; i < 6; i++) // Laço para realizar as operacoes com os valores de cada linha do arquivo ( o contador é oque define a linha para ser considerada na operacao)
    {
        cout << "Resultado da operacao da linha " << i + 1 << " --> " << op.Operacao(&pilha, i, valoresFile) << endl;
    }
}*/

double operaReturn(Arv *arvPop, vector<vector<string>> valoresFile) // retornar soma da diferença,  ao quadrado, de uma arvore
{
    stack<NoArv *> pilha;
    Avaliacao resultOperacao;         // classe para realizar a operacao
    arvPop->preenchePilhaAux(&pilha); // Funcao no MI para preencher a pilha com os nós da arvore

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

void eficienciaArvores(Arv **vetorArvores, vector<vector<string>> valoresArquivo) // preeche um vetor com a aptidao de cada arvore (soma das diferenças)
{
    for (int i = 0; i < FAMILIA; i++)
    {
        vetorArvores[i]->setAptidao(operaReturn(vetorArvores[i], valoresArquivo)); // funcao que o algoritmo trava
    }
}

void gerarPopulacaoInicial(Arv **vetorPop, int alturaArv) // Função que Gera uma População Inical de Arvores
{
    for (int i = 0; i < FAMILIA; i++)
    {
        vetorPop[i]->criaArvAleatoria(alturaArv);
    }
}

void mutacao(Arv *arvore, char *cabecalho, int tam, int alturaArv) // funcao que Muta uma determinada arvore
{
    Arv *aux = new Arv(cabecalho, tam); // gera uma arvore aleatoria;
    aux->criaArvAleatoria(alturaArv);
    arvore->Muta(aux);
    delete aux;
}

void imprimeApt(Arv **Pop, int tam)
{
    for (int i = 0; i < tam; i++)
    {

        cout << "Aptidao da Arvore " << i + 1 << " " << Pop[i]->getAptidao() << endl;
    }
}
void substituirPopulacao(Arv **PopulacaoInicial, Arv **PopulacaoGenitores)
{

    OrdenaVet ordenacaoInicial;
    OrdenaVet ordenacaoGenitores;

    ordenacaoInicial.quickSort(PopulacaoInicial, FAMILIA);
    ordenacaoGenitores.quickSort(PopulacaoGenitores, FAMILIA);
    /*
     cout<<"APT INICIAL: "<<endl;
        imprimeApt(PopulacaoInicial,FAMILIA);
        cout<<"APT GENITORES: "<<endl;
        imprimeApt(PopulacaoGenitores,FAMILIA);
    */

    int elite = 5;
    int j = 0;
    for (int i = elite; i < FAMILIA; i++)
    {
        PopulacaoInicial[i]->clona(PopulacaoGenitores[j]);
        j++;
    }

    /*
    cout<<"APT INICIAL 2: "<<endl;
        imprimeApt(PopulacaoInicial,FAMILIA);
    // descobrindo o melhor e o Pior
    double melhor = PopulacaoInicial[0]->getAptidao();
    double pior = PopulacaoGenitores[0]->getAptidao();
    int idxMelhor = 0;
    int idxPior = 0;
    for (int i = 1; i < FAMILIA; i++)
    {
        if (abs(PopulacaoInicial[i]->getAptidao()) < abs(melhor))
        {
            melhor = PopulacaoInicial[i]->getAptidao();
            idxMelhor = i;
        }
        if (abs(PopulacaoGenitores[i]->getAptidao()) > abs(pior))
        {
            pior = PopulacaoGenitores[i]->getAptidao();
            idxPior = i;
        }
    }

    // realizando a substituicao
    int j = 0;
    int i = 0;
    for (; i < FAMILIA; i++)
    {
        if (i != idxMelhor)
        {
            if (j == idxPior)
            {
                j++;
            }
            if (j < FAMILIA)
            {
                PopulacaoInicial[i]->clona(PopulacaoGenitores[j]);
                j++;
            }
        }
    }
    */
}

int getPai(Arv **PopulacaoInicial)
{
    /*
    int idx1 = gerarNumAleatorio(0, FAMILIA - 1);
    int idx2 = gerarNumAleatorio(0, FAMILIA - 1);
    if (abs(PopulacaoInicial[idx1]->getAptidao()) < abs(PopulacaoInicial[idx2]->getAptidao()))
    {
        return idx1;
    }
    else
    {
        return idx2;
    }
    */

    int participantes = 4;
    int *idx = new int[participantes];
    idx[0] = gerarNumAleatorio(0, FAMILIA - 1);
    int menor = idx[0];
    for (int i = 1; i < participantes; i++)
    {
        idx[i] = gerarNumAleatorio(0, FAMILIA - 1);
        if (abs(PopulacaoInicial[idx[i]]->getAptidao()) < abs(PopulacaoInicial[menor]->getAptidao()))
        {
            menor = idx[i];
        }
    }

    delete[] idx;

    return menor;
}

void gerarVetorPop(char *cabecalho, int tam, Arv **arvore) // Função que Gera uma População
{
    for (int i = 0; i < FAMILIA; i++)
    {
        arvore[i] = new Arv(cabecalho, tam);
    }
}

void imprimePop(Arv **Pop, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        cout << "Arvore " << i + 1 << ": ";
        Pop[i]->imprime();
    }
}
void imprimeArv(Arv **Pop, int n)
{

    cout << "Arvore " << n << ": ";
    Pop[n - 1]->imprime();
    cout << endl;
    cout << "Arvore " << n << " em ordem: ";
    Pop[n - 1]->imprimeOrdem();
}

int main()
{
    // calcular tempo do programa
    double time_spent = 0;
    clock_t begin = clock();

    srand(time(0));
    Arv **PopulacaoInicial = new Arv *[FAMILIA];
    Arv **PopulacaoGenitores = new Arv *[FAMILIA];

    int qtdVariaveis;
    int alturaArvore = 5;
    vector<vector<string>> infoArquivo = learquivo();
    char *cabecalhoVet = cabecalho(infoArquivo, &qtdVariaveis); // função para extrair somente o cabecalho do arquivo e guardar o numero de colunas da matriz

    gerarVetorPop(cabecalhoVet, qtdVariaveis - 1, PopulacaoInicial); // Constroi avores em cada indice do vetor de população
    gerarVetorPop(cabecalhoVet, qtdVariaveis - 1, PopulacaoGenitores);
    gerarPopulacaoInicial(PopulacaoInicial, alturaArvore); // Preenchendo cada arvore do vetor População Inicial desconsiderando a ultima coluna (valesperado)
    eficienciaArvores(PopulacaoInicial, infoArquivo);      // avaliando População Inicial

    cout << "Imprime arvores iniciais e aptidao:" << endl;

    imprimePop(PopulacaoInicial, FAMILIA);
    cout << endl;
    imprimeApt(PopulacaoInicial, FAMILIA);

    int idxPai1;
    int idxPai2;

    for (int geracao = 0; geracao < GERACAO; geracao++)
    {
        cout << "GERACAO : " << geracao << endl;
        for (int i = 0; i < FAMILIA; i += 2)
        {
            idxPai1 = getPai(PopulacaoInicial);
            idxPai2 = getPai(PopulacaoInicial);
            PopulacaoGenitores[i]->clona(PopulacaoInicial[idxPai1]);
            PopulacaoGenitores[i + 1]->clona(PopulacaoInicial[idxPai2]);

            // <------------------- > criar uma função clone(fazer na mão)

            // processo de mutação e Recombinação
            PopulacaoGenitores[i]->Recombina(PopulacaoGenitores[i + 1]);
            mutacao(PopulacaoGenitores[i], cabecalhoVet, qtdVariaveis - 1, alturaArvore);
            mutacao(PopulacaoGenitores[i + 1], cabecalhoVet, qtdVariaveis - 1, alturaArvore);
        }

        eficienciaArvores(PopulacaoGenitores, infoArquivo);
        // avaliacao da Populacao de filhos
        // Faz a  Substituição de todoss os individuos salvando o melhor da População Inicial e matando o pior da População de Filhos;
        substituirPopulacao(PopulacaoInicial, PopulacaoGenitores);
    }

    OrdenaVet ordenacao;
    ordenacao.quickSort(PopulacaoInicial, FAMILIA);

    cout << endl
         << "RESUTADO FINAL : " << endl
         << endl;
    imprimeApt(PopulacaoInicial, FAMILIA);

    int idx;
    cout << "-----------------------------------" << endl;
    cout << "Digite o indice da arvore desejada para impressão ( Digite 0 para sair ): ";
    cin >> idx;
    while (idx > 0)
    {
        imprimeArv(PopulacaoInicial, idx);
        cout << "Digite o indice da arvore desejada para impressão ( Digite 0 para sair ): ";
        cin >> idx;
    }

    for (int i = 0; i < FAMILIA; i++)
    {
        delete PopulacaoInicial[i];
        delete PopulacaoGenitores[i];
    }

    delete[] PopulacaoInicial;
    delete[] PopulacaoGenitores;
    delete[] cabecalhoVet;

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    cout << "Tempo do programa: " << time_spent << "segundos.";

    return 0;
}

// C:\Users\joaoa\Documents\projetos\PROJETOS_TP\dados.csv (x,y,z)
// C:\Users\joaoa\Documents\projetos\PROJETOS_TP\dados.gsheet   (f,j,b)
// C:\Users\luiza\Downloads\dados.csv

// proximos passos :
/*
-> Gerar um vetor de arvores; Definir o tamnho do vetor (100);
-> Operação nova: avaliar arvores; avaliar todos os registros do Csv -> calcular diferença (ao quadrado) entre val esperado e valor da arvore e somar essa diferença de todas linhas
obs: quanto menor o resultado, melhor a arvore -- guardar o resultado em um novo parametro;
-> Definir um laço de geração de arvores de tamnho 100; Dentro - passos : 1 - Selecionar arvores progenitoras; 2 - sortear aleatoriamente duas arvores do vetor dee arv
3 - escolher a arvore com o melhor resultado e guardar em um vetor de progenitores -> colocar outro laco de repetição com o mesmo valor da população (tamanho);
obs : o progenitor tem que ser uma cópia da arvore escolhida - operação psra clone da arvore ( PONTEIROS DIFERENTES );
-> Com a populaçao de progenitores gerar uma nova população de arvores geradas a partir de mutação e recombinações dos proprios progenitores;
-> avaliar essas novas arvores;
-> para substituir as soluções : - indentificar a melhor solução que tinha na população original, indentificar a pior solução na população de filhos;
- Substituir todas os individuos salvando o melhor e matando o pior

*/

//--------------------------------------------------------------------------------------------------------------------------------------------

/*Arv *teste = new Arv(cabecalhoVet, tam); // passa um vetor guardando o cabecalho e o seu tamnho no construtor da arvore
Arv *teste2 = new Arv(cabecalhoVet, tam);

teste->criaArvAleatoria(5); // Preeche a arvore com valores aleatorios com altura maxima de 5
teste2->criaArvAleatoria(5);
cout << "Arvore 1 -- > ";
teste->imprime();
cout << "Arvore 2 --> ";
teste2->imprime();*/

// Recombinação
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*teste->Recombina(teste2); // funcao de recombinação
cout << "--------------------------------------" << endl;
cout << "Arvore 1 -- > ";
teste->imprime();
cout << "Arvore 2 --> ";
teste2->imprime();*/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Mutação
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*teste->Muta(teste2); // Muta a arvore teste substituindo um nó aleatorio com a arvore teste2 gerada aleatoriamente
cout<<"Arvore evoluida --> ";
teste->imprime();
cout<<"Nos-->"<<teste->getNos()<<endl;*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// operação
// opera(teste, matriz); // chama a função opera para realizar as operações substituindo as variaveis pelos valores correspondentes do arquivo fornecido
