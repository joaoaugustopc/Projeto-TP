#include <string>
#include <regex>

using namespace std;

class Elemento
{
private:
    string info;
    char type; // 1 para operador1, 2 para operador 2, 3 para numero e 0 para variavel;
    bool isOperator1(string str)
    {
        return (str == "e" || str == "#" || str == "$" || str == "&" || str == "!"); // expoente de e, raiz quadrada, seno, tangente hiperbólica, log
    }

    bool isOperator2(string str)
    {
        return (str == "+" || str == "-" || str == "*" || str == "/" || str == "^"); // soma, subtração, multiplicação, divisão, potenciação
    }

    bool isVariavel(string str)
    {
        return ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z'));
    }

public:
    string getInfo()
    {
        return info;
    }
    void setInfo(string information)
    {
        info = information;

        if (isOperator1(info))
        {
            type = 1;
        }
        else if (isOperator2(info))
        {
            type = 2;
        }
        else if (isVariavel(info))
        {
            type = 3;
        }
        else
        {
            type = 0;
        }
    }
    char getType()
    {
        return type;
    }
};