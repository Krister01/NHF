#ifndef MENU_H
#define MENU_H
#include "palyakeszit.h"

enum Menu {FOMENU, NEHEZSEGM, SZABALYOK, JATEK, BJATEK, KILEPES};

void fomenukiir(void);

enum Menu fomenutovabb(void);

void nehezsegmkiir(void);

enum Menu nehezsegmtovabb(Palya *p);

void jatekmkiir(void);

void szabalykiir(void);

enum Menu szabaly_jatekmtovabb(void);
#endif //MENU_H
