#ifndef TJOGO_H
#define TJOGO_H

#include "tMapa.h"
#include "tFantasma.h"
#include "tPacman.h"

#define PACMAN '>'

typedef struct{
    tMapa* mapa;
    tPacman* pacman;
    tFantasma* fantasmaB, fantasmaP, fantasmaI, fantasmaC;
}tJogo;

tJogo* inicializaJogo(const char* caminhoConfig);

void arquivoInicializacao(tJogo* jogo);

void encerraJogo(tJogo* jogo);

#endif