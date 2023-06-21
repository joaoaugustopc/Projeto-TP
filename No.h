class No
{
private:
    char info;
    int Esq;
    int Dir;

public:
    No();
    ~No();
    void setEsq(int idx);
    void setDir(int idx);
    void setinfo(char val);
    int getEsq();
    int getDir();
    char getInfo();
};
