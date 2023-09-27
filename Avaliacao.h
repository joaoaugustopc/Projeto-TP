#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Avaliacao {

private:
public:
    Avaliacao(){};
    ~Avaliacao(){};

    float Operacao(stack<NoArv *> &pilha, int i, vector<vector<string>> matriz)
    {
        // criar copia da pilha original
        stack<NoArv *> pilhaTemp = pilha; // criar copia da pilha de nós
        stack<NoArv *> pilhaCopia;
        stack<float> pilhaResultado;



       /* while (!pilha.empty())
        {
            pilhaCopia.push(pilha.top());
            pilhaTemp.push(pilha.top());
            pilha.pop();
        }
        */

        while (!pilhaTemp.empty())
        {
            pilhaCopia.push(pilhaTemp.top());
            pilhaTemp.pop();
        }




        // realiza a operacao
        while (!pilhaCopia.empty())
        {
            if (pilhaCopia.top()->getTipo() == 2) // verifica se é um operador
            {
                char operacao = ((char)pilhaCopia.top()->getInfo()); // lida como um char
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
                    if (val2 == 0) // divisao protegida
                    {
                        resultado = 0;
                    }
                    else
                    {
                        resultado = val1 / val2;
                    }

                    break;
                default:
                    cout << "Operador inválido!" << endl;
                    exit(1);
                }

                pilhaResultado.push(resultado);
            }
            else if (pilhaCopia.top()->getTipo() == 0) // verifica se é um numero
            {
                pilhaResultado.push(pilhaCopia.top()->getInfo());
                pilhaCopia.pop();
            }
            else if (pilhaCopia.top()->getTipo() == 1) // verifica se é uma varialvel
            {
                for (int j = 0; j < matriz[0].size() - 1; j++) // retirar o valor esperado das operações
                {
                    istringstream trans(matriz[0][j]);
                    char elemento;
                    trans >> elemento;
                    char valor = ((char)pilhaCopia.top()->getInfo());

                    if (valor == elemento) // encontrar a coluna correspondente ao elemento da pilha
                    {
                        // "i" é a linha escolhida para selecionar os valores (escolhida na main)
                        istringstream ent(matriz[i][j]); // altera para o numero correspondente (float)
                        float val;
                        ent >> val;
                        pilhaResultado.push(val);
                        pilhaCopia.pop();
                        break;
                    }
                }
            }
        }

        return pilhaResultado.top();
    };
};