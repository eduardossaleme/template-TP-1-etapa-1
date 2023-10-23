#include "tJogo.h"

tJogo inicializaJogo(char *argv[ ]){
    tJogo jogo;
    jogo.mapa=CriaMapa(argv);
    jogo.pacman=CriaPacman(ObtemPosicaoItemMapa(jogo.mapa, PACMAN));
    jogo.fantasmaB=CriaFantasma(ObtemPosicaoItemMapa(jogo.mapa, B), B);
    jogo.fantasmaP=CriaFantasma(ObtemPosicaoItemMapa(jogo.mapa, P), P);
    jogo.fantasmaI=CriaFantasma(ObtemPosicaoItemMapa(jogo.mapa, I), I);
    jogo.fantasmaC=CriaFantasma(ObtemPosicaoItemMapa(jogo.mapa, C), C);
}