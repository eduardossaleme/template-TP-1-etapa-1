#ifndef TFANTASMA_H
#define TFANTASMA_H

#include "tPosicao.h"
#include "tMovimento.h"


typedef struct{
    tPosicao* posicao;
    COMANDO comando;
    char simbolo;
}tFantasma;

tFantasma* CriaFantasma(tPosicao* posicao, char simbolo);

#endif