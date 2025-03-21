#include <stdio.h>
#include "./TAD_LISTAHET/TAD_LISTAHET.h"

int main() {
    printf("Criando um lista Heterogênea de Retângulos, Círculos e Triânguloes!\n");
    Listahet* minha_lista = lsthet_cria();

    minha_lista = lsthet_insere(minha_lista, 1, RET, lsthet_cria_elemento(RET));
    minha_lista = lsthet_insere(minha_lista, 2, CIR, lsthet_cria_elemento(CIR));
    minha_lista = lsthet_insere(minha_lista, 3, TRI, lsthet_cria_elemento(TRI));
    
    if(lsthet_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    else{
        printf("Lista de Tipos Heterogênesos:\n");
        lsthet_imprime(minha_lista);   
    }

    return 0;
}
