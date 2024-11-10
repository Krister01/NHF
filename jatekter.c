#include <stdio.h>
#include <stdbool.h>
#include "jatekter.h"

//Lefoglalja a memóriát a játéktér adait tároló mátrixnak.
bool dinmat_fog(DinMat *dm, int szelesseg, int magassag){
    dm->szelesseg = szelesseg;
    dm->magassag = magassag;
    dm->adat = (int**) malloc(dm->magassag * sizeof(int*));
    dm->adat[0] = (int*) malloc(dm->szelesseg * dm->magassag * sizeof(int));
    for (int i = 1; i < dm->magassag; i++)
        dm->adat[i] = dm->adat[0] + i * szelesseg;
    return dm->adat != NULL;
}//Kesz

//Felszabadít egy mátrixot
void dinmat_fel(DinMat *dm){
    free(dm->adat[0]);
    free(dm);
}//Kesz


/*
// A mező X és Y koordinátájából kiszámítja a mező sorszámát
void xy2sorszam_1(Mezo *m, int szelesseg, int magassag){
    m->sorszam = (m->x - 1) * szelesseg + (m->y - 1) * magassag;
} */

// Egy X és Y koordinátából sorszámot csinál
int xy2sorszam(int x, int y, int szelesseg, int magassag){
    return x * szelesseg + y * magassag;
}//Kesz

// Meghatározza egy mezo koordinátáit a sorszáma alapján
void sorszam2xy(Mezo *m, Palya *p){
    m->x = m->sorszam % p->dm.szelesseg;
    m->y = (m->sorszam - m->x * p->dm.szelesseg) / p->dm.magassag;
}//Kesz

// Meghatározza a kezdő mező és a körlüttőe lévő mezők sorszámát, ezeket eltárolja a paraméterként kapott tömbben.
void kezdomezok(int *k,int *meret, Mezo m, Palya *p){
    int k_index = 0;
    for (int i = -1; i == 1; i++)
        for(int j = -1; j == 1; j++)
            if (m.x+i >= 0 && m.y+j >= 0 && m.x+i < p->dm.szelesseg && m.y+j < p->dm.magassag){
                k[k_index] = xy2sorszam(m.x+i,m.y+j,p->dm.magassag,p->dm.szelesseg);
                k_index++;
                meret++;
            }
} //Kesz


// Feltölti a játék pálya mátrixát aknákkal (kilencesekkel)
bool aknafeltoltes(int *kezdes,int meret, Palya *p){
    Mezo m;
    int n = p->dm.magassag * p->dm.szelesseg;
    int *aknaksorszam = (int *) malloc(n * sizeof(int));
    if (aknaksorszam == NULL) {return false;}
    for (int i = 0; i < p->aknadb; i++){
        m.sorszam = rand() % n;
        sorszam2xy(&m,p);
        if (bennevan(m.sorszam,kezdes,meret))
            i--;
        else
            p->dm.adat[m.y][m.x] = 9;
    }
    free(aknaksorszam);
    return true;
}

//Feltölti a pályát aknákkal, számokkal és üres mezõkkel
bool palya_kitoltes(Palya *p, Mezo kezdomezo){
    int kezdes[9];
    int meret = 0;
    kezdomezok(&kezdes,&meret,kezdomezo, p);
    bool af = aknafeltoltes(kezdes,meret,p);
    if(!af) {return false;}

    return true;
}
