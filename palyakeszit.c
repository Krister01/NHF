#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "palyakeszit.h"

Palya *palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb){
    Palya *ujpalya = p;
    ujpalya->szelesseg = szelesseg;
    ujpalya->magassag = magassag;
    ujpalya->aknadb = aknadb;
    ujpalya->adat = (Mezo**) malloc(magassag * sizeof(Mezo*));
    if(ujpalya->adat == NULL) {return NULL;}
    for (int y = 0; y < magassag; y++)
        ujpalya->adat[y] = (Mezo*) malloc(szelesseg * sizeof(Mezo));
    return ujpalya;
}


/*Feltölti a pályát üres mezőkkel (0-kal) A használathoz meg kell adni egy "Palya" struktúrát*/
bool palya_betolt(Palya *p){
    for(int y = 0; y < p->magassag; y++){
        for(int x = 0; x < p->szelesseg; x++){
            p->adat[y][x].ertek = 0;
            p->adat[y][x].lefedett = true;
            p->adat[y][x].jelolt = false;
        }
    }
    return true;
}//Kész

/*Leellenőrzi, hogy egy tömbben benne van-e a keresett elem. A tömb méretét is meg kell adni!  */
static bool bennevan(int keresett, int *t, int meret){
    for (int i = 0; i < meret; i++)
        if (keresett == t[i])
            return true;
    return false;
}//Kész

/*Feltölti a pálya véletlenül kiválasztott elemeit aknákkal (9-esekkel)*/
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
        p->adat[y][x].ertek = 9;
    }
    free(ak);
    return true;
}//Kész

/*Feltölti a pályát számokkal (1-8)*/
bool szam_feltolt(Palya *p){
    for(int y = 0; y < p->magassag; y++)
        for(int x = 0; x < p->szelesseg; x++)
            if(p->adat[y][x].ertek != 9)
                for(int i = -1; i<= 1; i++)
                    for(int j = -1; j<= 1; j++)
                        if(y+i >= 0 && y+i < p->magassag && x+j >= 0 && x+j < p->szelesseg)
                            if(p->adat[y+i][x+j].ertek == 9)
                                p->adat[y][x].ertek++;
    return true;
}//Kész
