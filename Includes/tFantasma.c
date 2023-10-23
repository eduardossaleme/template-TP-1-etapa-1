#include "tFantasma.h"

tFantasma* CriaFantasma(tPosicao* posicao, char simbolo){
    tFantasma fantasma;
    fantasma.posicao=posicao;
    fantasma.simbolo=simbolo;
    if(fantasma.simbolo=='B') fantasma.comando= MOV_ESQUERDA;
    else if (fantasma.simbolo=='P') fantasma.comando= MOV_CIMA;
    else if (fantasma.simbolo=='I') fantasma.comando= MOV_BAIXO;
    else if (fantasma.simbolo=='C') fantasma.comando= MOV_DIREITA;

    return &fantasma;
}