#include "tJogo.h"

int main(int argc, char *argv[]){
    
    if (argc <= 1){//caso nao tenha sido informado o diretorio dos arquivos
    printf("ERRO:  O  diretorio  de  arquivos  de configuracao nao foi informado\n");
    return 1;
    }
    
    tJogo* jogo = inicializaJogo(argv[1]);

    int i=0;
    for(i=0;i<10;i++){
        jogo=realizaJogo(jogo);
    }
    
    encerraJogo(jogo);
    
    return 0;
}