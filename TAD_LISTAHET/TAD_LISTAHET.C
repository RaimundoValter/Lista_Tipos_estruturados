/*LSTHET_CRIA
Parêmetros: 
void
Retorna:
ponteiro para a cabeça da lista vazia criada.
*/
Listahet* lsthet_cria(void){
    return NULL;
}

/*LSTHET_LIBERA
Parêmetros: 
l    = cabeça da minha lista.
Retorna:
NULL
Libera a memória de toda a lista.
*/
Listahet* lsthet_libera(Listahet* l){
    
}

/*LSTHET_INSERE
Parêmetros: 
l    = cabeça da minha lista.
id   = chave primária que identifica unicamente um objeto da lista.
tipo = inteiro definido que identifica o tipo guardado na lista.
info = ponteiro void que guarda o endereço para a estrutura que guarda
       as informações de um tipo específico.  
Retorna:
ponteiro para a nocabeça da lista.
*/
Listahet* lsthet_insere(Listahet *l, int id, int tipo, void* info){
    Listahet* novo = (Listahet*)malloc(sizeof(Listahet));
    novo->id = id;
    novo->tipo = tipo;
    novo->info = info;
    novo->prox = l;

    return novo;
}

/*LSTHET_CRIA_ELEMENTO
Parêmetros: 
tipo = inteiro definido que identifica o tipo da estrutura a ser criada.

Retorna:
ponteiro para a estrutura do tipo específico já alocada e inidializada.
*/
void* lsthet_cria_elemento(int tipo){

    switch(tipo){
        case RET:
            Retangulo* ptr1 = (Retangulo*)malloc(sizeof(Retangulo));
            printf("Criando um RETÂNGULO:\n");
            printf("Digite a base: ");
            scanf("%f%*c", &ptr1->b);
            printf("Digite a altura: ");
            scanf("%f%*c", &ptr1->h);
            return (void*)ptr1;
        break;
        case CIR:
            Circulo* ptr2 = (Circulo*)malloc(sizeof(Circulo));
            printf("Criando um CÍRCULO:\n");
            printf("Digite o raio: ");
            scanf("%f%*c", &ptr2->r);
            return (void*)ptr2;
        break;
        case TRI:
            Triangulo* ptr3 = (Triangulo*)malloc(sizeof(Triangulo));
            printf("Criando um TRIÂNGULO:\n");
            printf("Digite a base: ");
            scanf("%f%*c", &ptr3->b);
            printf("Digite a altura: ");
            scanf("%f%*c", &ptr3->h);
            return (void*)ptr3;
        break;
        default:
            printf("\nTipo indefinido!!!\n");
            return NULL;
    }
}

Listahet* lsthet_retira(Listahet* l, int id);

/*LSTHET_VAZIA
Parêmetros: 
l    = cabeça da minha lista.
Retorna:
inteiro sinalizando que a lista está
vazia (1) ou não vazia (0).
*/
int lsthet_vazia(Listahet* l){
    return l == NULL;
}
Listahet* lsthet_busca(Listahet *l, int id);

/*LSTHET_IMPRIME
Parêmetros: 
l    = cabeça da minha lista.
Retorna:
Void.
Imprime na tela todos os elementos da lista.
*/
void lsthet_imprime(Listahet *l){
    for( ; l != NULL; l = l->prox){
        switch(l->tipo){
            case RET:
                Retangulo* ret = (Retangulo*)l->info;
                printf("====Retângulo====\n");
                printf("base: %.2f\n", ret->b);
                printf("altura: %.2f\n", ret->h);
                printf("=================\n");
            break;
            case TRI:
                Triangulo* tri = (Triangulo*)l->info;
                printf("====Triângulo====\n");
                printf("base: %.2f\n", tri->b);
                printf("altura: %.2f\n", tri->h);
                printf("=================\n");
            break;
            case CIR:
                Circulo* cir = (Circulo*)l->info;
                printf("====Círculo====\n");
                printf("raio: %.2f\n", cir->r);
                printf("=================\n");
            break;
            default:
            printf("Tipo não suportado...\n");
        }
    }

}