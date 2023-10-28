#include "tJogo.h"

tJogo* inicializaJogo(const char* caminhoConfig){
    tJogo* jogo = (tJogo*)malloc(sizeof(tJogo));
    jogo->mapa=CriaMapa(caminhoConfig);
    jogo->pacman=CriaPacman(ObtemPosicaoItemMapa(jogo->mapa, PACMAN));
    jogo->fantasmaB=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'B'), 'B');
    jogo->fantasmaP=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'P'), 'P');
    jogo->fantasmaI=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'I'), 'I');
    jogo->fantasmaC=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'C'), 'C');
    arquivoInicializacao(jogo);
    return jogo;
}

void arquivoInicializacao(tJogo* jogo){
    FILE* pFile = fopen("inicializacao.txt", "w");

    int i=0, j=0;
    tPosicao* posi;
    for(i=0;i<ObtemNumeroLinhasMapa(jogo->mapa);i++){
        for(j=0;j<ObtemNumeroColunasMapa(jogo->mapa);j++){
            posi=CriaPosicao(i,j);
            fprintf(pFile, "%c", ObtemItemMapa(jogo->mapa, posi));
            DesalocaPosicao(posi);
        }
        fprintf(pFile,"\n");
    }
    posi=ObtemPosicaoPacman(jogo->pacman);
    fprintf(pFile, "Pac-Man comecara o jogo na linha %d e coluna %d\n", (ObtemLinhaPosicao(posi)+1), (ObtemColunaPosicao(posi)+1));
    fclose(pFile);
 }


void encerraJogo(tJogo* jogo){
    DesalocaMapa(jogo->mapa);
    DesalocaPacman(jogo->pacman);
    DesalocaFantasma(jogo->fantasmaB);
    DesalocaFantasma(jogo->fantasmaP);
    DesalocaFantasma(jogo->fantasmaI);
    DesalocaFantasma(jogo->fantasmaC);
    free(jogo);
}