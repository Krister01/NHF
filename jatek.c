#include <stdio.h>
#include <stdbool.h>
#include "jatek.h"


bool felfed(Palya *p, int y, int x){
    int n = 0;
    for(int i = -1; i<= 1; i++){
        for(int j = -1; j<= 1; j++){
            if(y+i >= 0 && y+i < p->magassag && x+j >= 0 && x+j < p->szelesseg){
                if(p->adat[y+i][x+j].ertek == 0 && p->adat[y+i][x+j].lefedett)
                    n++;
                if(p->adat[y+i][x+j].ertek < 9)
                    p->adat[y+i][x+j].lefedett = false;
            }
        }
    }
    if(n == 0) {return false;}
    for(int i = -1; i<= 1; i++)
        for(int j = -1; j<= 1; j++)
            if(y+i >= 0 && y+i < p->magassag && x+j >= 0 && x+j < p->szelesseg)
                if(p->adat[y+i][x+j].ertek == 0)
                    if(felfed(p, y+i, x+j))
                        p->adat[y+i][x+j].lefedett = false;
    return true;
}//Kész

void palya_kiir(Palya p){
    for(int y = 0; y < p.magassag; y++){
        for(int x = 0; x < p.szelesseg; x++){
            if(p.adat[y][x].lefedett){printf("O ");}
            else if(p.adat[y][x].jelolt) {printf("P ");}
            else if(p.adat[y][x].ertek == 0) {printf("  ");}
            else if(p.adat[y][x].ertek == 9) {printf("X ");}
            else {printf("%d ",p.adat[y][x].ertek);}
        }
        printf("\n");
    }
}//Kész (még módosítva lesznek a kimenetek)
