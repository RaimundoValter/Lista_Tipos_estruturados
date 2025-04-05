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
LST_INSERE
    PARAMETROS: l(cabeça da lista)
    info: informação passada pelo usuario
    criei uma variavel "NOVO" para definir o campo info com o dado passado pelo usuario
    No IF ele percorre a cabeça da lista e faz a verificação pelo dado passado, tudo isso para começar a 
    apontar para o novo valor de novo.
    Após isso, criei duas variáveis que serão utilizadas para direcionar o valor da lista e 
    deixar na posição correta
    Ao final de tudo, assim como em uma Lista normal, ele aponta para o proximo e retorna a cabeça da lista.

*/
Lista* lst_insere(Lista *l, void *info, int (*verifica)(void*, void*)) {
    
    Lista *novo = (Lista*)malloc(sizeof(Lista));
   
    novo->info = info;
    
    if (l == NULL || verifica(info, l->info) < 0) {
        novo->prox = l;  
        return novo;     
    }

    Lista *antigo = l;
    Lista *atual = l->prox;
   
    while (atual != NULL && verifica(info, atual->info) >= 0) {
        antigo = atual;
        atual = atual->prox;
    }

    
    novo->prox = atual; 
    antigo->prox = novo;

    return l; 
}

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