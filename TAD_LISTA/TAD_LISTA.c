#include "TAD_LISTA.h"

/*
LST_CRIA
Cria uma lista genérica.
Retorno: Ponteiro para a cabeça da lista vazia.
*/
Lista* lst_cria(void){
    return NULL;
}

/*
LST_VAZIA
Verifica se uma lista está vazia.
Retorno: resultado lógico para a pegunta: lista está vazia? 1 para sim e 0 para não.
*/
int lst_vazia(Lista* l){
    return l == NULL;
}

/*
LST_LIBERA
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
LST_INSERE
Insere um novo elemento na lista genérica.
Retorno: Lista*, ponteiro para nova cabeça da lista.
 */
Lista *lst_insere(Lista *l, void *info, int (*verifica)(void *, void *)){
    Lista* ant = NULL;
    Lista* p = l;

    // Cria um novo elemento para a lista.
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    // Preenche o novo elemento com a informação.
    novo->info = info;

    // Encontrando a posição onde inserir o elemento.
    for(ant = NULL, p = l; p != NULL; ant = p, p = p->prox)
        if(verifica(p->info, info))
            break;

    // Nesse ponto, temos apenas 4 possibilidades para ant e p:
    // ant == NULL && p == NULL: indica que a lista está vazia e a inserção vai ocorrer na cabeça da lista.
    // ant == NULL && p != NULL: indica que a lista não está vazia e a inserção vai ocorrer na cabeça da lista.
    // ant != NULL && p != NULL: indica que a lista não está vazia e a inserção vai ocorrer no corpo da lista.
    // ant != NULL && p == NULL: indica que a lista não está vazia e que a inserção ocorrerá no fim da lista.

    // Caso a lista esteja vazia
    if (ant == NULL && p == NULL){
        // Marca o elemento como o último da lista.
        novo->prox = NULL;
        // Atualiza o ponteiro para a nova cabeça da lista.
        l=novo;
    }
    // Caso o elemento tenha que ser inserido no início da lista.
    else if (ant == NULL && p != NULL){
        // Marca o elemento como o primeiro da lista.
        novo->prox = l;
        // Atualiza o ponteiro para a nova cabeça da lista.
        l=novo;
    }
    // Caso o elemento tenha que ser inserido no corpo da lista
    else if(ant != NULL && p != NULL){
        // Marca o elemento como inserido no corpo da lista.
        novo->prox = p;
        // Atualiza o elemento anterior para apontar para o novo elemento da lista.
        ant->prox = novo;
    }
    // Caso o elemento tenha que ser inserido no final da lista que não está vazia
    else if(ant != NULL && p == NULL){
        // Marca o elemento como fim da lista.
        novo->prox = NULL;
        // Atualiza o elemento anterior para apontar para o novo elemento da lista.
        ant->prox = novo;

    }

    // Retorna a nova cabeça da lista.
    return l;
}

/*
LST RETIRA
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

    // Elemento não encontrado para exclusão
    if(p == NULL)
        return l;

    // Elemento encontrado para exclusão na cabeça da lista.
    if(anterior == NULL)
    {
        // Atualiza a nova cabeça da lista, retirando o elemento apontado por p da sequência da lista.
        l = p->prox;
    }
    // Elemento encontrado no corpo ou no fim da lista.
    else
    {
        // Atualiza retirado o elemento apontado por p da sequência da lista.
        anterior->prox = p->prox;
    }

    // Libera a informação dentro do elemento da lista para exclusão
    free(p->info);
    // Libera o elemento da lista para a exclusão.
    free(p);

    // Retorna a cabeça da lista.
    return l;
    
}

/*
LST_BUSCA
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
LST_MAP
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

/*
LST_IMPRIME
Parâmetros:
Lista *l - recebe um ponteiro para a estrutura "Lista" que contem os
    campos: void* info e struct lista* prox;
void (*imprime)(void *) - callback para uma função que manipula a informação e a imprime na tela.
*/
void lst_imprime(Lista *l, void (*imprime)(void*)){
    Lista* aux;
    for(aux=l; aux!=NULL; aux=aux->prox){
        imprime(aux->info);
    }
}
