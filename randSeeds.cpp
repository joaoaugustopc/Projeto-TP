#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main()
{
    // Abrir o arquivo para escrita
    std::ofstream arquivo("seeds.txt");

    // Verificar se o arquivo foi aberto corretamente
    if (!arquivo)
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    // Gerar números aleatórios e escrevê-los no arquivo
    std::srand(std::time(nullptr)); // Inicializar a semente do gerador de números aleatórios
    for (int i = 0; i < 9; i++)     // Alterado para 9 para evitar pular linha na última execução
    {
        int numero = std::rand() % 10001; // Gerar número aleatório entre 0 e 10000
        arquivo << numero << std::endl;   // Escrever o número no arquivo
    }

    int numero = std::rand() % 10001; // Gerar número aleatório entre 0 e 10000
    arquivo << numero;                // Escrever o número no arquivo sem pular linha

    // Fechar o arquivo
    arquivo.close();

    std::cout << "Números gerados e salvos no arquivo seeds.txt." << std::endl;

    return 0;
}
