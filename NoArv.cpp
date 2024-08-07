#include "NoArv.h"
#include <iostream>
using namespace std;

NoArv::NoArv()
{
    esq = NULL;
    dir = NULL;
}

NoArv::~NoArv() {}

void NoArv::setEsq(NoArv *p) { esq = p; }

void NoArv::setInfo(double val) { info = val; }

void NoArv::setDir(NoArv *p) { dir = p; }

NoArv *NoArv::getEsq() { return esq; }

double NoArv::getInfo() { return info; }

NoArv *NoArv::getDir() { return dir; }

void NoArv ::setTipo(char type) { tipo = type; }

char NoArv ::getTipo() { return tipo; }

void NoArv::limpaNo(NoArv* raizSub){
    info = raizSub->getInfo();
    tipo = raizSub->getTipo();
}