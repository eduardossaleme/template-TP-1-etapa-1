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

tJogo* realizaJogo(tJogo* jogo){
    scanf("%c%*c", &jogo->entrada);
    jogo->comando=obtemComandoEntrada(jogo->entrada);
    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), ' ');
    MovePacman(jogo->pacman, jogo->mapa, jogo->comando);
    imprimeMapa(jogo);
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

 void imprimeMapa(tJogo* jogo){
    int i=0, j=0;
    tPosicao* posi;
    printf("Estado do jogo apos o movimento '%c'\n", jogo->entrada);
    for(i=0;i<ObtemNumeroLinhasMapa(jogo->mapa);i++){
        for(j=0;j<ObtemNumeroColunasMapa(jogo->mapa);j++){
            posi=CriaPosicao(i,j);
            printf("%c", ObtemItemMapa(jogo->mapa, posi));
            DesalocaPosicao(posi);
        }
        printf("\n");
    }
    printf("Pontuação: %d\n", ObtemPontuacaoAtualPacman(jogo->pacman));
 }

COMANDO obtemComandoEntrada(char entrada){
    if(entrada =='w') return MOV_CIMA;
    else if(entrada =='s') return MOV_BAIXO;
    else if(entrada =='d') return MOV_DIREITA;
    else if(entrada =='a') return MOV_ESQUERDA;
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