#ifndef __TAD_LISTA_H__
    #define __TAD_LISTA_H__
    

    #include <stdlib.h>

    struct lista{
        void* info;
        struct lista* prox;
    };

    typedef struct lista Lista;
    
    Lista* lst_cria(void);
    int lst_vazia(Lista* l);
    Lista* lst_libera(Lista* l);

    Lista* lst_insere(Lista *l, void* info, int (*verifica)(void*, void*));
    Lista* lst_retira(Lista* l, void* info, int (*verifica)(void*, void*));
    void* lst_busca(Lista *l, void* info, int (*verifica)(void*, void*));
    void lst_imprime(Lista *l, void (*imprime)(void*));
    int lst_map(Lista* l, void (*operacao)(void*), int (*filtro)(void*));
    int verifica(Lista *l, int n);
    

    void ok();


    #include "TAD_LISTA.c"
#endif