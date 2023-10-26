#include "tJogo.h"

tJogo* inicializaJogo(const char* caminhoConfig){
    tJogo* jogo = (tJogo*)malloc(sizeof(tJogo));
    jogo->mapa=CriaMapa(caminhoConfig);
    jogo->pacman=CriaPacman(ObtemPosicaoItemMapa(jogo->mapa, PACMAN));
    // jogo->fantasmaB=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, B), B);
    // jogo->fantasmaP=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, P), P);
    // jogo->fantasmaI=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, I), I);
    // jogo->fantasmaC=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, C), C);
    return jogo;
}

void encerraJogo(tJogo* jogo){
    DesalocaMapa(jogo->mapa);
    DesalocaPacman(jogo->pacman);
    free(jogo);
}