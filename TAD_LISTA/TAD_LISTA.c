#include "TAD_LISTA.h"

/*
Cria uma lista genérica.
Retorno: Ponteiro para a cabeça da lista vazia.
*/
Lista* lst_cria(void){
    return NULL;
}

/*
Verifica se uma lista está vazia.
Retorno: resultado lógico para a pegunta: lista está vazia? 1 para sim e 0 para não.
*/
int lst_vazia(Lista* l){
    return l == NULL;
}

/*
Libera uma lista genérica.
Retorno: NULL.
*/
Lista* lst_libera(Lista* l){
    Lista* p = l;

    while( p != NULL){
        l = l->prox;
        free(p);
        p = l;
    }

    return p;
}

/*
 */
Lista *lst_insere(Lista *l, void *info, int (*verifica)(void *, void *));

/*

LST RETIRA:
parametros: l (cabeca da lista).
info: informação passada, sendo void pois não tem um tipo definido.
callback que retorna uma boleana, retornando 1 se for pra excluir, e 0 para não excluir.
while: percorre a lista enquanto não for NULL, comparando usando a função que verifica se o elemento que estou procurando é o mesmo que está na lista, se for, para a verificação com um break.
depois o if: verifica se o anterior é igual a NULL, se for, é pq o elemento que estou procurando está na cabeça da lista. Se não estiver na cabeça, ele está no meio ou fim da fila. 
p = p->prox: guarda a referencia de p no prox elemento antes de ser excluido.
anterior->prox = p->prox: guarda a referencia do anterior->prox no proximo elemento que p aponta.
free(p->info): libera a informação do p.
free(p): libera o elemento escolhido da lista.
No fim, retorna a lista sem o elemento que foi excluido.
*/
Lista* lst_retira(Lista* l, void* info, int (*verifica)(void*, void*))
{
    Lista * p = l;
    Lista * anterior = NULL;
    while (p != NULL)
    {
        if(verifica(p->info,info))
        {
            break;
        }
        else
        anterior = p; 
        p = p->prox;
    }

    if(anterior == NULL)
    {
        p = p->prox; 
    }
    else
    {
        anterior->prox = p->prox;
    }
    free(p->info);
    free(p);
    return l;
    
}

/*
Parâmetros: 
l= cabeça da lista,
info= elemento que vai ser buscado,
verifica = ponteiro para a função que vau fazer a comparação se são iguais ou não;
*/
Lista* lst_busca(Lista *l, void* info, int (*verifica)(void*, void*)){
    Lista* p = l;
    while (p != NULL)
    {
        if (verifica(p->info,info))// Vai comparar a informação inserida com as informações que existem na lista.
        {
            return p;// Retorna o elemento encontrado.
        }
        p = p->prox;
    } 
    return NULL;// Não encontrou o elemento.
}

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

void lst_imprime(Lista *l, void (*imprime)(void*)){
    Lista* aux;
    for(aux=l; aux!=NULL; aux=aux->prox){
        imprime(aux->info);
    }
}
