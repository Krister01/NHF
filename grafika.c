#include <stdio.h>
#include <stdbool.h>
#include "grafika.h"
#include "econio.h"


void palya_kiir(Palya *p){
    econio_clrscr();
    for(int x = 0; x < p->szelesseg+1; x++){
        if(x == 0) {printf("   ");}
        else if(x < 9) {printf("%d  ", x);}
        else {printf("%d ",x);}
    }
    printf("\n");

    for(int y = 0; y < p->magassag; y++){
        if (y < 9) {printf("%d ",y+1);}
        else {printf("%d",y+1);}
        for(int x = 0; x < p->szelesseg; x++){
            econio_textbackground(COL_YELLOW);
            econio_textcolor(COL_BLACK);
            if(p->adat[y][x].lefedett){printf(" O ");}
            else if(p->adat[y][x].jelolt) {printf(" P ");}
            else if(p->adat[y][x].ertek == 0) {printf("   ");}
            else if(p->adat[y][x].ertek == 9) {econio_textcolor(COL_RED); printf(" X "); econio_textcolor(COL_BLACK);}
            else {printf(" %d ",p->adat[y][x].ertek);}
            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        }
        printf("\n");
    }
    printf("\n");
}//Kész (még módosítva lesznek a kimenetek)
