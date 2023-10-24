#include "tJogo.h"

int main(int argc, char *argv[]){
    
    if (argc <= 1){//caso nao tenha sido informado o diretorio dos arquivos
    printf("ERRO:  O  diretorio  de  arquivos  de configuracao nao foi informado\n");
    return 1;
    }
    
    tJogo jogo= inicializaJogo(argv[1]);
    
    return 0;
}