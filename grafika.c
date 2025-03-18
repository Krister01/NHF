#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "grafika.h"
#include "econio.h"

//Az InfoC-n megtalálható Unicode -> UTF-8 konvertáló függvény
void unicode_2_utf8(uint16_t const *be, uint8_t *ki) {
    int pk = 0;
    for (int pb = 0; be[pb] != 0; ++pb) {
        if (be[pb] <= 0x007F) {
            // 00000000 0xxxxxxx, 0x0000-0x007F
            // 0xxxxxxx
            ki[pk++] = be[pb];
        } else if (be[pb] <= 0x07FF) {
            // 00000yyy yyxxxxxx, 0x0080-0x07FF
            // 110yyyyy 10xxxxxx
            ki[pk++] = 0xC0 | be[pb] >> 6;      // 0xC0 = 11000000
            ki[pk++] = 0x80 | (be[pb] & 0x3F);  // 0x80 = 10000000, 0x3F = 00111111
        } else {
            // zzzzyyyy yyxxxxxx, 0x0800-0xFFFF
            // 1110zzzz 10yyyyyy 10xxxxxx
            ki[pk++] = 0xE0 | be[pb] >> 12;     // 0xE0 = 11100000
            ki[pk++] = 0x80 | ((be[pb] >> 6) & 0x3F);
            ki[pk++] = 0x80 | (be[pb] & 0x3F);
        }
    }
    ki[pk] = 0;
}



void palya_kiir(Palya *p){
    uint16_t kocka[2] = {0x25A0,'\0'};
    uint8_t kocka_utf8[4];
    uint16_t kor[2] = {0x25CF,'\0'};
    uint8_t kor_utf8[4];
    unicode_2_utf8(kocka, kocka_utf8);
    unicode_2_utf8(kor, kor_utf8);

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

            if(p->adat[y][x].jelolt){
                    econio_textcolor(COL_BLUE);
                    printf(" P ");
            }
            else if(p->adat[y][x].lefedett)
                printf(" %s ",kocka_utf8);
            else if(p->adat[y][x].ertek == 0){
                econio_textbackground(COL_LIGHTGRAY);
                printf("   ");
            }
            else if(p->adat[y][x].ertek == 9){
                econio_textcolor(COL_RED);
                printf(" %s ", kor_utf8);
            }
            else
                printf(" %d ",p->adat[y][x].ertek);

            econio_textbackground(COL_RESET);
            econio_textcolor(COL_RESET);
        }
        printf("\n");
    }
    printf("\n");
}//Kész (még módosítva lesznek a kimenetek)
