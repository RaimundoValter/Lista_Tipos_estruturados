#include <stdio.h>

int main(int qtd_param, char* param[]){

    if (qtd_param == 2){
        char* nome_arquivo = param[1];

        FILE* fp = fopen(nome_arquivo, "rt");
        
        if(!fp){
            printf("Erro ao abrir o arquivo: %s", nome_arquivo);
            exit(1);
        }
        
        printf("\nArquivo abriu com sucesso!\n");

        fclose(fp);
    }
    return 0;
}