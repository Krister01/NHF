#include <stdio.h>
#include <stdbool.h>
#include "jatek.h"
#include "econio.h"

int felfed(Palya *p, int y, int x){
    if(!p->adat[y][x].lefedett || p->adat[y][x].ertek == 9)
        return 1;
    if(p->adat[y][x].ertek > 0){
        p->adat[y][x].lefedett = false;
        return 2;
    }
    p->adat[y][x].lefedett = false;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <=1; j++)
            if(y+i >= 0 && y+i < p->magassag && x+j >= 0 && x+j < p->szelesseg)
                if (felfed(p, y+i, x+j) == 0)
                    p->adat[y+i][x+j].lefedett = false;
    return 0;
}//Kész

void megjelol(Palya *p, int y, int x){
    p->adat[y][x].jelolt = true;
}//Kesz

bool nyeres(Palya p){
    int n = 0;
    for(int y = 0; y < p.magassag; y++)
        for(int x = 0; x < p.szelesseg; x++)
            if(p.adat[y][x].lefedett == true)
                n++;
    if(n == p.aknadb){
        return true;
    }
    return false;
}

bool vesztes(Palya *p, int y, int x){
    if(p->adat[y][x].ertek == 9){
        for(int i = 0; i < p->magassag; i++)
            for(int j = 0; j < p->szelesseg; j++)
                if(p->adat[i][j].ertek == 9)
                    p->adat[i][j].lefedett = false;
        return true;
    }
    return false;
}
