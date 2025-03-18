#include <stdio.h>
#include <stdbool.h>
#include "mentes.h"
#include "palyakeszit.h"
#include "debugmalloc.h"

bool mentes(Palya *p){
    FILE* f;
    f = fopen("minesweeper_save.txt","w");
    if(f == NULL){
        fclose(f);
        return false;
    }

    fprintf(f, "%d %d %d %d %d\n",p->szelesseg, p->magassag, p->aknadb, p->masodperc, p->idozito);
    for(int y = 0; y < p->magassag; y++){
        for(int x = 0; x < p->szelesseg; x++){
            fprintf(f,"%d %d %d, ",p->adat[y][x].ertek, p->adat[y][x].jelolt ,p->adat[y][x].lefedett);
        }
        fprintf(f,"\n");
    }

    fclose(f);
    return true;
}
Palya *betoltes(Palya *p){
    FILE* f;
    Palya *bpalya = p;
    f = fopen("minesweeper_save.txt","r");
    if(f == NULL) {return NULL;}

    int temp;
    if (fscanf(f, "%d %d %d %d %d\n", &bpalya->szelesseg, &bpalya->magassag, &bpalya->aknadb, &bpalya->masodperc, &temp) != 5) {
        fclose(f);
        return NULL;
    }
    bpalya->idozito = temp;
    bpalya = palya_lefog(bpalya);
    for(int y = 0; y < p->magassag; y++){
        for(int x = 0; x < p->szelesseg; x++){
            int tjelolt, tlefedett;
            if(fscanf(f,"%d %d %d, ",&p->adat[y][x].ertek, &tjelolt ,&tlefedett) != 3){
                fclose(f);
                return NULL;
            }
            p->adat[y][x].jelolt = tjelolt;
            p->adat[y][x].lefedett = tlefedett;
        }
    }

    fclose(f);
    return bpalya;
}
