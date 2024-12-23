#ifdef _WIN32
    #include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "econio.h"
#include "palyakeszit.h"
#include "jatek.h"
#include "grafika.h"

int main(){
    #ifdef _WIN32
            SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(0));

    //Memória lefoglalása a pálya paramétereinek beállítása, a mátrix lefoglalása

    int w, h, ak;
    printf("Paraméterek (szélesség magasság aknák száma): "); scanf("%d %d %d",&w ,&h, &ak);

    Palya *p = palya_lefog(w ,h ,ak);
    if (p == NULL) {return 1;}

    /*
    p.magassag = h;
    p.szelesseg = w;
    p.aknadb = ak;
    p.adat = (Mezo **) malloc(p.magassag * sizeof(Mezo*));
    if(p.adat == NULL) {return 1;}
    for (int y = 0; y < p.magassag; y++){
        p.adat[y] = (Mezo*) malloc (p.szelesseg * sizeof(Mezo));
        if (p.adat[y] == NULL) {return 1;}
    }
    */
    //Ideiglenes hibaüzenetek debugoláshoz
    bool a = palya_betolt(p);
    if (!a) {printf("Nincs 0...");}
    bool b = akna_feltolt(p);
    if (!b) {printf("Nincs akna...");}
    bool c = szam_feltolt(p);
    if (!c) {printf("Nincs szám :(");}

    //Játék:
    palya_kiir(p);
    int y, x;
    printf("Válaszon ki egy mezőt (sor oszlop): "); scanf("%d %d", &y, &x);
    while(y != -1 || x != -1){

        if(x-1 < 0 || y-1 < 0 || x-1 > p->szelesseg || y-1 > p->magassag){
            printf("Túlindexelsz!"); scanf("%d %d", &y, &x);
            continue;
        }

        if(vesztes(p, y-1, x-1)){
            palya_kiir(p);
            printf("Vesztettel.... :(\n");
            break;
        }
        int f = felfed(p, y-1, x-1);
        if(f == 1){
            printf("Ezt a mezőt már látod, adj meg egy másikat! "); scanf("%d %d", &y, &x);
            continue;
        }

        palya_kiir(p);

        if(nyeres(p)){
            printf("Gratulálunk Ön NYERT! *taps*\n");
            break;

        printf("Válaszon ki egy mezőt (sor oszlop): "); scanf("%d %d", &y, &x);
        }
    }


    //Memória felszabadítás
    for (int y = 0; y < p->magassag; y++)
        free(p->adat[y]);
    free(p->adat);
    free(p);
}
