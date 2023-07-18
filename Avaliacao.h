#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Avaliacao
{
private:
    float Auxoperacao(stack<char> &pilhaCopia)
    {
        // operacoes

        stack<float> pilhaResultado;
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
                        resultado = 0;
                    }
                    resultado = val1 / val2;
                    break;
                default:
                    cout << "Operador inválido!" << endl;
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
    };

public:
    Avaliacao(){};
    ~Avaliacao(){};
    float Operacao(stack<char> &pilha, int i, vector<vector<string>> matriz)
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
            int aux = 0;
            for (int j = 0; j < matriz[0].size(); j++)
            {
                istringstream trans(matriz[0][j]);
                char elemento;
                trans >> elemento;

                if (pilhaCopia.top() == elemento)
                {
                    istringstream ent(matriz[i][j]);
                    char val;
                    ent >> val;
                    pilhaCSV.push(val);
                    pilhaCopia.pop();
                    aux = 1;
                    break;
                }
            }
            if (aux == 0)
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

        return Auxoperacao(pilhaaux);
    };
};