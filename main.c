#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif

#include "debugmalloc.h"
#include "palyakeszit.h"

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    Palya p;
    p.magassag = 11;
    p.szelesseg = 11;
    p.aknadb = 3;
    p.adat = (int **) malloc(p.magassag * sizeof(int*));
    for (int y = 0; y < p.magassag; y++)
        p.adat[y] = (int*) malloc (p.szelesseg * sizeof(int));
    if(p.adat[0] == NULL || p.adat == NULL) {return 1;}

    for (int y = 0; y < p.magassag; y++)
        free(p.adat[y]);
    free(p.adat);
}
