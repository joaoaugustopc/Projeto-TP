#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <math.h>
#include <cctype>
#include <string>
#include <limits>
#include <cctype>
#include <regex>


using namespace std;

class Avaliacao
{

private:
    bool isOperator1(string str)
    {
        return (str == "e" || str == "#" || str == "$" || str == "&" || str == "!"); // expoente de e, raiz quadrada, seno, tangente hiperbólica, log
    }

    bool isOperator2(string str)
    {
        return (str == "+" || str == "-" || str == "*" || str == "/" || str == "^"); // soma, subtração, multiplicação, divisão, potenciação
    }

    bool isNumero(string &str)
    {
        regex e("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");

        if (regex_match(str, e))
            return true;

        return false;
    }

public:
    Avaliacao(){};
    ~Avaliacao(){};

    double Operacao(stack<string> &pilha, int i, vector<vector<string>> matriz)
    {
        // criar copia da pilha original
        stack<string> pilhaTemp = pilha; // criar copia da pilha de nós
        stack<string> pilhaCopia;
        stack<double> pilhaResultado;

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

            if (isOperator1(pilhaCopia.top())) // verifica se é uma operador de apenas um parâmetro

            {
                char operacao = (pilhaCopia.top())[0]; // get the first character from the string
                pilhaCopia.pop();

                if (pilhaResultado.size() < 1)
                {
                    cout << "erro de tamanho" << endl;
                    exit(1);
                }

                double val1 = pilhaResultado.top();
                pilhaResultado.pop();

                double resultado;

                switch (operacao)
                {
                case 'e': // expoente de e
                    if (std::isinf(exp(val1)))
                    {
                        resultado = std::numeric_limits<double>::infinity();
                    }
                    resultado = exp(val1); // ignorar o segundo valor
                    break;
                case '#': // raiz quadrada
                    if (val1 < 0)
                    {
                        resultado = val1;
                    }
                    else
                    {
                        resultado = sqrt(val1);
                    }
                    break;
                case '$': // seno
                    if (std::isinf(sin(val1)))
                    {
                        resultado = std::numeric_limits<double>::infinity();
                    }
                    resultado = sin(val1);
                    break;
                case '&':
                    if (std::isinf(tanh(val1)))
                    {
                        resultado = std::numeric_limits<double>::infinity();
                    }
                    resultado = tanh(val1);
                    break;
                case '!': // log
                    if (val1 <= 0)
                    {
                        resultado = val1;
                    }
                    else
                    {
                        resultado = log(val1);
                    }
                    break;
                default:
                    cout << "Operador inválido!" << endl;
                    exit(1);
                }

                pilhaResultado.push(resultado);
            }

            else if (isOperator2(pilhaCopia.top())) // verifica se é um operador
            {
                char operacao = (pilhaCopia.top())[0]; // lida como um char
                pilhaCopia.pop();

                if (pilhaResultado.size() < 2)
                {
                    cout << "erro de tamanho" << endl;
                    exit(1);
                }

                double val2 = pilhaResultado.top();
                pilhaResultado.pop();
                double val1 = pilhaResultado.top();
                pilhaResultado.pop();

                double resultado;

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
                    if (abs(val2) < 0.00001) // divisao protegida
                    {
                        resultado = 1;
                    }
                    else
                    {
                        resultado = val1 / val2;
                    }
                    break;
                case '^':
                    if (val1 < 0 && fmod(val2, 1.0) != 0)
                    {
                        resultado = 1;
                    }
                    else if (val1 < 0 && std::isinf(val2))
                    {
                        resultado = 0;
                    }
                    else
                    {
                        resultado = pow(val1, val2);
                    }
                    break;
                default:
                    cout << "Operador inválido!" << endl;
                    exit(1);
                }

                pilhaResultado.push(resultado);
            }
            else if (isNumero(pilhaCopia.top())) // verifica se é um numero
            {
                stringstream ent(pilhaCopia.top());
                double val;
                ent >> val;
                pilhaResultado.push(val);
                pilhaCopia.pop();
            }
            else if (isalpha((pilhaCopia.top())[0])) // verifica se é uma varialvel
            {
                char valor = (pilhaCopia.top())[0];
                string::size_type colunaValEsp = matriz[0].size();
                for (string::size_type j = 0; j < colunaValEsp - 1; j++) // retirar o valor esperado das operações
                {
                    istringstream trans(matriz[0][j]);
                    char elemento;
                    trans >> elemento;

                    if (valor == elemento) // encontrar a coluna correspondente ao elemento da pilha
                    {
                        // "i" é a linha escolhida para selecionar os valores (escolhida na main)
                        istringstream ent(matriz[i][j]); // altera para o numero correspondente (double)
                        double val;
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