#include <iostream>
#include "Arvore.h"
#include <random>
#include <math.h>

class OrdenaVet
{

private:
    void troca(Arv **a, Arv **b)
    {
        Arv *aux = *a;
        *a = *b;
        *b = aux;
    }
    int pivoAleatorio(int ini, int fim)
    {
        int pos = ini + rand() % ((fim - ini) + 1);
        return pos;
    }

    int medianaDeTres(Arv **v, int ini, int fim)
    {
        int meio = (ini + fim) / 2;
        if (abs(v[ini]->getAptidao()) > abs(v[fim]->getAptidao()))
            troca(&v[ini], &v[fim]);
        if (abs(v[meio]->getAptidao()) > abs(v[fim]->getAptidao()))
            troca(&v[meio], &v[fim]);
        if (abs(v[ini]->getAptidao()) > abs(v[meio]->getAptidao()))
            troca(&v[ini], &v[meio]);
        return meio;
    }

    int particionaH(Arv **v, int ini, int fim)
    {
        // int pivopos = (ini+fim)/2;
        int pivopos = pivoAleatorio(ini, fim);
        // int pivopos = medianaDeTres(v, ini, fim);
        Arv *pivo = v[pivopos];

        int i = ini - 1, j = fim + 1;
        do
        {
            do
            {
                i++;
            } while (abs(v[i]->getAptidao()) < abs(pivo->getAptidao()));
            do
            {
                j--;
            } while (abs(v[j]->getAptidao()) > abs(pivo->getAptidao()));
            if (i >= j)
                return j;
            troca(&v[i], &v[j]);
        } while (true);
    }

    void quickSortRec(Arv **v, int ini, int fim)
    {
        if (ini < fim)
        {
            int p = particionaH(v, ini, fim);
            quickSortRec(v, ini, p);
            quickSortRec(v, p + 1, fim);
            return;
        }
    }

public:
    OrdenaVet() {}
    ~OrdenaVet() {}
    void quickSort(Arv **v, int n)
    {
        quickSortRec(v, 0, n - 1);
    }
};