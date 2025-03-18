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
#include "menu.h"
#include "mentes.h"

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    srand(time(0));
    //Pálya inicializálása
    Palya *p = (Palya*) malloc(sizeof(Palya));
    if (p == NULL) {return 1;}
    p->masodperc = 0;
    p->idozito = false;

    enum Menu menu = FOMENU;
    fomenukiir();
    bool run = true;
    while(run){
        switch(menu){
            case FOMENU:
                fomenukiir();
                menu = fomenutovabb();
                break;
            case NEHEZSEGM:
                nehezsegmkiir();
                menu = nehezsegmtovabb(p);
                break;
            case JATEK:
                p = palya_lefog(p);
                if(p == NULL) {return 1;}
                if(!palya_keszit(p)) {return 1;}
                jatek(p);
                palya_felszab(p);
                menu = szabaly_jatekmtovabb();
                break;
            case BJATEK:
                p = betoltes(p);
                if(p == NULL) {return 1;}
                jatek(p);
                palya_felszab(p);
                menu = szabaly_jatekmtovabb();
                break;
            case SZABALYOK:
                szabalykiir();
                menu = szabaly_jatekmtovabb();
                break;
            case KILEPES:
                run = false;
                break;
        }
    }
    free(p);
    return 0;
}
