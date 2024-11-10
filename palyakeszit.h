#ifndef PALYAKESZIT_H
#define PALYAKESZIT_H

typedef struct Palya{
    int **adat;
    int szelesseg;
    int magassag;
    int aknadb;
}Palya;
/*
typedef struct Mezo{
    int x, y, sorszam;
}Mezo;
*/
bool palya_lefog(Palya *p, int szelesseg, int magassag, int aknadb);

void palya_felszab(Palya *p);

bool ures_feltolt(Palya *p);

bool akna_feltolt(Palya *p);

bool szam_feltolt(Palya *p);

#endif // PALYAKESZIT_H
