#ifndef TJOGO_H
#define TJOGO_H

#include "tMapa.h"
#include "tFantasma.h"
#include "tPacman.h"

#define PACMAN '>'

typedef struct{
    tMapa* mapa;
    tPacman* pacman;
    tFantasma* fantasmaB;
    tFantasma* fantasmaP;
    tFantasma* fantasmaI;
    tFantasma* fantasmaC;
    char entrada;
    COMANDO comando;
}tJogo;

tJogo* inicializaJogo(const char* caminhoConfig);

tJogo* realizaJogo(tJogo* jogo);

void arquivoInicializacao(tJogo* jogo);

void imprimeMapa(tJogo* jogo);

COMANDO obtemComandoEntrada(char entrada);

void encerraJogo(tJogo* jogo);

#endif