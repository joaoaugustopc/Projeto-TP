#ifndef NOARV_H
#define NOARV_H
class NoArv
{

private:
    float info;
    NoArv *esq;
    NoArv *dir;
    char tipo; // 0 = numero, 1 = variavel, 2 = operador

public:
    NoArv();
    ~NoArv();
    void setEsq(NoArv *p);
    void setInfo(float val);
    void setDir(NoArv *p);
    NoArv *getEsq();
    float getInfo();
    NoArv *getDir();
    void setTipo(char type);
    char getTipo();
    void limpaNo(NoArv* raizSub);
};

#endif