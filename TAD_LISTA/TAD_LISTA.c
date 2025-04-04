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
Lista* lst_insere(Lista *l, void* info, int (*verifica)(void*, void*));

/*
*/
Lista* lst_retira(Lista* l, void* info, int (*verifica)(void*, void*));

/*
*/
Lista* lst_busca(Lista *l, void* info, int (*verifica)(void*, void*));

/*
*/
void lst_imprime(Lista *l, void (*imprime)(void*));

/*
*/
int lst_map(Lista* l, void (*operacao)(void*), int (*filtro)(void*));