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

void MontaRanking(tJogo* jogo);

void TrocaPosicao(int ranking[4][4], int i, int j);

void MontaResumo(tJogo* jogo);

char ObtemLetraComando(COMANDO comando);

void EncerraJogo(tJogo* jogo);

#endif