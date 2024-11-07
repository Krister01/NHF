#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "palyakeszit.h"

bool palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb){
    p->szelesseg = szelesseg;
    p->magassag = magassag;
    p->aknadb = aknadb;
    p->adat = (int **) malloc(magassag * sizeof(int*));
    for (int y = 0; y < magassag; y++)
        p->adat[y] = (int *) malloc(szelesseg * sizeof(int));
    if (p->adat == NULL)
        return false;
    return true;
} // Nem m�k�dik f�ggv�nyk�nt csak mainen bel�l

void palya_felszab(Palya *p){
    for (int y = 0; y < p->magassag; ++y)
        free(p->adat[y]);
    free(p->adat);
} //Nem m�k�dik f�ggv�nyk�nt csak mainen bel�l

bool ures_feltolt(Palya *p){
    for(int y = 0; y < p->magassag; y++)
        for(int x = 0; x < p->szelesseg; x++)
            p->adat[y][x] = 0;
    return true;
}//K�sz

bool bennevan(int keresett, int *t, int meret){
    for (int i = 0; i < meret; i++)
        if (keresett == t[i])
            return true;
    return false;
}//K�sz

bool akna_feltolt(Palya *p){
    int *ak = (int*) malloc(p->aknadb* sizeof(int));
    if (ak == NULL) {return false;}
    int aknahely;
    for (int i = 0; i < p->aknadb; i++){
        aknahely = rand() % (p->magassag * p->szelesseg);
        if (!bennevan(aknahely,ak,i))
            ak[i] = aknahely;
        else
            i--;
    }
    int x, y;
    for (int i = 0; i < p->aknadb;i++){
        x = ak[i] % p->szelesseg;
        y = ak[i] / p->szelesseg;
        p->adat[y][x] = 9;
    }
    free(ak);
    return true;
}//K�sz

