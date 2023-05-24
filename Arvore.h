class Arvore{
private:
int max;
int n;
char *vet;
void sobe(int i);
void desce(char i);
void auximprime(int i); 

public:
Arvore(int tam);
~Arvore();
char getraiz();
void insere(char val);
void imprime();
int left(int i);
int right(int i);
int pai(int i);
};