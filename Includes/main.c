#include <stdio.h>
#include "tMapa.h"

int main(int argc, char *argv[]){
    
    if (argc <= 1){//caso nao tenha sido informado o diretorio dos arquivos
    printf("ERRO:  O  diretorio  de  arquivos  de configuracao nao foi informado\n");
    return 1;
    }
    
    printf("ere");

    tMapa* mapa = CriaMapa(argv[1]);

    printf("erere");
    
    return 0;
}