#include "tPacman.h"

tPacman* CriaPacman(tPosicao* posicao){
    tPacman* pacman = (tPacman*)calloc(1, sizeof(tPacman));
    pacman->estaVivo=1;
    pacman->posicaoAtual=posicao;
    
    return pacman;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman){
    return pacman->posicaoAtual;
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