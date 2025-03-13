#include <stdio.h>
#include "./TAD_INTEIRO/TAD_INTEIRO.h"

int main() {
    printf("Criando um lista de Inteiros!\n");
    Lista* minha_lista = lst_cria();

    if(lst_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    return 0;
}
