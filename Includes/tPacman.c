#include "tPacman.h"

tPacman* CriaPacman(tPosicao* posicao){
    tPacman* pacman = (tPacman*)calloc(1, sizeof(tPacman));
    pacman->estaVivo=1;
    pacman->posicaoAtual=posicao;
    pacman->historicoDeMovimentosSignificativos = (tMovimento**)malloc(1 * sizeof(tMovimento*));
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
    
    tMovimento** clone= (tMovimento**)malloc((pacman->nMovimentosSignificativos) * sizeof(tMovimento*));
    for(i=0;i<pacman->nMovimentosSignificativos;i++){
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
    int i, j;
    if(PossuiTunelMapa(mapa)){
        if(AcessouTunelMapa(mapa, pacman->posicaoAtual)){
            AtualizaItemMapa(mapa, pacman->posicaoAtual, '@');
        }
    }
    i=ObtemLinhaPosicao(pacman->posicaoAtual);
    j=ObtemColunaPosicao(pacman->posicaoAtual);
    DesalocaPosicao(pacman->posicaoAtual);
    if(comando==MOV_BAIXO){
        pacman->posicaoAtual=CriaPosicao(i+1, j);
        pacman->nMovimentosBaixo++;
        if(EncontrouParedeMapa(mapa, pacman->posicaoAtual)){
            DesalocaPosicao(pacman->posicaoAtual);
            pacman->posicaoAtual=CriaPosicao(i, j);
            pacman->nColisoesParedeBaixo++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman->posicaoAtual)){
            pacman->nFrutasComidasBaixo++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else if(PossuiTunelMapa(mapa)){
            if(AcessouTunelMapa(mapa, pacman->posicaoAtual)){
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
    }
    else if(comando==MOV_CIMA){
        pacman->posicaoAtual=CriaPosicao(i-1, j);
        pacman->nMovimentosCima++;
        if(EncontrouParedeMapa(mapa, pacman->posicaoAtual)){
            DesalocaPosicao(pacman->posicaoAtual);
            pacman->posicaoAtual=CriaPosicao(i, j);
            pacman->nColisoesParedeCima++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman->posicaoAtual)){
            pacman->nFrutasComidasCima++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else if(PossuiTunelMapa(mapa)){
            if(AcessouTunelMapa(mapa, pacman->posicaoAtual)){
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
    }
    else if(comando==MOV_DIREITA){
        pacman->posicaoAtual=CriaPosicao(i, j+1);
        pacman->nMovimentosDireita++;
        if(EncontrouParedeMapa(mapa, pacman->posicaoAtual)){
            DesalocaPosicao(pacman->posicaoAtual);
            pacman->posicaoAtual=CriaPosicao(i, j);
            pacman->nColisoesParedeDireita++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman->posicaoAtual)){
            pacman->nFrutasComidasDireita++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else if(PossuiTunelMapa(mapa)){
            if(AcessouTunelMapa(mapa, pacman->posicaoAtual)){
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
    }
    else if(comando==MOV_ESQUERDA){
        pacman->posicaoAtual=CriaPosicao(i, j-1);
        pacman->nMovimentosEsquerda++;
        if(EncontrouParedeMapa(mapa, pacman->posicaoAtual)){
            DesalocaPosicao(pacman->posicaoAtual);
            pacman->posicaoAtual=CriaPosicao(i, j);
            pacman->nColisoesParedeEsquerda++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "colidiu com a parede");
        }
        else if(EncontrouComidaMapa(mapa, pacman->posicaoAtual)){
            pacman->nFrutasComidasEsquerda++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "pegou comida");
        }
        else if(PossuiTunelMapa(mapa)){
            if(AcessouTunelMapa(mapa, pacman->posicaoAtual)){
                AtualizaTrilhaPacman(pacman);
                EntraTunelMapa(mapa, pacman->posicaoAtual);
            }
        }
    }
    AtualizaItemMapa(mapa, pacman->posicaoAtual, '>');
    AtualizaTrilhaPacman(pacman);
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas){
    pacman->nLinhasTrilha=nLinhas;
    pacman->nColunasTrilha=nColunas;
    pacman->trilha=(int**)malloc(nLinhas * sizeof(int*));
    
    int i, j;
    for(i=0;i<nLinhas;i++){
        pacman->trilha[i]=(int*)malloc(nColunas*sizeof(int));
        for(j=0;j<nColunas;j++){
            pacman->trilha[i][j]=-1;
        }
    }
}

void AtualizaTrilhaPacman(tPacman* pacman){
    pacman->trilha[ObtemLinhaPosicao(pacman->posicaoAtual)][ObtemColunaPosicao(pacman->posicaoAtual)]=ObtemNumeroAtualMovimentosPacman(pacman);
}

void SalvaTrilhaPacman(tPacman* pacman){
    FILE* pFile = fopen("trilha.txt", "w");
    int i, j;
    for(i=0;i<pacman->nLinhasTrilha;i++){
        for(j=0;j<pacman->nColunasTrilha;j++){
            if(pacman->trilha[i][j]!=-1){
                fprintf(pFile, "%d ", pacman->trilha[i][j]);
            }
            else{
                fprintf(pFile, "# ");
            }
        }
        fprintf(pFile,"\n");
    }
    fclose(pFile);                        
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao){
    pacman->nMovimentosSignificativos++;
    pacman->historicoDeMovimentosSignificativos=(tMovimento**)realloc(pacman->historicoDeMovimentosSignificativos, (pacman->nMovimentosSignificativos) * sizeof(tMovimento*));
    pacman->historicoDeMovimentosSignificativos[pacman->nMovimentosSignificativos-1]=CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando, acao);
}

void MataPacman(tPacman* pacman){
    pacman->estaVivo=0;
}

void DesalocaPacman(tPacman* pacman){
    int i;
    DesalocaPosicao(pacman->posicaoAtual);
    for(i=0;i<pacman->nMovimentosSignificativos;i++){
        DesalocaMovimento(pacman->historicoDeMovimentosSignificativos[i]);
    }
    for(i=0;i<pacman->nLinhasTrilha;i++){
        free(pacman->trilha[i]);
    }
    free(pacman->trilha);
    free(pacman->historicoDeMovimentosSignificativos);
    free(pacman);
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman){
    return (pacman->nMovimentosBaixo+pacman->nMovimentosCima+pacman->nMovimentosDireita+pacman->nMovimentosEsquerda);
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman){
    return (ObtemNumeroAtualMovimentosPacman(pacman)-ObtemPontuacaoAtualPacman(pacman));
}

int ObtemNumeroColisoesParedePacman(tPacman* pacman){
    return (pacman->nColisoesParedeBaixo+pacman->nColisoesParedeCima+pacman->nColisoesParedeDireita+pacman->nColisoesParedeEsquerda);
}

int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman){
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman){
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman){
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman* pacman){
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman){
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman){
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman){
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman){
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman){
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman){
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman){
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman){
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman){
    return pacman->nMovimentosSignificativos;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman){
    return (pacman->nFrutasComidasBaixo + pacman->nFrutasComidasCima + pacman->nFrutasComidasDireita + pacman->nFrutasComidasEsquerda);
}