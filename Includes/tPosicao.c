#include "tPosicao.h"

tPosicao* CriaPosicao(int linha, int coluna){
    tPosicao* posi = (tPosicao*)malloc(sizeof(tPosicao));
    posi->linha=linha;
    posi->coluna=coluna;
    return posi;
}

tPosicao* ClonaPosicao(tPosicao* posicao){
    tPosicao* posi = (tPosicao*)malloc(sizeof(tPosicao));
    *posi=*posicao;
    return posi;
}

int ObtemLinhaPosicao(tPosicao* posicao){
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao){
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova){
    *posicaoAtual=*posicaoNova;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2){
    if(posicao1->coluna == posicao2->coluna && posicao1->linha == posicao2->linha){
        return true;
    }
    else return false;
}

void DesalocaPosicao(tPosicao* posicao){
    free(posicao);
}