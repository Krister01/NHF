#ifndef JATEKTER_H
#define JATEKTER_H

typedef struct DinMat{
    int **adat;
    int szelesseg, magassag;
}DinMat;

typedef struct Palya{
    DinMat dm;
    int aknadb;
}Palya;

typedef struct Mezo{
    int x, y, sorszam;
}Mezo;

//bool dinmat_fog(DinMat *dm, int szelesseg, int magassag);

void dinmat_fel(DinMat *dm);

//bool palya_kitoltes(Palya *p, Mezo kezdomezo);
#endif // JATEKTER_H
