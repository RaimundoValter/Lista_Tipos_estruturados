Listahet* lsthet_cria(void){
    return NULL;
}

Listahet* lsthet_libera(Listahet* l);

/*LST_INSERE
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

void* lsthet_cria_elemento(int tipo){
    switch(tipo){
        case RET:
            Retangulo* ptr = (Retangulo*)malloc(sizeof(Retangulo));
            printf("Criando um RETÂNGULO:\n")
            printf("Digite a base: ");
            scanf("%f%*c", &ptr->b);
            printf("Digite a altura: ");
            scanf("%f%*c", &ptr->h);
        break;
        case CIR:
            Circulo* ptr = (Circulo*)malloc(sizeof(Circulo));
            printf("Criando um CÍRCULO:\n")
            printf("Digite o raio: ");
            scanf("%f%*c", &ptr->r);
        break;
        case TRI:
            Triangulo* ptr = (Triangulo*)malloc(sizeof(Triangulo));
            printf("Criando um TRIÂNGULO:\n")
            printf("Digite a base: ");
            scanf("%f%*c", &ptr->b);
            printf("Digite a altura: ");
            scanf("%f%*c", &ptr->h);
        break;
        default:
            printf("\nTipo indefinido!!!\n");
            return NULL;
    }

    return (void*)ptr;
}

Listahet* lsthet_retira(Listahet* l, int id);

int lsthet_vazia(Listahet* l){
    return l == NULL;
}
Listahet* lsthet_busca(Listahet *l, int id);
void lsthet_imprime(Listahet *l);