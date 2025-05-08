#include <stdio.h>
#include <stdlib.h>
#include "../TAD_LISTA/TAD_LISTA.h"


void formatacao(void* elemento);
void* ler_linha(char* linha_arquivo);

typedef struct contato{
    char nome[81];
    char telefone[15];
} Contato;

int main(int argc, char* argv[]){

    Lista* minha_lista = lst_cria();
    
    FILE* arquivo_entrada = fopen("arquivo_contatos.txt", "rt");

    if(!arquivo_entrada){
        printf("Erro ao carregar arquivo");
        return 1;
    }

    minha_lista = lst_carrega(minha_lista, arquivo_entrada, ler_linha);

    printf("=> Nossa lista CARREGADA DA MEMÓRIA!!!\n\
        Faremos uma lista contatos.");

    // Imprime a lista de inteiros criada.
    lst_imprime(minha_lista, formatacao);

    // Liberando a lista completa.
    printf("\n\nLiberando minha Lista de CONTATOS...\n");
    
    minha_lista = lst_libera(minha_lista);

    if(lst_vazia(minha_lista))
        printf("\nLista liberada com sucesso...\n");
    else
        printf("\nLista não liberou memória corretamente...\n");
    
    return 0;
}

// Funções ÚTEIS
// Define o formato e imprime elemento da lista genérica.
void formatacao(void* elemento){
    Contato* contato = (Contato*)elemento;
    printf("| %80s | %14s |", contato->nome, contato->telefone);
}

// Processa a linha do arquivo e
// retorna um ponteiro para a estrutura com os dados inseridos nela.
void* ler_linha(char* linha_arquivo){
    // Aloca a memória para receber os dados presentes em linha_arquivo
    Contato* novo_contato = (Contato*)malloc(sizeof(Contato));
    char c = linha_arquivo[0];

    // Copia os dados para a estrutura novo_contato.
    // Enquanto não encontramo o final da string ou da linha.
    for(int i=0; linha_arquivo[i]!= '\0' || linha_arquivo[i]!= '\n'; i++)
    {
        // FAZENDO...
    }

    // Retorna a estrutura como void* para ser guardada na lista.
    return (void*)novo_contato;
}