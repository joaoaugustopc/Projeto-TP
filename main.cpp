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

#define TAM 100

using namespace std;

int gerarNumAleatorio(int a, int b)     // Retornar um Numero dentro de uma faixa de valores 
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

void opera(Arv *x, vector<vector<string>> valoresFile)
{
    stack<NoArv *> pilha;
    Avaliacao op;               // classe para realizar a operacao
    x->preenchePilhaAux(pilha); // Funcao no MI para preencher a pilha com os nós da arvore
    for (int i = 1; i < 6; i++) // Laço para realizar as operacoes com os valores de cada linha do arquivo ( o contador é oque define a linha para ser considerada na operacao)
    {
        cout << "Resultado da operacao da linha " << i + 1 << " --> " << op.Operacao(pilha, i, valoresFile) << endl;
    }
}

float operaReturn(Arv *arvPop, vector<vector<string>> valoresFile)  // retornar soma da diferença,  ao quadrado, de uma arvore
{ 
    stack<NoArv *> pilha;
    Avaliacao resultOperacao;        // classe para realizar a operacao
    arvPop->preenchePilhaAux(pilha); // Funcao no MI para preencher a pilha com os nós da arvore

    int qtdLinhasFile = valoresFile.size();

    float diferencaValEsp = 0;

    int indiceValEsperado = valoresFile[0].size() - 1;

    for (int i = 1; i < qtdLinhasFile; i++)
    {
        istringstream ent(valoresFile[i][indiceValEsperado]);
        float valEsperado;
        ent >> valEsperado;
        diferencaValEsp += pow(valEsperado - resultOperacao.Operacao(pilha, i, valoresFile), 2);
    }

    return diferencaValEsp;
}

void eficienciaArvores(vector<Arv *> vetorArvores, float *aptidoes, vector<vector<string>> valoresArquivo)  // preeche um vetor com a aptidao de cada arvore (soma das diferenças)
{ 
    int qtdArvores = vetorArvores.size();
    for (int i = 0; i < qtdArvores; i++)
    {
        aptidoes[i] = operaReturn(vetorArvores[i], valoresArquivo);
    }
}

vector<Arv *> gerarPopulacaoInicial(char *cabecalho, int tam)  // Função que Gera uma População Inical de Arvores 
{
    int tamPopulacao = TAM;
    vector<Arv *> arvPopulacao(tamPopulacao, NULL); // vetor de arvores

    for (int i = 0; i < tamPopulacao; i++)
    {
        arvPopulacao[i] = new Arv(cabecalho, tam);
        arvPopulacao[i]->criaArvAleatoria(5);
    }

    return arvPopulacao;
}
void mutacao(Arv *arvore, char *cabecalho, int tam)  // funcao que Muta uma determinada arvore 
{
    Arv *aux = new Arv(cabecalho, tam);  // gera uma arvore aleatoria;
    aux->criaArvAleatoria(5);
    arvore->Muta(aux);
}

void substituirPopulacao(vector<Arv *> PopulacaoInicial, vector<Arv *> PopulacaoGenitores, float *aptidoes, float *aptidoesFilhos)
{
    float melhor = aptidoes[0];
    float pior = aptidoesFilhos[0];
    int idxMelhor = 0;
    int idxPior = 0;
    for (int i = 1; i < PopulacaoInicial.size(); i++)
    {
        if (abs(aptidoes[i]) < abs(melhor))
        {
            melhor = aptidoes[i];
            idxMelhor = i;
        }
        if (abs(aptidoesFilhos[i]) > abs(pior))
        {
            pior = aptidoesFilhos[i];
            idxPior = i;
        }
    }
    int j = 0;
    for (int i = 0; i < PopulacaoInicial.size(); i++)
    {
        if (i == idxMelhor)
        {
            continue;
        }
        else
        {
            if (j == idxPior)
            {
                delete PopulacaoGenitores[j];
                j++;
            }
            delete PopulacaoInicial[i];
            PopulacaoInicial[i] = PopulacaoGenitores[j];
            aptidoes[i] = aptidoesFilhos[j];
            j++;
            delete PopulacaoGenitores[j];
        }
    }
}

int main()
{

    srand(time(NULL));
    vector<Arv *> PopulacaoInicial;
    vector<Arv *> PopulacaoGenitores(TAM, NULL);

    float aptidoes[TAM];       // vetor que guarda as aptidões da Populacao Inicial
    float aptidoesFilhos[TAM]; // vetor que guarda as aptidoes da Populacao gerada a partir da mutacao e recombinação de genitores
    int tamanhoCabecalho;

    vector<vector<string>> matriz = learquivo();
    char *cabecalhoVet = cabecalho(matriz, &tamanhoCabecalho); // função para extrair somente o cabecalho do arquivo

    PopulacaoInicial = gerarPopulacaoInicial(cabecalhoVet, tamanhoCabecalho); // gerando População Inicial
    eficienciaArvores(PopulacaoInicial, aptidoes, matriz);                    // avaliando População Inicial

    int idxPai1;
    int idxPai2;

    for (int geracao = 0; geracao < TAM; geracao++)
    {

        for (int i = 0; i < TAM; i += 2)
        {

            // Processo de Cópia de arvores selecionadas
            idxPai1 = gerarNumAleatorio(0, PopulacaoInicial.size() - 1);
            idxPai2 = gerarNumAleatorio(0, PopulacaoInicial.size() - 1);
            PopulacaoGenitores[i] = new Arv(cabecalhoVet, tamanhoCabecalho);
            *PopulacaoGenitores[i] = *PopulacaoInicial[idxPai1];
            PopulacaoGenitores[i + 1] = new Arv(cabecalhoVet, tamanhoCabecalho);
            *PopulacaoGenitores[i + 1] = *PopulacaoInicial[idxPai2];

            // processo de mutação e Recombinação
            mutacao(PopulacaoGenitores[i], cabecalhoVet, tamanhoCabecalho);
            mutacao(PopulacaoGenitores[i + 1], cabecalhoVet, tamanhoCabecalho);
            PopulacaoGenitores[i]->Recombina(PopulacaoGenitores[i + 1]);

            // avaliacao da Populacao de filhos
            eficienciaArvores(PopulacaoGenitores, aptidoesFilhos, matriz);
        }

        // Faz a  Substituição de todoss os individuos salvando o melhor da População Inicial e matando o pior da População de Filhos;
        substituirPopulacao(PopulacaoInicial, PopulacaoGenitores, aptidoes, aptidoesFilhos);
    }

    // deletar
    for (int i = 0; i < PopulacaoInicial.size(); i++)
    {
        delete PopulacaoInicial[i];
        delete PopulacaoGenitores[i];
    }

    return 0;
}

// C:\Users\joaoa\Documents\dados.csv (x,y,z)
// C:\Users\joaoa\Downloads\csv.csv   (f,j,b)

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
