#include "tMapa.h"

#define TUNEL '@'
#define COMIDA '*'
#define PAREDE '#'

tMapa* CriaMapa(const char* caminhoConfig){
    char arquivo[1000];
    sprintf(arquivo, "%s/mapa.txt", caminhoConfig);

    FILE* pFile = fopen(arquivo, "r");

    if (!pFile){
        printf("Arquivo %s nao foi encontrado!\n", arquivo);
        exit(1);   
    }

    tMapa* mapa = (tMapa*)malloc(sizeof(tMapa));
    
    mapa->nFrutasAtual=0;

    int i=0, j=0;
    char c;
    fscanf(pFile, "%d\n", &(mapa->nMaximoMovimentos));
    mapa->grid = (char**) malloc(1 * sizeof(char*));

    while(1)
    {
        if(fscanf(pFile, "%c", &c)== EOF){
            break;
        }
        j=0;
        mapa->grid = (char**) realloc(mapa->grid, (i+1) * sizeof (char*));
        mapa->grid[i] = (char*) malloc(1 * sizeof (char));
        while(1){
            if(c =='\n'){
                i++;
                break;
            }
            else{
                if(c=='*'){
                    mapa->nFrutasAtual++;
                }
                mapa->grid[i] = (char*) realloc(mapa->grid[i], (j+1)*sizeof (char));
                mapa->grid[i][j] = c;
                fscanf(pFile, "%c", &c);
                j++;
            }

        }
    }
    
    mapa->nColunas=j;
    mapa->nLinhas=i;

    int i1=0, j1=0, i2=0, j2=0;
    for(i=0;i<mapa->nLinhas;i++){
        for(j=0;j<mapa->nColunas;j++){
            if(mapa->grid[i][j]== TUNEL){
                if(i1==0){
                    i1=i;
                    j1=j;
                }
                else{
                    i2=i;
                    j2=j;
                }
            }
        }
    }
    
    mapa->tunel = CriaTunel(i1, j1, i2, j2);


    fclose(pFile);
    return mapa;
    
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    int i=0, j=0;
    tPosicao* posi;
    posi=NULL;
    for(i=0;i<mapa->nLinhas;i++){
        for(j=0;j<mapa->nColunas;j++){
            if(mapa->grid[i][j]== item){
                posi=CriaPosicao(i,j);
            }
        }
    }
    return posi;
}

tTunel* ObtemTunelMapa(tMapa* mapa){
    return mapa->tunel;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao){
    return mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)];
}

int ObtemNumeroLinhasMapa(tMapa* mapa){
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa){
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa){
    return mapa->nFrutasAtual;
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa){
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao){
    if(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == COMIDA){
        return true;
    }
    else return false;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao){
    if(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)] == PAREDE){
        return true;
    }
    else return false;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item){
    if(!(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)])){
        return false;
    }
    else{
        mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)]=item;
        return true;
    }
    
}

bool PossuiTunelMapa(tMapa* mapa){
    if(mapa->tunel==NULL){
        return false;
    }
    else return true;
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao){
    if(EntrouTunel(mapa->tunel, posicao)){
        return true;
    }
    else return false;
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao){
    LevaFinalTunel(mapa->tunel, posicao);
}

void DesalocaMapa(tMapa* mapa){
    DesalocaTunel(mapa->tunel);
    int i;
    for(i=0;i<mapa->nLinhas;i++){
        free(mapa->grid[i]);
    }
    free(mapa->grid);
    free(mapa);
}