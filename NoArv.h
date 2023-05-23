class NoArv{
private:
char info;
NoArv* esq;
NoArv* dir;
public:
NoArv() ;
~NoArv();
void setEsq(NoArv *p);
void setInfo(int val);
void setDir(NoArv *p);
NoArv* getEsq(); 
char getInfo();
NoArv* getDir();
};