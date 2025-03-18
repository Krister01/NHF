#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "palyakeszit.h"
#include "debugmalloc.h"

bool egyedi_parameter(int *szelesseg, int *magassag, int *aknadb){
    printf("Adja meg a kívánt paramétereket (szelesseg magassag aknadb): ");
    fflush(stdin);
    int db = scanf("%d %d %d",szelesseg, magassag, aknadb);
    if(db != 3){
        printf("Csak számokat adj meg!\n");
        return false;
    }
    if(*szelesseg < 4 || *magassag < 4 ){
        printf("A pálya túl kicsi.\n");
        return false;
    }
    if(*szelesseg > 99 || *magassag > 99 ){
        printf("A pálya túl nagy.\n");
        return false;
    }
    if(*aknadb <= 0){
        printf("Legyen legalább egy akna!\n");
        return false;
    }
    if(*aknadb >= *szelesseg * *magassag){
        printf("Túl sok akna van");
        return false;
    }
    return true;
}

void palya_parameter(Palya *p, int magassag, int szelesseg, int aknadb){
    p->magassag = magassag;
    p->szelesseg = szelesseg;
    p->aknadb = aknadb;
}

Palya *palya_lefog(Palya *p){
    Palya *ujp = p;
    ujp->adat = (Mezo**) malloc(ujp->magassag * sizeof(Mezo*));
    if(ujp->adat == NULL) {return NULL;}
    for (int y = 0; y < ujp->magassag; y++){
        ujp->adat[y] = (Mezo*) malloc(ujp->szelesseg * sizeof(Mezo));
        if(ujp->adat[y] == NULL) {return NULL;}
    }
    return ujp;
}

void palya_felszab(Palya *p){
    for (int y = 0; y < p->magassag; y++)
        free(p->adat[y]);
    free(p->adat);
}

//Feltölti a pályát üres mezőkkel (0-kal) A használathoz meg kell adni egy "Palya" struktúrát
static bool palya_betolt(Palya *p){
    for(int y = 0; y < p->magassag; y++){
        for(int x = 0; x < p->szelesseg; x++){
            p->adat[y][x].ertek = 0;
            p->adat[y][x].lefedett = true;
            p->adat[y][x].jelolt = false;
        }
    }
    return true;
}

//Leellenőrzi, hogy egy tömbben benne van-e a keresett elem. A tömb méretét is meg kell adni!
static bool bennevan(int keresett, int *t, int meret){
    for (int i = 0; i < meret; i++)
        if (keresett == t[i])
            return true;
    return false;
}

//Feltölti a pálya véletlenül kiválasztott elemeit aknákkal (9-esekkel)
static bool akna_feltolt(Palya *p){
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

//Feltölti a pályát számokkal (1-8)
static bool szam_feltolt(Palya *p){
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

bool palya_keszit (Palya *p){
    if(!palya_betolt(p)) {return false;}
    if(!akna_feltolt(p)) {return false;}
    if(!szam_feltolt(p)) {return false;}
    return true;
}//Kész
