#include "tPacman.h"

tPacman* CriaPacman(tPosicao* posicao){
    tPacman* pacman = (tPacman*)calloc(1, sizeof(tPacman));
    pacman->estaVivo=1;
    pacman->posicaoAtual=posicao;
    
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman){
    tPacman* pacmanClone = (tPacman*)calloc(1, sizeof(tPacman));
    pacmanClone->posicaoAtual=ClonaPosicao(pacman->posicaoAtual);
    return pacmanClone;
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman){
    int i;
    tMovimento* aux;
    
    tMovimento** clone= (tMovimento**)malloc(1 * sizeof(tMovimento*));
    for(i=0;i<pacman->nMovimentosSignificativos;i++){
        clone= (tMovimento**)realloc(clone, (i+1) * sizeof(tMovimento*));
        aux=pacman->historicoDeMovimentosSignificativos[i];
        clone[i]=CriaMovimento(ObtemNumeroMovimento(aux), ObtemComandoMovimento(aux), ObtemAcaoMovimento(aux));
    }

    return clone;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman){
    return pacman->estaVivo;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando){
    tPosicao* posi;
    int i, j;
    i=ObtemLinhaPosicao(pacman->posicaoAtual);
    j=ObtemColunaPosicao(pacman->posicaoAtual);
    DesalocaPosicao(pacman->posicaoAtual);
    if(comando==MOV_BAIXO){
        pacman->posicaoAtual=CriaPosicao(i+1, j);
        if(ObtemItemMapa(mapa, pacman->posicaoAtual)== '#'){
            MovePacman(pacman, mapa, MOV_CIMA);
        }
    }
    else if(comando==MOV_CIMA){
        pacman->posicaoAtual=CriaPosicao(i-1, j);
        if(ObtemItemMapa(mapa, pacman->posicaoAtual)== '#'){
            MovePacman(pacman, mapa, MOV_BAIXO);
        }
    }
    else if(comando==MOV_DIREITA){
        pacman->posicaoAtual=CriaPosicao(i, j+1);
        if(ObtemItemMapa(mapa, pacman->posicaoAtual)== '#'){
            MovePacman(pacman, mapa, MOV_ESQUERDA);
        }
    }
    else if(comando==MOV_ESQUERDA){
        pacman->posicaoAtual=CriaPosicao(i, j-1);
        if(ObtemItemMapa(mapa, pacman->posicaoAtual)== '#'){
            MovePacman(pacman, mapa, MOV_DIREITA);
        }
    }
    AtualizaItemMapa(mapa, pacman->posicaoAtual, '>');
}

void DesalocaPacman(tPacman* pacman){
    int i;
    for(i=0;i<pacman->nLinhasTrilha;i++){
        free(pacman->trilha[i]);
    }
    free(pacman->trilha);
    DesalocaPosicao(pacman->posicaoAtual);
    for(i=0;i<pacman->nMovimentosSignificativos;i++){
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
    }
    free(pacman->historicoDeMovimentosSignificativos);

    free(pacman);
}

int ObtemPontuacaoAtualPacman(tPacman* pacman){
    return (pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima + pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda);
}