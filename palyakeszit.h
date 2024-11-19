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
}Palya;

Palya *palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb);

//void palya_felszab(Palya *p);

bool palya_betolt(Palya *p);

bool akna_feltolt(Palya *p);

bool szam_feltolt(Palya *p);

#endif // PALYAKESZIT_H
