#include <stdlib.h>
#include <stdio.h>

/*
 */
Lista *lst_cria(void);

/*
 */
int lst_vazia(Lista *l);

/*
 */
Lista *lst_libera(Lista *l);

/*
 */
Lista *lst_insere(Lista *l, void *info, int (*verifica)(void *, void *));

/*
 */
Lista *lst_retira(Lista *l, void *info, int (*verifica)(void *, void *));

/*
 */
Lista *lst_busca(Lista *l, void *info, int (*verifica)(void *, void *));

/*
 */
void lst_imprime(Lista *l, void (*imprime)(void *));

/*
Função lst_map, percorre a lista "Lista *l", verificando se o elemnto "l->info" satisfaz
a condição da função "filtro" passada por parâmetro. Se satisfeita a condição, "l-info"
é passada como parâmetro para a função "operacao" esta que é, também, passada como parâmetro na função
"lst_map. Após o "if" "l" recebe "l->prox" para que todos os elementos da lista sejam acessados.

Parâmetros:
Lista *l - recebe um ponteiro para a estrutura "Lista" que contem os
    campos: void* info e struct lista* prox;
void (*operacao)(void *) - callback para uma função que executa alguma operação em um elemento da lista.
int (*filtro)(void *) - callback para uma função que verifica se uma condição será satisfeita e retorn 1 ou 0.

*/
int lst_map(Lista *l, void (*operacao)(void *), int (*filtro)(void *))
{
    while (l != NULL)
    {
        if (filtro(l->info))
        {
            operacao(l->info);
        }
        l = l->prox;
    }
    return 1;
}

void ok()
{
    printf("\nOK!\n\n");
}