#include "NoArv.h"
#include <iostream>

using namespace std;

NoArv::NoArv() {
    esq = NULL;
    dir = NULL;
}

NoArv::~NoArv() {}

void NoArv::setEsq(NoArv *p){
    esq = p;
}

void NoArv::setDir(NoArv *p){
    dir = p;
}

void NoArv::setInfo(int val){
    info = val;
}

NoArv* NoArv::getEsq(){
    return esq;
}

NoArv* NoArv::getDir(){
    return dir;
}

int NoArv::getInfo(){
    return info;
}