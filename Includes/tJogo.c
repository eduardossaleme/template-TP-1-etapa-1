#include "tJogo.h"

tJogo* InicializaJogo(const char* caminhoConfig){
    tJogo* jogo = (tJogo*)malloc(sizeof(tJogo));
    jogo->mapa=CriaMapa(caminhoConfig);
    jogo->pacman=CriaPacman(ObtemPosicaoItemMapa(jogo->mapa, PACMAN));
    jogo->fantasmaB=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'B'), 'B');
    jogo->fantasmaP=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'P'), 'P');
    jogo->fantasmaI=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'I'), 'I');
    jogo->fantasmaC=CriaFantasma(ObtemPosicaoItemMapa(jogo->mapa, 'C'), 'C');
    CriaTrilhaPacman(jogo->pacman, ObtemNumeroLinhasMapa(jogo->mapa), ObtemNumeroColunasMapa(jogo->mapa));
    ArquivoInicializacao(jogo);
    AtualizaTrilhaPacman(jogo->pacman);
    return jogo;
}

void RealizaJogo(tJogo* jogo){
    scanf("%c%*c", &jogo->entrada);
    jogo->comando=ObtemComandoEntrada(jogo->entrada);
    jogo->pacmanAnterior=ClonaPacman(jogo->pacman);

    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), ' ');

    MoveFantasma(jogo->fantasmaB, jogo->mapa);
    MoveFantasma(jogo->fantasmaP, jogo->mapa);
    MoveFantasma(jogo->fantasmaI, jogo->mapa);
    MoveFantasma(jogo->fantasmaC, jogo->mapa);

    MovePacman(jogo->pacman, jogo->mapa, jogo->comando);
    if(PossuiTunelMapa(jogo->mapa)){
        tTunel* tunel=ObtemTunelMapa(jogo->mapa);
        AtualizaItemMapa(jogo->mapa, tunel->acesso1 , '@');
        AtualizaItemMapa(jogo->mapa, tunel->acesso2 , '@');
    }
    AtualizaItemMapa(jogo->mapa, ObtemPosicaoPacman(jogo->pacman), '>');

    AtualizaFantasmaMapa(jogo->fantasmaB, jogo->mapa);
    AtualizaFantasmaMapa(jogo->fantasmaP, jogo->mapa);
    AtualizaFantasmaMapa(jogo->fantasmaI, jogo->mapa);
    AtualizaFantasmaMapa(jogo->fantasmaC, jogo->mapa);

    if(VerificaSeBateuPacmanFantasmas(jogo)){
        MataPacman(jogo->pacman);
    }
    
    LiberaPosicaoAnteriorFantasma(jogo->fantasmaB);
    LiberaPosicaoAnteriorFantasma(jogo->fantasmaP);
    LiberaPosicaoAnteriorFantasma(jogo->fantasmaI);
    LiberaPosicaoAnteriorFantasma(jogo->fantasmaC);

    DesalocaPosicao(ObtemPosicaoPacman(jogo->pacmanAnterior));
    free(jogo->pacmanAnterior);

    ImprimeMapa(jogo);
}

bool ContinuaJogo(tJogo* jogo){
    if(!(EstaVivoPacman(jogo->pacman))){
        printf("Game over!\n");
        printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(jogo->pacman));
        InsereNovoMovimentoSignificativoPacman(jogo->pacman, jogo->comando, "fim de jogo por enconstar em um fantasma");
        return false;
    }
    else if(ObtemNumeroAtualMovimentosPacman(jogo->pacman)==ObtemNumeroMaximoMovimentosMapa(jogo->mapa)){
        printf("Game over!\n");
        printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(jogo->pacman));
        return false;
    }
    else if(ObtemPontuacaoAtualPacman(jogo->pacman) == ObtemQuantidadeFrutasIniciaisMapa(jogo->mapa)){
        printf("Voce venceu!\n");
        printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(jogo->pacman));
        return false;
    }
    else return true;
}

void ArquivoInicializacao(tJogo* jogo){
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

 void ImprimeMapa(tJogo* jogo){
    int i=0, j=0;
    tPosicao* posi;
    printf("Estado do jogo apos o movimento '%c':\n", jogo->entrada);
    for(i=0;i<ObtemNumeroLinhasMapa(jogo->mapa);i++){
        for(j=0;j<ObtemNumeroColunasMapa(jogo->mapa);j++){
            posi=CriaPosicao(i,j);
            printf("%c", ObtemItemMapa(jogo->mapa, posi));
            DesalocaPosicao(posi);
        }
        printf("\n");
    }
    printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(jogo->pacman));
 }

COMANDO ObtemComandoEntrada(char entrada){
    if(entrada =='w') return MOV_CIMA;
    else if(entrada =='s') return MOV_BAIXO;
    else if(entrada =='d') return MOV_DIREITA;
    else if(entrada =='a') return MOV_ESQUERDA;
}

bool VerificaSeBateuPacmanFantasmas(tJogo* jogo){
    if(BateuFantasma(jogo->fantasmaB, ObtemPosicaoPacman(jogo->pacman)) || 
            CruzouFantasma(jogo->fantasmaB, ObtemPosicaoPacman(jogo->pacman), ObtemPosicaoPacman(jogo->pacmanAnterior), jogo->mapa)){
        return true;
    }
    else if(BateuFantasma(jogo->fantasmaP, ObtemPosicaoPacman(jogo->pacman)) || 
            CruzouFantasma(jogo->fantasmaP, ObtemPosicaoPacman(jogo->pacman), ObtemPosicaoPacman(jogo->pacmanAnterior), jogo->mapa)){
        return true;
    }
    else if(BateuFantasma(jogo->fantasmaI, ObtemPosicaoPacman(jogo->pacman)) || 
            CruzouFantasma(jogo->fantasmaI, ObtemPosicaoPacman(jogo->pacman), ObtemPosicaoPacman(jogo->pacmanAnterior), jogo->mapa)){
        return true;
    }
    else if(BateuFantasma(jogo->fantasmaC, ObtemPosicaoPacman(jogo->pacman)) || 
            CruzouFantasma(jogo->fantasmaC, ObtemPosicaoPacman(jogo->pacman), ObtemPosicaoPacman(jogo->pacmanAnterior), jogo->mapa)){
        return true;
    }
    else return false;
}

void ArquivoEstatisticas(tJogo* jogo){
     FILE* pFile = fopen("estatisticas.txt", "w");
     
     fprintf(pFile,"Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(jogo->pacman));
     fprintf(pFile,"Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(jogo->pacman));
     fprintf(pFile,"Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(jogo->pacman));
     fprintf(pFile,"Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(jogo->pacman));
     fprintf(pFile,"Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(jogo->pacman));
     fprintf(pFile,"Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(jogo->pacman));
     fprintf(pFile,"Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(jogo->pacman));

     fclose(pFile);
}

void EncerraJogo(tJogo* jogo){
    SalvaTrilhaPacman(jogo->pacman);
    ArquivoEstatisticas(jogo);
    DesalocaMapa(jogo->mapa);
    DesalocaPacman(jogo->pacman);
    DesalocaFantasma(jogo->fantasmaB);
    DesalocaFantasma(jogo->fantasmaP);
    DesalocaFantasma(jogo->fantasmaI);
    DesalocaFantasma(jogo->fantasmaC);
    free(jogo);
}