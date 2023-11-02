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
        InsereNovoMovimentoSignificativoPacman(jogo->pacman, jogo->comando, "fim de jogo por encostar em um fantasma");
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

void MontaRanking(tJogo* jogo){
    int ranking[4][4]={'w', ObtemNumeroFrutasComidasCimaPacman(jogo->pacman), ObtemNumeroColisoesParedeCimaPacman(jogo->pacman), ObtemNumeroMovimentosCimaPacman(jogo->pacman),
    's', ObtemNumeroFrutasComidasBaixoPacman(jogo->pacman), ObtemNumeroColisoesParedeBaixoPacman(jogo->pacman), ObtemNumeroMovimentosBaixoPacman(jogo->pacman),
    'a', ObtemNumeroFrutasComidasEsquerdaPacman(jogo->pacman), ObtemNumeroColisoesParedeEsquerdaPacman(jogo->pacman), ObtemNumeroMovimentosEsquerdaPacman(jogo->pacman),
    'd', ObtemNumeroFrutasComidasDireitaPacman(jogo->pacman), ObtemNumeroColisoesParedeDireitaPacman(jogo->pacman), ObtemNumeroMovimentosDireitaPacman(jogo->pacman)};
    int i, j;

    for(i=0;i<=3;i++){//ordenando o ranking na ordem correta
        for(j=1;j+i<=3;j++){  
            if(ranking[i][1]<ranking[i+j][1]){
                TrocaPosicao(ranking, i, j);
            }
            else if(ranking[i][1]==ranking[i+j][1] && ranking[i][2]>ranking[i+j][2]){
                TrocaPosicao(ranking, i, j);
            }
            else if(ranking[i][1]==ranking[i+j][1]&& ranking[i][2]==ranking[i+j][2] && ranking[i][3]<ranking[i+j][3]){
                TrocaPosicao(ranking, i, j);
            }
            else if(ranking[i][1]==ranking[i+j][1] && ranking[i][2]==ranking[i+j][2] && ranking[i][3]==ranking[i+j][3]&& ranking[i][0]>ranking[i+j][0]){
                TrocaPosicao(ranking, i, j);
            }
        }
    }
    FILE* pFile = fopen("ranking.txt", "w");
    fprintf(pFile,"%c,%d,%d,%d\n", ranking[0][0], ranking[0][1], ranking[0][2], ranking[0][3]);
    fprintf(pFile,"%c,%d,%d,%d\n", ranking[1][0], ranking[1][1], ranking[1][2], ranking[1][3]);
    fprintf(pFile,"%c,%d,%d,%d\n", ranking[2][0], ranking[2][1], ranking[2][2], ranking[2][3]);
    fprintf(pFile,"%c,%d,%d,%d\n", ranking[3][0], ranking[3][1], ranking[3][2], ranking[3][3]);
    fclose(pFile);
}

void MontaResumo(tJogo* jogo){
    tMovimento** resumo = ClonaHistoricoDeMovimentosSignificativosPacman(jogo->pacman);
    FILE* pFile = fopen("resumo.txt", "w");
    int i=0;
    for(i=0;i<ObtemNumeroMovimentosSignificativosPacman(jogo->pacman);i++){
        fprintf(pFile,"Movimento %d (%c) %s\n", resumo[i]->numeroDoMovimento, ObtemLetraComando(resumo[i]->comando), resumo[i]->acao);
        DesalocaMovimento(resumo[i]);
    }
    free(resumo);
    fclose(pFile);
}

char ObtemLetraComando(COMANDO comando){
    if(comando == MOV_CIMA) return 'w';
    else if(comando == MOV_BAIXO) return 's';
    else if(comando == MOV_DIREITA) return 'd';
    else if(comando == MOV_ESQUERDA) return 'a';
}

void TrocaPosicao(int ranking[4][4], int i, int j){
    int aux0, aux1, aux2, aux3;
    aux0=ranking[i][0];
    aux1=ranking[i][1];
    aux2=ranking[i][2];
    aux3=ranking[i][3];
    ranking[i][0]=ranking[i+j][0];
    ranking[i][1]=ranking[i+j][1];
    ranking[i][2]=ranking[i+j][2];
    ranking[i][3]=ranking[i+j][3];
    ranking[i+j][0]=aux0;
    ranking[i+j][1]=aux1;
    ranking[i+j][2]=aux2;
    ranking[i+j][3]=aux3; 
}

void EncerraJogo(tJogo* jogo){
    SalvaTrilhaPacman(jogo->pacman);
    ArquivoEstatisticas(jogo);
    MontaRanking(jogo);
    MontaResumo(jogo);
    DesalocaMapa(jogo->mapa);
    DesalocaPacman(jogo->pacman);
    DesalocaFantasma(jogo->fantasmaB);
    DesalocaFantasma(jogo->fantasmaP);
    DesalocaFantasma(jogo->fantasmaI);
    DesalocaFantasma(jogo->fantasmaC);
    free(jogo);
}