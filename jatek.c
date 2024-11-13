#include <stdio.h>
#include <stdbool.h>
#include "jatek.h"

//Kisérleti változat
bool felfed(Palya *p, int y, int x){
    if(p->adat[y][x] >= 10 || y > p->magassag || x > p->szelesseg)
        return false;
    p->adat[y][x] += 10;
    return true;
}

void palya_kiir(Palya p){
    for(int y = 0; y < p.magassag; y++){
        for(int x = 0; x < p.szelesseg; x++){
            if(p.adat[y][x] < 10){printf("O ");}
            if(p.adat[y][x] == 10) {printf("  ");}
            if(p.adat[y][x] > 10 && p.adat[y][x] < 19) {printf("%d ",p.adat[x][y]-10);}
            if(p.adat[y][x] == 19) {printf("A ");}
        }
    printf("\n");
    }
}//Kész (még módosítva lesznek a kimenetek)
