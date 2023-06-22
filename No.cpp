#include "No.h"
#include <iostream>

using namespace std;

No::No()
{
    Esq = -1;
    Dir = -1;
}

No::~No()
{
}

void No::setEsq(int idx)
{
    Esq = idx;
}

void No::setDir(int idx)
{
    Dir = idx;
}

void No::setinfo(char val)
{
    info = val;
}

int No::getEsq()
{
    return Esq;
}

int No::getDir()
{
    return Dir;
}

char No::getInfo()
{
    return info;
}