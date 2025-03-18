#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "jatek.h"
#include "econio.h"
#include "grafika.h"
#include "mentes.h"

static int felfed(Palya *p, int y, int x){
    if(!p->adat[y][x].lefedett || p->adat[y][x].ertek == 9)
        return 1;
    if(p->adat[y][x].ertek > 0){
        p->adat[y][x].lefedett = false;
        return 2;
    }
    p->adat[y][x].lefedett = false;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <=1; j++)
            if(y+i >= 0 && y+i < p->magassag && x+j >= 0 && x+j < p->szelesseg)
                if (felfed(p, y+i, x+j) == 0)
                    p->adat[y+i][x+j].lefedett = false;
    return 0;
}

static void megjelol(Palya *p, int y, int x){
    if(!p->adat[y][x].jelolt)
        p->adat[y][x].jelolt = true;
    else
        p->adat[y][x].jelolt = false;
}

static void stopper_veg(time_t start){
    time_t end;
    time(&end);
    int eltelt = difftime(end, start);
    printf("Eltelt idő: %d másodperc. \n",eltelt);
}

static bool idozito_veg(time_t start, Palya *p){
    if(p->idozito){
        time_t end;
        time(&end);
        double eltelt = difftime(end, start);
        if (eltelt > p->masodperc)
            return true;
    }
    return false;
}

static bool nyeres(Palya *p){
    int n = 0;
    for(int y = 0; y < p->magassag; y++)
        for(int x = 0; x < p->szelesseg; x++)
            if(p->adat[y][x].lefedett == true)
                n++;
    if(n == p->aknadb){
        printf("Gratulálunk Ön NYERT! *taps*\n");
        return true;
    }
    return false;
}

static bool vesztes(Palya *p, int y, int x){
    if(p->adat[y][x].ertek == 9){
        for(int i = 0; i < p->magassag; i++)
            for(int j = 0; j < p->szelesseg; j++)
                if(p->adat[i][j].ertek == 9)
                    p->adat[i][j].lefedett = false;
        palya_kiir(p);
        printf("Vesztettel.... :(\n");
        return true;
    }
    return false;
}

void jatek(Palya *p){
    palya_kiir(p);
    int y, x;
    char mod;
    time_t start;
    time(&start);
    while(true){
        fflush(stdin);
        printf("Válaszon ki egy mezőt (sor oszlop): ");
        if(scanf(" %c %d %d", &mod, &y, &x) != 3){
            printf("Hibás bemenet!\n");
            continue;
        }
        //Időzítő
        if(idozito_veg(start, p)){
            printf("Lejárt az idő, vége a játéknak.\n");
            printf("(0) Főmenü (1) Új játék (K) Kilépés\n");
            return;
        }
        //Mentés
        if(mod == 'm' || mod == 'M'){
            bool ment = mentes(p);
            if(ment)
                printf("A mentés sikeres.\n");
            continue;
        }
        //Kilépés
        else if(mod == 'K' || mod == 'k'){
            printf("(0) Főmenü (1) Új játék (K) Kilépés\n");
            return;
        }
        //Jelölés
        else if(mod == 'j' || mod == 'J'){
            //Index ellenőrzés
            if(x-1 < 0 || y-1 < 0 || x-1 > p->szelesseg || y-1 > p->magassag){
                printf("Nincs ilyen mező.\n");
                continue;
            }
            megjelol(p, y-1, x-1);
            palya_kiir(p);
        }
        //Felfedés
        else if(mod == 'f' || mod == 'F'){
            //Index ellenőrzés
            if(x-1 < 0 || y-1 < 0 || x-1 > p->szelesseg || y-1 > p->magassag){
                printf("Nincs ilyen mező.\n");
                continue;
            }
            //Vesztés
            if(vesztes(p, y-1, x-1)){
                if(!p->idozito) {stopper_veg(start);}
                printf("(0) Főmenü (1) Új játék (K) Kilépés\n");
                return;
            }
            //Felfedés
            int f = felfed(p, y-1, x-1);
            if(f == 1){
                printf("Ezt a mezőt már látod.\n");
                continue;
            }
            palya_kiir(p);
            //Nyerés
            if(nyeres(p)){
                if(!p->idozito) {stopper_veg(start);}
                printf("(0) Főmenü (1) Új játék (K) Kilépés\n");
                return;
            }
        }
        //Rossz mód
        else
            printf("Nincs ilyen mód.\n");
    }
}
