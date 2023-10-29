#include "tTunel.h"

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2){
    tTunel* tunel = NULL;
   
    if(linhaAcesso1 != 0 && colunaAcesso1 !=0){
        tunel = (tTunel*)malloc(sizeof(tTunel));
        tunel->acesso1=CriaPosicao(linhaAcesso1, colunaAcesso1);
        tunel->acesso2=CriaPosicao(linhaAcesso2, colunaAcesso2);
    }
    

    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao){
    if(SaoIguaisPosicao(posicao, tunel->acesso1) || SaoIguaisPosicao(posicao, tunel->acesso2)){
        return true;
    }
    else return false;
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao){
    if(SaoIguaisPosicao(posicao, tunel->acesso1)){
        AtualizaPosicao(posicao, tunel->acesso2);
    }
    else{
        AtualizaPosicao(posicao, tunel->acesso1);
    }
}

void DesalocaTunel(tTunel* tunel){
    if(tunel != NULL){
        DesalocaPosicao(tunel->acesso1);
        DesalocaPosicao(tunel->acesso2);
        free(tunel);
    }
}