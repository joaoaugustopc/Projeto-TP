#ifndef NOARV_H
#define NOARV_H

class NoArv{

    private:
    NoArv *esq;
    NoArv *dir;
    int info;

    public:
    NoArv();
    ~NoArv();
    void setEsq(NoArv *p);
    void setDir(NoArv *p);
    void setInfo(int val);
    NoArv* getEsq();
    NoArv* getDir();
    int getInfo();

};


#endif