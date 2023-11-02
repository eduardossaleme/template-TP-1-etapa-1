#include "tJogo.h"

int main(int argc, char *argv[]){
    
    if (argc <= 1){//caso nao tenha sido informado o diretorio dos arquivos
    printf("ERRO:  O  diretorio  de  arquivos  de configuracao nao foi informado\n");
    return 1;
    }
    
    tJogo* jogo = InicializaJogo(argv[1]);

    while(ContinuaJogo(jogo)){
        RealizaJogo(jogo);
    }
    
    EncerraJogo(jogo);
    
    return 0;
}