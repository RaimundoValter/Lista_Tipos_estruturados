#include <stdio.h>
#include <stdlib.h>
#include "./TAD_lISTA/TAD_LISTA.h"

int verifica_posicao(void* elemento_posicao, void* elemento_inserir);
int todos_elementos(void* elemento_posicao);
int elementos_impares(void* elemento_posicao);
int se_igual(void* elemento1, void* elemento2);
void duplica(void* elemento);

int main(int argc, char* argv[]){
    
    int qtd_elementos=0, elemento_exclusao = 0;
    int* elemento_busca = NULL;
    int* elemento_encontrado = NULL;

    Lista* minha_lista = lst_cria();

    printf("Nossa lista genérica!!!\nFaremos uma lista de números interios.");

    printf("Digite a quantidade de elementos que quer inserir: ");
    scanf("%d%*c", &qtd_elementos);
    
    int* novo_elemento;

    for(int i = 0; i < qtd_elementos; i++){
        novo_elemento = (int*)malloc(sizeof(int));
        *novo_elemento = rand()%100;
        lst_insere(minha_lista, (void*)novo_elemento, verifica_posicao);
    }

    lst_imprime(minha_lista, todos_elementos);

    printf("\nDigite um número para excluir: ");
    scanf("%d%*c", &elemento_exclusao);

    minha_lista = lst_retira(minha_lista, (void*)elemento_exclusao, se_igual);
    
    lst_imprime(minha_lista, todos_elementos);

    printf("\nDigite um número para buscar: ");
    scanf("%d%*c", &elemento_busca);

    elemento_encontrado = lst_busca(minha_lista, (void*)elemento_busca, se_igual);

    if (elemento_encontrado)
        printf("\nElemento %d encontrado!\n", *((int*)elemento_encontrado));
    else
        printf("\nElemento não encontrado!\n");
    
    printf("\nUtilizando a função MAP para duplicar a lista de inteiros...\n");

    if(map(minha_lista, duplica, todos_elementos))
        lst_imprime(minha_lista, todos_elementos);

    minha_lista = lst_libera(minha_lista);

    printf("\nLista de inteiros liberada...\n");

    if(lst_vazia(minha_lista))
        printf("\nLista liberada com sucesso...\n");
    else
        printf("\nLista não liberou memória corretamente...\n");
    
    return 0;
}

// Funções úteis
// Retorna a verificação lógica para saber se a posição de inserção 
// do novo elemento na lista é aceitável. Retorna 1 para aceitável ou
// 0 para não.
int verifica_posicao(void* elemento_posicao, void* elemento_inserir){
    return (int)elemento_posicao > (int)elemento_inserir;
}

// Retorna a verificação lógica para identificar que
// todos os valores são para impressão.
int todos_elementos(void* elemento){
    prinf("| %d |", *((int*)elemento));
}

// Retorna a verificação lógica para identificar
// os elementos ímpares para impressão.
int elementos_impares(void* elemento){
    if (*((int*)elemento) % 2 != 0)
        prinf("| %d |", *((int*)elemento));
}

// Retorna a verificação lógica para identificar
// se os elementos 1 e 2 são iguais.
int se_igual(void* elemento1, void* elemento2){
    return *(int*)elemento1 == *((int*)elemento2);
}

// Duplica um elemento inteiro repassado como
// ponteior para void.
void duplica(void* elemento){
    *(int*)elemento = 2 * (*(int*)elemento);
}