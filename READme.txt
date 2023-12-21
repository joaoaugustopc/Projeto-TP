Funcionamento do script:

PARA TREINAMENTO
-> Os argumentos passados são: arquivo de leitura, semente, número da função analisada, quantidade de dados para treinamento
-> Para o registro das melhores árvores, é preciso criar um arquivo csv no folder TESTE_POP/Arquivos_Arvores/ do tipo: avaliacaoFuncao(numeroDaFuncao)_arvores(numeroDeTestes).csv

PARA TESTES:
-> Os argumentos passados são: número da função analisada e quantidade de dados para treinamento
-> Para execução correta, criar os seguintes arquivos:
    1. para guardar os 50k dados de teste: funcao(numeroDaFuncao)_teste50k.csv
    2. para guardar as árvores, já foi passado anteriormente