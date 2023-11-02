#include "tFantasma.h"

tFantasma* CriaFantasma(tPosicao* posicao, char simbolo){
    tFantasma* fantasma = NULL;
    if(posicao!=NULL){
        fantasma = (tFantasma*)malloc(sizeof (tFantasma));
        fantasma->posicao=posicao;
        fantasma->simbolo=simbolo;
        fantasma->casaAnterior=' ';
        if(fantasma->simbolo=='B') fantasma->comando= MOV_ESQUERDA;
        else if (fantasma->simbolo=='P') fantasma->comando= MOV_CIMA;
        else if (fantasma->simbolo=='I') fantasma->comando= MOV_BAIXO;
        else if (fantasma->simbolo=='C') fantasma->comando= MOV_DIREITA;
    }
    return fantasma;
}

void MoveFantasma(tFantasma* fantasma, tMapa* mapa){
    if(fantasma==NULL) return;
    int i, j;
    AtualizaItemMapa(mapa, fantasma->posicao, fantasma->casaAnterior);
    i=ObtemLinhaPosicao(fantasma->posicao);
    j=ObtemColunaPosicao(fantasma->posicao);
    fantasma->posicaoAnterior=CriaPosicao(i, j);
    DesalocaPosicao(fantasma->posicao);
    if(fantasma->comando==MOV_BAIXO){
        fantasma->posicao=CriaPosicao(i+1, j);
        if(EncontrouParedeMapa(mapa, fantasma->posicao)){
            DesalocaPosicao(fantasma->posicao);
            fantasma->posicao=CriaPosicao(i-1, j);
            fantasma->comando=MOV_CIMA;
        }
    }
    else if(fantasma->comando==MOV_CIMA){
        fantasma->posicao=CriaPosicao(i-1, j);
        if(EncontrouParedeMapa(mapa, fantasma->posicao)){
            DesalocaPosicao(fantasma->posicao);
            fantasma->posicao=CriaPosicao(i+1, j);
            fantasma->comando=MOV_BAIXO;
        }
    }
    else if(fantasma->comando==MOV_DIREITA){
        fantasma->posicao=CriaPosicao(i, j+1);
        if(EncontrouParedeMapa(mapa, fantasma->posicao)){
            DesalocaPosicao(fantasma->posicao);
            fantasma->posicao=CriaPosicao(i, j-1);
            fantasma->comando=MOV_ESQUERDA;
        }
    }
    else if(fantasma->comando==MOV_ESQUERDA){
        fantasma->posicao=CriaPosicao(i, j-1);
        if(EncontrouParedeMapa(mapa, fantasma->posicao)){
            DesalocaPosicao(fantasma->posicao);
            fantasma->posicao=CriaPosicao(i, j+1);
            fantasma->comando=MOV_DIREITA;
        }
    }
    fantasma->casaAnterior=ObtemItemMapa(mapa, fantasma->posicao);
}

void AtualizaFantasmaMapa(tFantasma* fantasma, tMapa* mapa){
    if (fantasma==NULL) return;
    AtualizaItemMapa(mapa, fantasma->posicao, fantasma->simbolo);
}

bool BateuFantasma(tFantasma* fantasma, tPosicao* posi){
    if(fantasma==NULL) return false;

    if(SaoIguaisPosicao(fantasma->posicao, posi)){
        return true;
    }
    else return false;
}

bool CruzouFantasma(tFantasma* fantasma, tPosicao* posiPac, tPosicao* pacAnt, tMapa* mapa){
    if(fantasma==NULL) return false;
    
    if(SaoIguaisPosicao(fantasma->posicaoAnterior, posiPac) && SaoIguaisPosicao(fantasma->posicao, pacAnt)){
        AtualizaItemMapa(mapa, posiPac, ' ');
        return true;
    }
    else{
        return false;
    }
}

void LiberaPosicaoAnteriorFantasma(tFantasma* fantasma){
    if(fantasma==NULL) return;
    DesalocaPosicao(fantasma->posicaoAnterior);
}

void DesalocaFantasma(tFantasma* fantasma){
    if(fantasma!=NULL){
        DesalocaPosicao(fantasma->posicao);
        free(fantasma);
    }
}