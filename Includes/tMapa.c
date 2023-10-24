#include "tMapa.h"

tMapa* CriaMapa(const char* caminhoConfig){
    char arquivo[1000];
    sprintf(arquivo, "%s/mapa.txt", caminhoConfig);

    FILE* pFile = fopen(arquivo, "r");

    if (!pFile){
        printf("Arquivo %s nao foi encontrado!\n", arquivo);
        exit(1);   
    }

    tMapa* mapa;
    int i=0, j=0;
    char c;
    fscanf(pFile, "%d\n", &(mapa->nMaximoMovimentos));
    mapa->grid = (char**) malloc(1*(sizeof (char*)));
    printf("TESTE %d", mapa->nMaximoMovimentos);
    while (!(feof(pFile)))
    {
        mapa->grid = (char**) realloc(mapa->grid, (i+1)*(sizeof (char*)));
        mapa->grid[i] = (char*) malloc(1*(sizeof (char)));
        j=0;
        while(1){
            fscanf(pFile, "%c", &c);
            printf("\n");
            if(c=='\n'){
                i++;
                break;
            }
            else{
                mapa->grid[i] = (char*) realloc(mapa->grid[i], (j+1)*(sizeof (char)));
                mapa->grid[i][j]=c;
                j++;
                printf("%c", mapa->grid[i][j]);
            }

        }
    }
    
    mapa->nColunas=j;
    mapa->nLinhas=i;
    
    return mapa;
    
}