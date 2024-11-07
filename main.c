#ifdef _WIN32
    #include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "debugmalloc.h"
#include "palyakeszit.h"

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(0));

    int w, h, ak;
    printf("Paraméterek (szélesség, magasság, aknák száma): "); scanf("%d %d %d",&w ,&h, &ak);

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

    bool a = ures_feltolt(&p);
    if (!a) {printf("Nincs 0...");}
    bool b = akna_feltolt(&p);
    if (!b) {printf("Nincs akna...");}

    for(int y = 0; y < p.magassag; y++){
        for(int x = 0; x < p.szelesseg; x++)
            printf("%d ",p.adat[y][x]);
        printf("\n");
    }

    for (int y = 0; y < p.magassag; y++)
        free(p.adat[y]);
    free(p.adat);
}
