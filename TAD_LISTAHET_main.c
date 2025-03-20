#include <stdio.h>
#include "./TAD_LISTAHET/TAD_LISTAHET.h"

int main() {
    printf("Criando um lista Heterogênea de Retângulos, Círculos e Triânguloes!\n");
    Listahet* minha_lista = lsthet_cria();

    if(lsthet_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    else{
        printf("Lista de Tipos Heterogênesos:\n");
        printf("...");   
    }

      return 0;
}
