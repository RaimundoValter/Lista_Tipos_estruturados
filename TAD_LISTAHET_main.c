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
    
    int id_busca = -1;
    printf("\n## Buscando um elemento pelo ID ##\n");
    printf("Digite um id: ");
    scanf("%d", &id_busca);

    Listahet* elemento_busca = lsthet_busca(minha_lista, id_busca);
    if( elemento_busca )
        printf("Elemento com id %d encontrado!\n", id_busca);
    else
        printf("Elemento com id %d inexistente...\n", id_busca);

    printf("Liberando minha lista...\n");
    minha_lista = lsthet_libera(minha_lista);

    if(lsthet_vazia(minha_lista))
        printf("Minha lista está vazia!\n");
    else{
        printf("Lista de Tipos Heterogênesos:\n");
        lsthet_imprime(minha_lista);   
    }
    return 0;
}
