#include "NoArv.h"
#include<iostream>
using namespace std;

NoArv::NoArv() {}

NoArv::~NoArv() {}

void NoArv::setEsq(NoArv *p) { esq = p;}

void NoArv::setInfo(int val) { info = val;}

void NoArv::setDir(NoArv *p) { dir = p;}

NoArv* NoArv::getEsq() { return esq;}

char NoArv::getInfo() { return info;}

NoArv* NoArv::getDir() { return dir;}