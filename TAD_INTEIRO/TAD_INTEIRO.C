

Lista* lst_cria(void){
    return NULL;
}

void lst_libera(Lista* l);

Lista* lst_insere(Lista *l, int i){
    Lista* novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;

    return novo;
}

Lista* lst_retira(Lista* l, int v);

int lst_vazia(Lista* l){
    return l == NULL;
}

Lista* lst_busca(Lista *l, int v);
void lst_imprime(Lista *l);