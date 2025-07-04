#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_HASHTABLE.h"

#define MAX_LINE_LEN 3500

void *parse_csv_line(void *line_ptr)
{
    char *line = (char *)line_ptr;
    Data *data = (Data *)malloc(sizeof(Data));
    if (!data)
        return NULL;

    char *line_copy = strdup(line);
    char *token;
    token = strtok(line_copy, ",");
    data->series_reference = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->period = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->type = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->data_value = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->lower_ci = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->upper_ci = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->units = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->indicator = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->cause = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->validation = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->population = strdup(token ? token : "");
    token = strtok(NULL, ",");
    data->age = strdup(token ? token : "");
    token = strtok(NULL, "\n");
    data->severity = strdup(token ? token : "");
    free(line_copy);
    return data;
}

int main()
{
    char filename[] = "./output/aluno.csv";
    Hash *h = hsh_create(filename, HASH_TABLE_LENGTH);
    if (!h)
    {
        printf("Falha ao criar a estrutura hash.\n");
        return 1;
    }

    FILE *file = fopen(h->file_name, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo CSV");
        hsh_free(h, NULL);
        return 1;
    }

    char line[MAX_LINE_LEN];
    fgets(line, MAX_LINE_LEN, file);

    for (int i = 0; i < h->max_lines - 1; i++)
    {
        if (fgets(line, MAX_LINE_LEN, file))
        {
            hsh_update(h, parse_csv_line(line), data_to_csv_line, i);
        }
    }
    fclose(file);
    printf("Arquivo '%s' carregado com sucesso.\n", h->file_name);

    int choice;
    do
    {
        printf("\nMenu:\n1. LER\n2. ALTERAR\n3. DELETAR\n4. BUSCAR\n5. SALVAR E SAIR\n0. SAIR SEM SALVAR\nEscolha: ");
        scanf("%d", &choice);

        int user_line_num;
        unsigned int internal_index;

        if (choice >= 1 && choice <= 4)
        {
            printf("Digite o número da linha de dados (1 em diante): ");
            scanf("%d", &user_line_num);
            if (user_line_num <= 0)
            {
                printf("-> Linha inválida. Deve ser 1 ou maior.\n");
                continue;
            }
            internal_index = user_line_num - 1;
        }
        else
        {
            internal_index = -1;
        }

        switch (choice)
        {
        case 1:
        {
            Data *data = (Data *)hsh_busca(h, internal_index, NULL);
            if (data)
            {
                printf("-> Dados da linha %d: Cause = %s\n", user_line_num, data->cause);
            }
            else
            {
                printf("-> Linha %d não encontrada.\n", user_line_num);
            }
            break;
        }
        case 2:
        {
            Data *old_data = (Data *)hsh_busca(h, internal_index, NULL);
            if (old_data)
            {
                char buffer[256];
                printf("  -> Causa atual: %s\n", old_data->cause);
                printf("  Digite a nova 'Cause': ");
                scanf(" %255[^\n]", buffer);

                Data *new_data = (Data *)malloc(sizeof(Data));

                new_data->series_reference = strdup(old_data->series_reference);
                new_data->period = strdup(old_data->period);
                new_data->type = strdup(old_data->type);
                new_data->data_value = strdup(old_data->data_value);
                new_data->lower_ci = strdup(old_data->lower_ci);
                new_data->upper_ci = strdup(old_data->upper_ci);
                new_data->units = strdup(old_data->units);
                new_data->indicator = strdup(old_data->indicator);
                new_data->validation = strdup(old_data->validation);
                new_data->population = strdup(old_data->population);
                new_data->age = strdup(old_data->age);
                new_data->severity = strdup(old_data->severity);

                new_data->cause = strdup(buffer);

                hsh_update(h, new_data, data_to_csv_line, internal_index);
                printf("-> Linha %d atualizada.\n", user_line_num);
            }
            else
            {
                printf("-> Linha %d não existe.\n", user_line_num);
            }
            break;
        }
        case 3:
        {
            hsh_delete(h, internal_index);
            printf("-> Linha %d deletada (se existia).\n", user_line_num);
            break;
        }
        case 4:
        {
            if (hsh_busca(h, internal_index, NULL))
            {
                printf("-> Informação encontrada na linha %d.\n", user_line_num);
            }
            else
            {
                printf("-> Nenhuma informação para a linha %d.\n", user_line_num);
            }
            break;
        }
        case 5:
        {
            hsh_free(h, data_to_csv_line);
            printf("-> Operação finalizada.\n");
            return 0;
        }
        case 0:
        {
            printf("Saindo sem salvar...\n");
            hsh_free(h, NULL);
            return 0;
        }
        default:
            printf("Opção inválida!\n");
        }
    } while (1);
}