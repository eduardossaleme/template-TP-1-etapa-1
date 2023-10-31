#ifndef TFANTASMA_H
#define TFANTASMA_H

#include "tPosicao.h"
#include "tMovimento.h"
#include "tMapa.h"


typedef struct{
    tPosicao* posicao;
    tPosicao* posicaoAnterior;
    COMANDO comando;
    char simbolo, casaAnterior;
}tFantasma;

tFantasma* CriaFantasma(tPosicao* posicao, char simbolo);

void MoveFantasma(tFantasma* fantasma, tMapa* mapa);

void DesalocaFantasma(tFantasma* fantasma);

#endif