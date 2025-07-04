#include "TAD_HASHTABLE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_file_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro ao abrir arquivo para contagem");
        return -1;
    }
    int count = 0;
    char buffer[3500];
    while (fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }
    fclose(file);
    return count;
}

char *data_to_csv_line(void *data_ptr)
{
    Data *d = (Data *)data_ptr;
    if (!d)
        return NULL;
    char *line = (char *)malloc(2048 * sizeof(char));
    sprintf(line, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",
            d->series_reference, d->period, d->type, d->data_value, d->lower_ci,
            d->upper_ci, d->units, d->indicator, d->cause, d->validation,
            d->population, d->age, d->severity);
    return line;
}

void free_data(void *data_ptr)
{
    Data *data = (Data *)data_ptr;
    if (data)
    {
        free(data->series_reference);
        free(data->period);
        free(data->type);
        free(data->data_value);
        free(data->lower_ci);
        free(data->upper_ci);
        free(data->units);
        free(data->indicator);
        free(data->cause);
        free(data->validation);
        free(data->population);
        free(data->age);
        free(data->severity);
        free(data);
    }
}

static int hsh_function(unsigned int csv_line)
{
    return csv_line % HASH_TABLE_LENGTH;
}

Hash *hsh_create(char *file_name, int table_length)
{
    Hash *h = (Hash *)malloc(sizeof(Hash));
    h->file_name = strdup(file_name);
    h->max_lines = count_file_lines(file_name);

    int len = (table_length > 0) ? table_length : HASH_TABLE_LENGTH;
    h->HASH_TABLE = calloc(len, sizeof(void *));
    h->CSV_LINE_TABLE = calloc(h->max_lines, sizeof(Node *));
    h->DIRTY_LINE_TABLE = calloc(h->max_lines, sizeof(unsigned char));
    return h;
}

void *hsh_busca(Hash *hash_table, unsigned int line_id, void *(*from_csv_line)(void *))
{
    if (line_id >= hash_table->max_lines || hash_table->CSV_LINE_TABLE[line_id] == NULL)
    {
        return NULL;
    }
    return (void *)hash_table->CSV_LINE_TABLE[line_id]->data;
}

void hsh_delete(Hash *hash_table, unsigned int line_id)
{
    if (line_id >= hash_table->max_lines || hash_table->CSV_LINE_TABLE[line_id] == NULL)
    {
        return;
    }

    unsigned int index = hsh_function(line_id);
    Node *node_to_delete = hash_table->CSV_LINE_TABLE[line_id];

    Node **p_current = (Node **)&(hash_table->HASH_TABLE[index]);
    while (*p_current && *p_current != node_to_delete)
    {
        p_current = &((*p_current)->next);
    }

    if (*p_current == node_to_delete)
    {
        *p_current = node_to_delete->next;
    }

    free_data(node_to_delete->data);
    free(node_to_delete);

    hash_table->CSV_LINE_TABLE[line_id] = NULL;
    hash_table->DIRTY_LINE_TABLE[line_id] = 1;
}

void hsh_update(Hash *hash_table, void *info, char *(*to_csv_line)(void *), unsigned int line_id)
{
    if (line_id >= hash_table->max_lines)
        return;

    Node *target_node = hash_table->CSV_LINE_TABLE[line_id];

    if (target_node != NULL)
    {
        free_data(target_node->data);
        target_node->data = (Data *)info;
    }
    else
    {
        unsigned int index = hsh_function(line_id);
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->key = line_id;
        new_node->data = (Data *)info;

        new_node->next = (Node *)hash_table->HASH_TABLE[index];
        hash_table->HASH_TABLE[index] = new_node;

        hash_table->CSV_LINE_TABLE[line_id] = new_node;
    }

    hash_table->DIRTY_LINE_TABLE[line_id] = 1;
}

void hsh_free(Hash *hash_table, char *(*to_csv_line)(void *))
{

    if (to_csv_line != NULL)
    {
        char temp_filename[512];
        sprintf(temp_filename, "%s.tmp", hash_table->file_name);

        FILE *temp_file = fopen(temp_filename, "w");
        if (temp_file)
        {
            fprintf(temp_file, "Series_reference,Period,Type,Data_value,Lower_CI,Upper_CI,Units,Indicator,Cause,Validation,Population,Age,Severity\n");
            for (int i = 0; i < hash_table->max_lines; i++)
            {
                if (hash_table->CSV_LINE_TABLE[i] != NULL)
                {
                    char *line_csv = to_csv_line(hash_table->CSV_LINE_TABLE[i]->data);
                    if (line_csv)
                    {
                        fprintf(temp_file, "%s\n", line_csv);
                        free(line_csv);
                    }
                }
            }
            fclose(temp_file);

            remove(hash_table->file_name);

            rename(temp_filename, hash_table->file_name);

            printf("\nArquivo '%s' atualizado com sucesso.\n", hash_table->file_name);
        }
        else
        {
            perror("Erro ao criar arquivo temporário. As alterações não foram salvas.");
        }
    }

    for (int i = 0; i < HASH_TABLE_LENGTH; i++)
    {
        Node *current = (Node *)hash_table->HASH_TABLE[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free_data(temp->data);
            free(temp);
        }
    }

    free(hash_table->HASH_TABLE);
    free(hash_table->CSV_LINE_TABLE);
    free(hash_table->DIRTY_LINE_TABLE);
    free(hash_table->file_name);
    free(hash_table);
}