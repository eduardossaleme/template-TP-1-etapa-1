#ifndef TJOGO_H_
#define TJOGO_H_

#include "tMapa.h"
#include "tFantasma.h"
#include "tPacman.h"

typedef struct{
    tMapa* mapa;
    tPacman* pacman;
    tFantasma* fantasmaB, fantasmaP, fantasmaI, fantasmaC;
}tJogo;

tJogo inicializaJogo(char *argv[ ]);
#endif