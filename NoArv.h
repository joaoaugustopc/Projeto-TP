#ifndef NOARV_H
#define NOARV_H
class NoArv
{

private:
    double info;
    NoArv *esq;
    NoArv *dir;
    char tipo; // 0 = numero, 1 = variavel, 2 = operador

public:
    NoArv();
    ~NoArv();
    void setEsq(NoArv *p);
    void setInfo(double val);
    void setDir(NoArv *p);
    NoArv *getEsq();
    double getInfo();
    NoArv *getDir();
    void setTipo(char type);
    char getTipo();
    void limpaNo(NoArv* raizSub);
};

#endif