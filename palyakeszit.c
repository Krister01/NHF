#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "palyakeszit.h"

bool palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb){
    p->szelesseg = szelesseg;
    p->magassag = magassag;
    p->aknadb = aknadb;
    p->adat = (int **) malloc(magassag * sizeof(int*));
    for (int y = 0; y < magassag; y++)
        p->adat[y] = (int *) malloc(szelesseg * sizeof(int));
    if (p->adat == NULL || p->adat[0] == NULL)
        return false;
    return true;
}
