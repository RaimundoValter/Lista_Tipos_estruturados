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