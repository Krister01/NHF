#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
#endif

#include "debugmalloc.h"
#include "palyakeszit.h"
int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    Palya p;
    int w = 30;
    int h = 30;
    int akna = 5;

    bool a = palya_lefog(&p,w,h,akna);
    if (!a) {return 1;}

    for (int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            p.adat[j][i] = 0;
            printf("%d ",p.adat[j][i]);
        }
        printf("\n");
    }

    for (int y = 0; y < h; ++y)
        free(p.adat[y]);
    free(p.adat);

    return 0;
}
