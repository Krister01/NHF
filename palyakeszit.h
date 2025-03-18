#ifndef PALYAKESZIT_H
#define PALYAKESZIT_H

typedef struct Mezo{
    int ertek;
    bool lefedett;
    bool jelolt;
}Mezo;

typedef struct Palya{
    Mezo **adat;
    int szelesseg;
    int magassag;
    int aknadb;
    int masodperc;
    bool idozito;
}Palya;

bool egyedi_parameter(int *szelesseg, int *magassag, int *aknadb);

void palya_parameter(Palya *p, int magassag, int szelesseg, int aknadb);

Palya *palya_lefog(Palya *p);

void palya_felszab(Palya *p);

bool palya_keszit (Palya *p);
#endif // PALYAKESZIT_H
