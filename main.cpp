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

#define TAM 6

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

void opera(Arv *x, vector<vector<string>> valoresFile) // função com nenhuma utilidade (antiga)
{
    stack<NoArv *> pilha;
    Avaliacao op;               // classe para realizar a operacao
    x->preenchePilhaAux(pilha); // Funcao no MI para preencher a pilha com os nós da arvore
    for (int i = 1; i < 6; i++) // Laço para realizar as operacoes com os valores de cada linha do arquivo ( o contador é oque define a linha para ser considerada na operacao)
    {
        cout << "Resultado da operacao da linha " << i + 1 << " --> " << op.Operacao(pilha, i, valoresFile) << endl;
    }
}

float operaReturn(Arv *arvPop, vector<vector<string>> valoresFile) // retornar soma da diferença,  ao quadrado, de uma arvore
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

void eficienciaArvores(vector<Arv *> vetorArvores, vector<vector<string>> valoresArquivo) // preeche um vetor com a aptidao de cada arvore (soma das diferenças)
{
    int qtdArvores = vetorArvores.size();
    for (int i = 0; i < qtdArvores; i++)
    {
        vetorArvores[i]->setAptidao(operaReturn(vetorArvores[i], valoresArquivo));

        // teste
        cout << "Imprime arvores" << i << ": ";
        vetorArvores[i]->imprime();
        cout << "Aptidao da arvore " << i << ": " << vetorArvores[i]->getAptidao() << endl;

        // teste
    }
}

vector<Arv *> gerarPopulacaoInicial(char *cabecalho, int tam, int alturaArv) // Função que Gera uma População Inical de Arvores
{
    int tamPopulacao = TAM;
    vector<Arv *> arvPopulacao(tamPopulacao, NULL); // vetor de arvores obs: passar altura arvore como parametro

    for (int i = 0; i < tamPopulacao; i++)
    {
        arvPopulacao[i] = new Arv(cabecalho, tam);
        arvPopulacao[i]->criaArvAleatoria(alturaArv);
    }

    return arvPopulacao;
}
void mutacao(Arv *arvore, char *cabecalho, int tam, int alturaArv) // funcao que Muta uma determinada arvore
{
    Arv *aux = new Arv(cabecalho, tam); // gera uma arvore aleatoria;
    aux->criaArvAleatoria(alturaArv);
    arvore->Muta(aux);
    delete aux;
}

void substituirPopulacao(vector<Arv *> PopulacaoInicial, vector<Arv *> PopulacaoGenitores)
{
    // descobrindo o melhor e o Pior
    float melhor = PopulacaoInicial[0]->getAptidao();
    float pior = PopulacaoGenitores[0]->getAptidao();
    int idxMelhor = 0;
    int idxPior = 0;
    for (int i = 1; i < PopulacaoInicial.size(); i++)
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
    for (; i < PopulacaoInicial.size(); i++)
    {
        if (i == idxMelhor)
        {
            continue;
        }
        else
        {
            if (j == idxPior)
            {
                PopulacaoGenitores[j]->liberar();
                j++;
            }
            if (j < PopulacaoGenitores.size())
            {
                PopulacaoInicial[i]->liberar();
                PopulacaoInicial[i]->clona(PopulacaoGenitores[j]);
                PopulacaoGenitores[j]->liberar();
                j++;
            }
        }
    }
    if (j < i) //  caso o ultimo elemento do genitor for o pior
    {
        PopulacaoGenitores[j]->liberar();
    }
}

int getPai(vector<Arv *> PopulacaoInicial)
{
    int idx1 = gerarNumAleatorio(0, PopulacaoInicial.size() - 1);
    int idx2 = gerarNumAleatorio(0, PopulacaoInicial.size() - 1);
    if (PopulacaoInicial[idx1]->getAptidao() < PopulacaoInicial[idx2]->getAptidao())
    {
        return idx1;
    }
    else
    {
        return idx2;
    }
}

vector<Arv *> gerarVetorDeGenitores(char *cabecalho, int tam) // Função que Gera uma População Inical de Arvores
{
    int tamPopulacao = TAM;
    vector<Arv *> arvPopulacao(tamPopulacao, NULL); // vetor de arvores obs: passar altura arvore como parametro

    for (int i = 0; i < tamPopulacao; i++)
    {
        arvPopulacao[i] = new Arv(cabecalho, tam);
    }

    return arvPopulacao;
}

int main()
{

    srand(time(NULL));
    vector<Arv *> PopulacaoInicial; // Estudar algum jeito de alocar um vetor de classe que precisa de um construtor;
    vector<Arv *> PopulacaoGenitores;

    int qtdVariaveis;
    int alturaArvore = 5;

    vector<vector<string>> infoArquivo = learquivo();
    char *cabecalhoVet = cabecalho(infoArquivo, &qtdVariaveis); // função para extrair somente o cabecalho do arquivo e guardar o numero de colunas da matriz

    PopulacaoInicial = gerarPopulacaoInicial(cabecalhoVet, qtdVariaveis - 1, alturaArvore); // gerando População Inicial desconsiderando a ultima coluna (valesperado)
    eficienciaArvores(PopulacaoInicial, infoArquivo);                                       // avaliando População Inicial
    PopulacaoGenitores = gerarVetorDeGenitores(cabecalhoVet, qtdVariaveis - 1);
    int idxPai1;
    int idxPai2;

    for (int geracao = 0; geracao < TAM; geracao++)
    {

        for (int i = 0; i < TAM; i += 2)
        {

            // Processo de Cópia de arvores selecionadas

            // <-------->  Sortear 2 e ver qual é o melhor e guardar no idxPai1, fazer o mesmo processo e guardar no idxPai2

            idxPai1 = getPai(PopulacaoInicial);
            idxPai2 = getPai(PopulacaoInicial);
            PopulacaoGenitores[i]->clona(PopulacaoInicial[idxPai1]);
            PopulacaoGenitores[i + 1]->clona(PopulacaoInicial[idxPai2]);
            // <------------------- > criar uma função clone(fazer na mão)

            // processo de mutação e Recombinação
            PopulacaoGenitores[i]->Recombina(PopulacaoGenitores[i + 1]);
            //mutacao(PopulacaoGenitores[i], cabecalhoVet, qtdVariaveis, alturaArvore);
            //mutacao(PopulacaoGenitores[i + 1], cabecalhoVet, qtdVariaveis, alturaArvore);
        }
        // teste
        cout << "Arvores apos processos de mutacao e recombinacao: " << endl;
        // teste
        eficienciaArvores(PopulacaoGenitores, infoArquivo);
        // avaliacao da Populacao de filhos

        // Faz a  Substituição de todoss os individuos salvando o melhor da População Inicial e matando o pior da População de Filhos;
        cout << "substituicao" << endl;
        substituirPopulacao(PopulacaoInicial, PopulacaoGenitores);
    }

    // teste
    cout << "Populacao apos substituicao:" << endl;
    for (int i = 0; i < PopulacaoGenitores.size() - 1; i++)
    {
        cout << "Resultado da avaliacao arvore " << i << ": " << operaReturn(PopulacaoInicial[i], infoArquivo) << endl;
    }
    // teste

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
