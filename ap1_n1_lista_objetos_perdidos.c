#include <stdio.h>
#include <stdlib.h>
#include "./TAD_LISTA/TAD_LISTA.h"

typedef struct {
    char descricao[100]; // Exemplo: “mochila preta da nike”
    char local_encontrado[50]; // Exemplo: “banheiro”
    char data[11]; // formato "DD/MM/AAAA"
    char tipo[30]; // ex: "chave", "caderno", "mochila"
    int devolvido; // 0 = ainda perdido, 1 = devolvido ao dono
    } ObjetoPerdido;

ObjetoPerdido* cria_objeto_perdido();
int verifica_posicao(void* elemento_posicao, void* elemento_inserir);
int todos_elementos(void* elemento_posicao);
int elementos_impares(void* elemento_posicao);
int se_igual(void* elemento1, void* elemento2);
void duplica(void* elemento);
void formatacao(void* elemento);

int main(int argc, char* argv[]){
    
    int qtd_elementos=3;

    Lista* minha_lista = lst_cria();

    printf("=> Nossa lista genérica!!!\n\
        Faremos uma lista de OBJETOS PERDIDOS.");

    
    // Inserindo inteiros na minha lista.
    ObjetoPerdido* novo_elemento;
    
    int i = 0;

    while(i < qtd_elementos){
        
        // Alocando a memória para acondicionar um inteiro.
        novo_elemento = cria_objeto_perdido();
        
        // Caso exista este elemento na lista, não inseri-lo.
        if(lst_busca(minha_lista, (void*)novo_elemento, se_igual)){
            printf("Você já inseriu este item...");
        }
        else{
            // Insere o elemento na lista.
            minha_lista = lst_insere(minha_lista, (void*)novo_elemento, verifica_posicao);
            i++;
        }
    }

    // Imprime a lista de inteiros criada.
    lst_imprime(minha_lista, formatacao);

    // // Excluir um número inteiro.
    // int* elemento_exclusao = (int*)malloc(sizeof(int));

    // printf("\nDigite um número INTEIRO para excluir: ");
    // scanf("%d%*c", elemento_exclusao);

    // minha_lista = lst_retira(minha_lista, (void*)elemento_exclusao, se_igual);
    
    // // Imprime minha lista após exclusão do elemento.

    // printf("\nMinha lista após exclusão: \n");
    // lst_imprime(minha_lista, formatacao);

    // //Buscar um número inteiro.
    // int* elemento_busca = (int*)malloc(sizeof(int));
    // Lista* elemento_encontrado = NULL;

    // printf("\nDigite um número para buscar: ");
    // scanf("%d%*c", elemento_busca);

    // elemento_encontrado = lst_busca(minha_lista, (void*)elemento_busca, se_igual);

    // if (elemento_encontrado)
    //     printf("\nElemento %d encontrado!\n", *((int*)(elemento_encontrado->info)));
    // else
    //     printf("\nElemento não encontrado!\n");
    
    // // Utilizando a função MAP para duplicar os elementos da minha lista
    // printf("\n\nUtilizando a função MAP para duplicar a lista de inteiros...\n");

    // if(lst_map(minha_lista, duplica, todos_elementos))
    //     lst_imprime(minha_lista, formatacao);

    
    // // Liberando a lista completa.
    // printf("\n\nLiberando minha Lista de INTEIROS...\n");
    
    // minha_lista = lst_libera(minha_lista);

    // if(lst_vazia(minha_lista))
    //     printf("\nLista liberada com sucesso...\n");
    // else
    //     printf("\nLista não liberou memória corretamente...\n");
    
    return 0;
}

// Funções ÚTEIS
// Retorna a verificação lógica para saber se a posição de inserção 
// do novo elemento na lista é aceitável. Retorna 1 para aceitável ou
// 0 para não.


int devolvido;

ObjetoPerdido* cria_objeto_perdido(){

    ObjetoPerdido* novo_elemento = (ObjetoPerdido*)malloc(sizeof(ObjetoPerdido));

    printf("\n== CRIANDO OBJETO PERDIDO ==\n");
    printf("Descrição:");
    scanf("%99[^\n]%*c", novo_elemento->descricao);
    printf("Local encontrado:");
    scanf("%49[^\n]%*c", novo_elemento->local_encontrado);
    printf("Data:");
    scanf("%10[^\n]%*c", novo_elemento->data);
    printf("Tipo:");
    scanf("%29[^\n]%*c", novo_elemento->tipo);
    
    // Isso sinaliza que o elemento que queremos inserir na lista
    // está perdido e ainda não foi devolvido.
    novo_elemento->devolvido = 0;

    return novo_elemento;
}

int verifica_posicao(void* elemento_posicao, void* elemento_inserir){
    return (int)elemento_posicao > (int)elemento_inserir;
}

// Define o formato e imprime elemento da lista genérica.
void formatacao(void* elemento){
    ObjetoPerdido* elemento_impressao = (ObjetoPerdido*)elemento;

    printf("\n== OBJETO PERDIDO ==\n");
    printf("Descrição: %s\n", elemento_impressao->descricao);
    printf("Local encontrado: %s\n", elemento_impressao->local_encontrado);
    printf("Data: %s\n", elemento_impressao->data);
    printf("Tipo: %s\n", elemento_impressao->tipo);
    printf("Devolvido: ");
    if(elemento_impressao->devolvido)
        printf("sim\n");
    else
        printf("não\n");
}

// Retorna a verificação lógica para identificar que
// todos os valores são para impressão.
int todos_elementos(void* elemento){
    return 1;
}

// Retorna a verificação lógica para identificar
// os elementos ímpares para impressão.
int elementos_impares(void* elemento){
    if (*((int*)elemento) % 2 != 0)
        return 1;
    else
        return 0;
}

// Retorna a verificação lógica para identificar
// se os elementos 1 e 2 são iguais.
int se_igual(void* elemento1, void* elemento2){
    ObjetoPerdido* objeto1 = (ObjetoPerdido*)elemento1;
    ObjetoPerdido* objeto2 = (ObjetoPerdido*)elemento2;

    if(strcmp(objeto1->descricao, objeto2->descricao) == 0 && strcmp(objeto1->data, objeto2->data) == 0)
        return 1;
    else    
        return 0;
}

// Duplica um elemento inteiro repassado como
// ponteior para void.
void duplica(void* elemento){
    *(int*)elemento = 2 * (*(int*)elemento);
}