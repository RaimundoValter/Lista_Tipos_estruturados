#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_HASHTABLE.h"

#define MAX_LINE_LEN 3500
#define INITIAL_FIELDS 20 // Capacidade inicial para colunas em uma linha

void *parse_generic_csv_line(char *line);
void print_row(RowData *data, char **header, int num_columns);

int main()
{

    char filename[] = "./output/serious-injury-outcome-indicators-2000-2023.csv";

    // Verificação inicial se o arquivo existe.
    FILE *check_file = fopen(filename, "r");
    if (!check_file)
    {
        printf("\nNao foi possivel abrir o arquivo CSV. Verifique o caminho e o nome");
        return 1;
    }
    fclose(check_file);

    Hash *h = hsh_create(filename, HASH_TABLE_LENGTH);
    if (!h)
    {
        printf("\nFalha ao criar a estrutura hash.\n");
        return 1;
    }

    FILE *file = fopen(h->file_name, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo CSV");
        hsh_free(h, NULL);
        return 1;
    }

    // Lê o cabeçalho
    char line[MAX_LINE_LEN];
    if (fgets(line, MAX_LINE_LEN, file))
    {
        RowData *header_data = parse_generic_csv_line(line);
        h->header = header_data->fields;
        h->num_columns = header_data->num_fields;
        free(header_data);
    }

    // Lê o resto do arquivo e popula a hash
    for (unsigned int i = 0; i < h->max_lines - 1; i++)
    {
        if (fgets(line, MAX_LINE_LEN, file))
        {
            hsh_update(h, parse_generic_csv_line(line), row_to_csv_line, i);
        }
    }
    fclose(file);
    printf("Arquivo '%s' carregado com %d colunas.\n", h->file_name, h->num_columns);

    int choice;
    do
    {
        printf("\nMenu:\n1. LER\n2. ALTERAR\n3. DELETAR\n4. BUSCAR\n5. SALVAR E SAIR\n0. SAIR SEM SALVAR\nEscolha: ");
        scanf("%d", &choice);

        int user_line_num = -1;
        unsigned int internal_index = -1;

        if (choice >= 1 && choice <= 4)
        {
            printf("\nDigite o numero da linha de dados (a primeira linha de dados e a linha 1): ");
            scanf("%d", &user_line_num);
            if (user_line_num <= 0)
            {
                printf("\n-> Linha invalida. Deve ser 1 ou maior.\n");
                continue;
            }
            internal_index = user_line_num - 1;
        }

        switch (choice)
        {
        case 1:
        { // LER
            RowData *data = (RowData *)hsh_busca(h, internal_index, NULL);
            if (data)
            {
                printf("\n-> Dados da linha %d:\n", user_line_num);
                print_row(data, h->header, h->num_columns);
            }
            else
            {
                printf("\n-> Linha %d nao encontrada ou vazia.\n", user_line_num);
            }
            break;
        }
        case 2:
        { // ALTERAR
            RowData *old_data = (RowData *)hsh_busca(h, internal_index, NULL);
            if (old_data)
            {
                printf("\nDados atuais da linha %d:\n", user_line_num);
                print_row(old_data, h->header, h->num_columns);

                int col_to_change;
                printf("\nDigite o numero da coluna que deseja alterar (1 a %d): ", h->num_columns);
                scanf("%d", &col_to_change);

                if (col_to_change < 1 || col_to_change > h->num_columns)
                {
                    printf("\n-> Coluna invalida.\n");
                    break;
                }
                int col_index = col_to_change - 1;

                char buffer[256];
                printf("\nDigite o novo valor para a coluna '%s': ", h->header[col_index]);
                scanf(" %255[^\n]", buffer);

                RowData *new_data = (RowData *)malloc(sizeof(RowData));
                new_data->num_fields = old_data->num_fields;
                new_data->fields = malloc(new_data->num_fields * sizeof(char *));

                for (int i = 0; i < new_data->num_fields; i++)
                {
                    if (i == col_index)
                    {
                        new_data->fields[i] = strdup(buffer);
                    }
                    else
                    {
                        new_data->fields[i] = strdup(old_data->fields[i]);
                    }
                }

                hsh_update(h, new_data, row_to_csv_line, internal_index);
                printf("\n-> Linha %d atualizada com sucesso.\n", user_line_num);
            }
            else
            {
                printf("\n-> Linha %d nao existe e não pode ser alterada.\n", user_line_num);
            }
            break;
        }
        case 3:
        { // DELETAR
            hsh_delete(h, internal_index);
            printf("\n-> Linha %d deletada (se existia).\n", user_line_num);
            break;
        }
        case 4:
        { // BUSCAR
            if (hsh_busca(h, internal_index, NULL))
            {
                printf("\n-> Informacao encontrada na linha %d.\n", user_line_num);
            }
            else
            {
                printf("\n-> Nenhuma informacao para a linha %d.\n", user_line_num);
            }
            break;
        }
        case 5:
        { // SALVAR E SAIR
            hsh_free(h, row_to_csv_line);
            printf("\n-> Alteracoes salvas. Operação finalizada.\n");
            return 0;
        }
        case 0:
        {
            printf("\n\nSaindo sem salvar...\n");
            hsh_free(h, NULL);
            return 0;
        }
        default:
            printf("\nOpção invlida!\n");
        }
    } while (1);

    return 0;
}

void *parse_generic_csv_line(char *line)
{
    RowData *data = (RowData *)malloc(sizeof(RowData));
    if (!data)
        return NULL;

    data->fields = malloc(INITIAL_FIELDS * sizeof(char *));
    data->num_fields = 0;
    int capacity = INITIAL_FIELDS;

    char *line_copy = strdup(line);
    line_copy[strcspn(line_copy, "\r\n")] = 0; // Remove quebras de linha

    char *token = strtok(line_copy, ","); // ver oq é esse token
    while (token)
    {
        if (data->num_fields >= capacity)
        {
            capacity *= 2;
            data->fields = realloc(data->fields, capacity * sizeof(char *));
        }
        // Remove aspas se existirem no início e fim do token
        if (token[0] == '"')
            token++;
        if (strlen(token) > 0 && token[strlen(token) - 1] == '"')
            token[strlen(token) - 1] = '\0';

        data->fields[data->num_fields++] = strdup(token);
        token = strtok(NULL, ",");
    }

    free(line_copy);
    return data;
}

/*
 Função auxiliar para imprimir uma linha de dados de forma legível,
 usando o cabeçalho para descrever cada campo.
*/
void print_row(RowData *data, char **header, int num_columns)
{
    for (int i = 0; i < data->num_fields; i++)
    {
        if (header && i < num_columns)
        {
            printf("  -> %s: %s\n", header[i], data->fields[i]);
        }
        else
        {
            printf("  -> Coluna %d: %s\n", i + 1, data->fields[i]);
        }
    }
}