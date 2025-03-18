#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "econio.h"
#include "palyakeszit.h"
#include "jatek.h"
#include "debugmalloc.h"

void fomenukiir(void){
    econio_clrscr();
    printf("   ___  ____                                                          \n"
        "   |  \\/  (_)                                                           \n"
        "   | .  . |_ _ __   ___  _____      _____  ___ _ __   ___ _ __           \n"
        "   | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
        "   | |  | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |          \n"
        "   \\_|  |_/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|      \n"
        "                                              | |                        \n"
        "                                              |_|                        \n");
    printf("(1) Játék (2) Szabályok (K) Kilépés\n");
}

enum Menu fomenutovabb(void){
    econio_rawmode();
    while(true){
        int key = econio_getch();
        switch(key){
            case '1':
                econio_normalmode();
                return NEHEZSEGM;
            case '2':
                econio_normalmode();
                return SZABALYOK;
            case 'K':
            case 'k':
                econio_normalmode();
                return KILEPES;
            default:
                continue;
        }
    }
}
void nehezsegmkiir(void){
    econio_clrscr();
    printf("Válassz nehézséget!\n");
    printf("(1) Könnyű (2) Közepes (3) Nehéz (4) Analízis zh. (5) Egyedi (I) Időlimit be/ki\n");
    printf("(B) Legutóbbi mentés betöltése (0) Vissza a főmenübe (K) Kilépés\n");
}

enum Menu nehezsegmtovabb(Palya *p){
    econio_rawmode();
    while(true){
        int key = econio_getch();
        switch(key){
            case '0':
                return FOMENU;
            case '1':
                econio_normalmode();
                palya_parameter(p, 8, 8 ,10);
                return JATEK;
            case '2':
                econio_normalmode();
                palya_parameter(p, 16, 16 ,40);
                return JATEK;
            case '3':
                econio_normalmode();
                palya_parameter(p, 16, 30 ,99);
                return JATEK;
            case '4':
                econio_normalmode();
                palya_parameter(p, 40, 40 ,450);
                return JATEK;
            case '5':
                econio_normalmode();
                int szelesseg, magassag, aknadb;
                bool helyes = false;
                while(!helyes){
                    helyes = egyedi_parameter(&szelesseg, &magassag, &aknadb);
                }
                palya_parameter(p, magassag, szelesseg, aknadb);
                return JATEK;
            case 'I':
            case 'i':
                econio_normalmode();
                if(p->idozito){
                    p->idozito = false;
                    p->masodperc = 0;
                    printf("Idő limit kikapcsolva.\n");
                }
                else{
                    p->idozito = true;
                    while(true){
                        printf("Hány másodperc legyen? ");
                        if(scanf("%d",&p->masodperc) != 1)
                            break;
                        else
                            printf("Hibás bemenet!\n");
                    }
                }
                econio_rawmode();
                continue;
            case 'B':
            case 'b':
                econio_normalmode();
                return BJATEK;
            case 'K':
            case 'k':
                econio_normalmode();
                return KILEPES;
            default:
                continue;
        }
    }
}

void szabalykiir(void){
    econio_clrscr();
    printf("Hogyan kell játszani:\n"
        "A játék célja a mezőn lévő összes akna megtalálása, illetve azok elkerülése. A játéktér        \n"
        "lefedett mezőkből áll ezek felfedés után lehetnek üres mezők, számos mezők vagy                \n"
        "aknás mezők. Az üres mezők és azok szomszédai nem tartalmaznak aknákat. A számos               \n"
        "mezők azt mutatják, hogy a körlöttük lévő 8 mezőn, hány darab akna található. A játékosnak     \n"
        "lehetősége van megjelölni azokat a cellákat, amiken szerinte akna található. A játék akkor ér  \n"
        "véget, ha a játékos felfedte az összes bombát NEM tartalmazó mezőt, ekkor nyer, vagy           \n"
        "felfedett egy aknát tartalmazó mezőt, ebben az esetben a játékos vesztett. \n");
    printf("(0) Vissza a főmenübe (1) Játék (K) Kilépés\n");
}
enum Menu szabaly_jatekmtovabb(void){
    econio_rawmode();
    while(true){
        int key = econio_getch();
        switch(key){
            case '0':
                econio_normalmode();
                return FOMENU;
            case '1':
                econio_normalmode();
                return NEHEZSEGM;
            case 'K':
            case 'k':
                econio_normalmode();
                return KILEPES;
            default:
                continue;
        }
    }
}
