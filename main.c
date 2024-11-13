#ifdef _WIN32
    #include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "palyakeszit.h"
#include "jatek.h"

int main(){
    #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(0));

    int w, h, ak;
    printf("Paraméterek (szélesség magasság aknák száma): "); scanf("%d %d %d",&w ,&h, &ak);

    /*Memória lefoglalása a pálya paramétereinek beállítása, a mátrix lefoglalása*/
    Palya p;
    p.magassag = h;
    p.szelesseg = w;
    p.aknadb = ak;
    p.adat = (int **) malloc(p.magassag * sizeof(int*));
    if(p.adat == NULL) {return 1;}
    for (int y = 0; y < p.magassag; y++){
        p.adat[y] = (int*) malloc (p.szelesseg * sizeof(int));
        if (p.adat[y] == NULL) {return 1;}
    }

    //Ideiglenes hibaüzenetek debugoláshoz
    bool a = ures_feltolt(&p);
    if (!a) {printf("Nincs 0...");}
    bool b = akna_feltolt(&p);
    if (!b) {printf("Nincs akna...");}
    bool c = szam_feltolt(&p);
    if (!c) {printf("Nincs szám :(");}

    //Játék:
    palya_kiir(p);
    int y, x;
    printf("Válaszon ki egy mezőt (sor oszlop): "); scanf("%d %d", &y, &x);
    while(y != -1 || x != -1){
        bool f = felfed(&p, y-1, x-1);
        if(!f){
            printf("Ezt a mezőt már látod, adj meg egy másikat! "); scanf("%d %d", &y, &x);
            continue;
        }
        palya_kiir(p);
        printf("Válaszon ki egy mezőt (sor oszlop): "); scanf("%d %d", &y, &x);
    }


    //Memória felszabadítás
    for (int y = 0; y < p.magassag; y++)
        free(p.adat[y]);
    free(p.adat);
}
