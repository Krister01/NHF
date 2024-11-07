#ifndef PALYAKESZIT_H
#define PALYAKESZIT_H

typedef struct Palya{
    int **adat;
    int szelesseg, magassag;
    int aknadb;
}Palya;

bool palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb);

#endif // PALYAKESZIT_H
