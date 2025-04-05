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
*/
Lista* lst_retira(Lista* l, void* info, int (*verifica)(void*, void*));

/*
*/
Lista* lst_busca(Lista *l, void* info, int (*verifica)(void*, void*));

/*
*/
void lst_imprime(Lista *l, void (*imprime)(void*)){
    Lista* aux;
    for(aux=l; aux!=NULL; aux=aux->prox){
        imprime(aux->info);
    }
}

int lst_map(Lista* l, void (*operacao)(void*), int (*filtro)(void*));