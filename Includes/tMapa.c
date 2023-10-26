#include "tMapa.h"

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
        printf("\n");
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
                // printf("%c", c);
                mapa->grid[i] = (char*) realloc(mapa->grid[i], (j+1)*sizeof (char));
                mapa->grid[i][j] = c;
                fscanf(pFile, "%c", &c);
                j++;
            }

        }
    }
    
    mapa->nColunas=j;
    mapa->nLinhas=i;
    fclose(pFile);
    return mapa;
    
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item){
    int i=0, j=0;
    tPosicao* posi = (tPosicao*)malloc(sizeof(tPosicao));
    posi=NULL;
    for(i=0;i<mapa->nLinhas;i++){
        for(j=0;j<mapa->nColunas;j++;){
            if(mapa->grid[i][j]== item){
                posi=CriaPosicao(i,j);
            }
        }
    }
    return posi;
}




void DesalocaMapa(tMapa* mapa){
    DesalocaTunel(mapa->tunel);
    int i;
    for(i=0;i<mapa->nLinhas;i++){
        free(mapa->grid[i]);
    }
    free(mapa->grid);
    // DesalocaTunel(mapa->tunel);
    free(mapa);
}