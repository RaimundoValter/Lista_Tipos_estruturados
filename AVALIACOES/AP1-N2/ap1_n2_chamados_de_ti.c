#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../TAD_LISTA/TAD_LISTA.h"
#include "../../TAD_TREE/TAD_TREE.h"

typedef struct atendimento
{
    int id_chamado;
    int id_usuario;
    char solicitante[100];
    char setor[50];
    char data[11];
    char problema[100];
    int resolvido;
} AtendimentoTI;

// Estrutura para a avaliação de satisfação de um atendimento.
typedef struct avaliacao
{
    int id_chamado;
    int satisfacao;
    char comentario[200];
} AvaliacaoTI;

// Estrutura para armazenar o resultado da união dos dados de atendimento e avaliação.
typedef struct uniao
{
    int id_usuario;
    char solicitante[100];
    char comentario[200];
    char setor[50]; // Campo necessário para o relatório
    int satisfacao; // Campo necessário para o relatório
} Uniao;

// Estrutura auxiliar para a construção do relatório de satisfação por setor.
typedef struct relatorio_setor
{
    char nome_setor[50];
    float soma_satisfacao;
    int contador_avaliacoes;
} RelatorioSetor;

// Variável global para auxiliar na busca dentro da árvore por ID.
int id_chamado_para_buscar;

void *ler_linha_atendimento(char *linha_arquivo);
void *criar_chamado(int id_atual);
char *montar_linha_atendimento(void *elemento);
void formatacao_atendimento(void *elemento);

// Funções de União de Dados
Lista *unir_dados(Node *arvore_chamados);
void *ler_linha_avaliacao(char *linha_arquivo);
int condicao_busca_id(void *info_no);

// Funções de Análise e Relatório
void executar_analise_de_dados(Node *arvore_chamados);
void gerar_relatorio_satisfacao_por_setor(Lista *lista_uniao);

void *copia_chamado(void *info);
int verifica_chamado_aberto(void *elemento);
int verifica_id_chamado_maior(void *elemento1, void *elemento2);
int verifica_setor_igual(void *r, void *nome_setor);
int insere_em_qualquer_lugar();
int todos_registros(void *elemento);

int main(void)
{
    Node *Atendimentos = tree_create_empty();

    // 1. Carrega os dados dos chamados do arquivo para a árvore
    Atendimentos = tree_load_from_file("banco_de_dados_chamados.csv", ler_linha_atendimento, verifica_id_chamado_maior);
    printf("=> Árvore de chamados carregada da memória.\n");
    tree_map(Atendimentos, formatacao_atendimento);

    // 2. Filtra e exibe os chamados que ainda não foram resolvidos
    printf("\n=> Imprimindo chamados não resolvidos:\n");
    Lista *chamados_abertos = tree_filter_as_list(Atendimentos, verifica_chamado_aberto, copia_chamado, verifica_id_chamado_maior);
    lst_map(chamados_abertos, formatacao_atendimento, todos_registros);
    lst_libera(chamados_abertos);

    // 3. Insere um novo chamado (para fins de demonstração)
    printf("\n=> Inserindo 1 elemento novo na árvore:\n");
    AtendimentoTI *chamado_novo = criar_chamado(51); // Exemplo com ID fixo
    if (chamado_novo)
    {
        Atendimentos = tree_insert_node(Atendimentos,
                                        tree_create_node(chamado_novo, tree_create_empty(), tree_create_empty()),
                                        verifica_id_chamado_maior);
    }
    printf("\n=> Árvore após inserção:\n");
    tree_map(Atendimentos, formatacao_atendimento);

    // 4. Salva o estado atual da árvore de volta no arquivo
    tree_to_file(Atendimentos, "banco_de_dados_chamados.csv", montar_linha_atendimento);
    printf("\nÁrvore de chamados foi salva em 'banco_de_dados_chamados.csv'.\n");

    // 5. Executa a rotina de análise e geração de relatórios
    executar_analise_de_dados(Atendimentos);

    // 6. Libera a memória alocada para a árvore
    printf("\nLiberando a árvore de chamados...\n");
    tree_free(Atendimentos);
    printf("Programa finalizado com sucesso.\n");

    return 0;
}

void executar_analise_de_dados(Node *arvore_chamados)
{
    printf("INICIANDO PROCESSO DE ANÁLISE E RELATÓRIOS...\n");

    // Une os dados dos arquivos de chamados e satisfação
    Lista *lista_unida_completa = unir_dados(arvore_chamados);

    if (lst_vazia(lista_unida_completa))
    {
        printf("Nenhum dado correspondente encontrado para gerar relatórios.\n");
    }
    else
    {
        printf("Dados de chamados e avaliações unidos com sucesso.\n");
        // Gera o relatório de satisfação agrupado por setor
        gerar_relatorio_satisfacao_por_setor(lista_unida_completa);
        // Libera a memória da lista unida que foi criada para a análise
        lst_libera(lista_unida_completa);
    }
}

void gerar_relatorio_satisfacao_por_setor(Lista *lista_uniao)
{
    printf("\n--- RELATÓRIO DE SATISFAÇÃO POR SETOR ---\n");

    Lista *relatorio = lst_cria();

    for (Lista *p = lista_uniao; p != NULL; p = p->prox)
    {
        Uniao *dado_atual = (Uniao *)p->info;
        RelatorioSetor *setor_existente = (RelatorioSetor *)lst_busca(relatorio, dado_atual->setor, verifica_setor_igual);

        if (setor_existente != NULL)
        {
            setor_existente->soma_satisfacao += dado_atual->satisfacao;
            setor_existente->contador_avaliacoes++;
        }
        else
        {
            RelatorioSetor *novo_setor = (RelatorioSetor *)malloc(sizeof(RelatorioSetor));
            strcpy(novo_setor->nome_setor, dado_atual->setor);
            novo_setor->soma_satisfacao = dado_atual->satisfacao;
            novo_setor->contador_avaliacoes = 1;
            relatorio = lst_insere(relatorio, novo_setor, insere_em_qualquer_lugar);
        }
    }

    // Imprime os resultados finais do relatório
    for (Lista *p = relatorio; p != NULL; p = p->prox)
    {
        RelatorioSetor *r_final = (RelatorioSetor *)p->info;
        float media = r_final->soma_satisfacao / r_final->contador_avaliacoes;
        printf("Setor: %-20s | Média de Satisfação: %.2f | Avaliações: %d\n",
               r_final->nome_setor, media, r_final->contador_avaliacoes);
    }

    lst_libera(relatorio);
}

// Funções de União de Dados

Lista *unir_dados(Node *arvore_chamados)
{
    Lista *lista_avaliacoes = lst_carrega(lst_cria(), "banco_de_dados_satisfacao.csv", ler_linha_avaliacao);

    if (lst_vazia(lista_avaliacoes))
    {
        printf("AVISO: Arquivo 'banco_de_dados_satisfacao.csv' não pôde ser carregado ou está vazio.\n");
        return NULL;
    }

    Lista *lista_uniao = lst_cria();

    for (Lista *p_aval = lista_avaliacoes; p_aval != NULL; p_aval = p_aval->prox)
    {
        AvaliacaoTI *avaliacao_atual = (AvaliacaoTI *)p_aval->info;
        id_chamado_para_buscar = avaliacao_atual->id_chamado;
        Node *no_encontrado = tree_search(arvore_chamados, condicao_busca_id);

        if (no_encontrado != NULL)
        {
            AtendimentoTI *atendimento = (AtendimentoTI *)no_encontrado->info;
            Uniao *novo_unido = (Uniao *)malloc(sizeof(Uniao));

            novo_unido->id_usuario = atendimento->id_usuario;
            strcpy(novo_unido->solicitante, atendimento->solicitante);
            strcpy(novo_unido->comentario, avaliacao_atual->comentario);
            strcpy(novo_unido->setor, atendimento->setor);
            novo_unido->satisfacao = avaliacao_atual->satisfacao;

            lista_uniao = lst_insere(lista_uniao, novo_unido, insere_em_qualquer_lugar);
        }
    }

    lst_libera(lista_avaliacoes);
    return lista_uniao;
}

// Funções de Chamados de TI e Auxiliares

void formatacao_atendimento(void *elemento)
{
    AtendimentoTI *atendimento = (AtendimentoTI *)elemento;
    printf("| %-4d | %-4d | %-25s | Resolvido: %d\n", atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante, atendimento->resolvido);
}

void *ler_linha_atendimento(char *linha_arquivo)
{
    AtendimentoTI *novo = (AtendimentoTI *)malloc(sizeof(AtendimentoTI));
    sscanf(linha_arquivo, "%d;%d;%99[^;];%49[^;];%10[^;];%99[^;];%d",
           &novo->id_chamado, &novo->id_usuario, novo->solicitante,
           novo->setor, novo->data, novo->problema, &novo->resolvido);
    return novo;
}

void *ler_linha_avaliacao(char *linha_arquivo)
{
    AvaliacaoTI *novo = (AvaliacaoTI *)malloc(sizeof(AvaliacaoTI));
    sscanf(linha_arquivo, "%d;%d;%199[^\n]", &novo->id_chamado, &novo->satisfacao, novo->comentario);
    return novo;
}

char *montar_linha_atendimento(void *elemento)
{
    AtendimentoTI *atendimento = (AtendimentoTI *)elemento;
    char *linha = (char *)malloc(300 * sizeof(char));
    sprintf(linha, "%d;%d;%s;%s;%s;%s;%d\n",
            atendimento->id_chamado, atendimento->id_usuario, atendimento->solicitante,
            atendimento->setor, atendimento->data, atendimento->problema, atendimento->resolvido);
    return linha;
}

void *criar_chamado(int id_atual)
{
    AtendimentoTI *novo = (AtendimentoTI *)malloc(sizeof(AtendimentoTI));
    novo->id_chamado = id_atual + 1;
    printf("Digite o ID do solicitante: ");
    scanf("%d%*c", &novo->id_usuario);
    printf("Digite o nome do solicitante: ");
    scanf("%99[^\n]%*c", novo->solicitante);
    printf("Digite o setor: ");
    scanf("%49[^\n]%*c", novo->setor);
    strcpy(novo->data, "13/06/2025"); // Data atual como exemplo
    printf("Digite a descrição do problema: ");
    scanf("%99[^\n]%*c", novo->problema);
    novo->resolvido = 0;
    return novo;
}

void *copia_chamado(void *info)
{
    AtendimentoTI *info_original = (AtendimentoTI *)info;
    AtendimentoTI *info_copia = (AtendimentoTI *)malloc(sizeof(AtendimentoTI));
    if (info_copia)
    {
        memcpy(info_copia, info_original, sizeof(AtendimentoTI));
    }
    return info_copia;
}

int verifica_chamado_aberto(void *elemento) { return ((AtendimentoTI *)elemento)->resolvido == 0; }
int verifica_id_chamado_maior(void *elemento1, void *elemento2) { return ((AtendimentoTI *)elemento1)->id_chamado < ((AtendimentoTI *)elemento2)->id_chamado; }
int condicao_busca_id(void *info_no) { return ((AtendimentoTI *)info_no)->id_chamado == id_chamado_para_buscar; }
int verifica_setor_igual(void *r, void *nome_setor) { return strcmp(((RelatorioSetor *)r)->nome_setor, (char *)nome_setor) == 0; }
int insere_em_qualquer_lugar() { return 1; }
int todos_registros(void *elemento) { return 1; }