#include "TAD_LISTA.h"


/*
*/
Lista* lst_cria(void);

/*
*/
int lst_vazia(Lista* l);

/*
*/
Lista* lst_libera(Lista* l);

/*
*/
Lista* lst_insere(Lista *l, void* info, int (*verifica)(void*, void*));

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
*/
void lst_imprime(Lista *l, void (*imprime)(void*));

/*
*/
int lst_map(Lista* l, void (*operacao)(void*), int (*filtro)(void*));
