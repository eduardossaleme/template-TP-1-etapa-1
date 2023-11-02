#ifndef TJOGO_H
#define TJOGO_H

#include "tMapa.h"
#include "tFantasma.h"
#include "tPacman.h"

#define PACMAN '>'

typedef struct{
    tMapa* mapa;
    tPacman* pacman;
    tPacman* pacmanAnterior; 
    tFantasma* fantasmaB;
    tFantasma* fantasmaP;
    tFantasma* fantasmaI;
    tFantasma* fantasmaC;
    char entrada;
    COMANDO comando;
}tJogo;

tJogo* InicializaJogo(const char* caminhoConfig);

void RealizaJogo(tJogo* jogo);

bool ContinuaJogo(tJogo* jogo);

void ArquivoInicializacao(tJogo* jogo);

void ImprimeMapa(tJogo* jogo);

COMANDO ObtemComandoEntrada(char entrada);

bool VerificaSeBateuPacmanFantasmas(tJogo* jogo);

void ArquivoEstatisticas(tJogo* jogo);

void EncerraJogo(tJogo* jogo);

#endif