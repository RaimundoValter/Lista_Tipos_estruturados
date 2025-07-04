#include "TAD_HASHTABLE.h"
#include <string.h>

/*
 Counts how many lines there are in the CSV file.

 Parameters:
- filename: name of the CSV file.

 Returns:
- Number of lines in the file (excluding '\0').
- Returns -1 in case of error.
*/
int count_file_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir arquivo para contagem");
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

/*
 Converte uma estrutura RowData de volta para uma string formatada como CSV.
 É a nova versão genérica de data_to_csv_line.
*/

/*
 Converts a RowData structure to a CSV string.
 Each field is enclosed in quotes and separated by commas.

 Parameters:
 - data_ptr: pointer to a RowData structure.

 Returns:
 - Pointer to a dynamically allocated CSV string.
*/
char *row_to_csv_line(void *data_ptr)
{
    RowData *d = (RowData *)data_ptr;
    if (!d || d->num_fields == 0)
        return NULL;

    unsigned int total_len = 1; // Para o caractere nulo de terminação
    for (int i = 0; i < d->num_fields; i++)
    {
        total_len += strlen(d->fields[i]) + 3; // +3 para aspas e vírgula/null
    }

    char *line = (char *)malloc(total_len * sizeof(char));
    if (!line)
        return NULL;

    line[0] = '\0';

    int pos = 0;
    for (int i = 0; i < d->num_fields; i++)
    {

        pos += sprintf(line + pos, "\"%s\"", d->fields[i]);

        if (i < d->num_fields - 1)
        {
            pos += sprintf(line + pos, ",");
        }
    }
    line[pos] = '\0';
    return line;
}

/* FREE ROW DATA
 Frees the memory allocated for a RowData structure,
 including all fields.

 Parameters:
 - data_ptr: pointer to RowData to be freed.
*/
void free_row_data(void *data_ptr)
{
    RowData *data = (RowData *)data_ptr;
    if (data)
    {
        if (data->fields)
        {
            for (int i = 0; i < data->num_fields; i++)
            {
                free(data->fields[i]); // Libera cada string (campo) individualmente
            }
            free(data->fields); // Libera o array de ponteiros fields (campo)
        }
        free(data); // Libera a memória do próprio struct
    }
}

/*CALCULATES THE HASH OF A CSV LINE
    Determines the index in the hash table where
    the given CSV line (representing a record to
    be recovered) should be stored.
Params
    - csv_line: Pointer to the CSV line representing the record.
Return
    The hash table index corresponding to the line.
*/
static int hsh_function(unsigned int csv_line)
{
    return csv_line % HASH_TABLE_LENGTH;
}

/*CREATES A HASH TABLE
    Initializes a hash table to manage
    the lines of a CSV file.

Params
    - file_name: Pointer to a string representing the file
        name.
    - table_length: Length of the hash table. If 0, the default
        HASH_TABLE_LENGTH is used.
Return
    Pointer to a struct hash.
*/
Hash *hsh_create(char *file_name, int table_length)
{
    Hash *h = (Hash *)malloc(sizeof(Hash));
    h->file_name = strdup(file_name);
    h->max_lines = count_file_lines(file_name);
    h->header = NULL;   // Será preenchido na main
    h->num_columns = 0; // Será preenchido na main

    int len = (table_length > 0) ? table_length : HASH_TABLE_LENGTH;
    h->HASH_TABLE = calloc(len, sizeof(void *));
    h->CSV_LINE_TABLE = calloc(h->max_lines, sizeof(Node *));
    h->DIRTY_LINE_TABLE = calloc(h->max_lines, sizeof(unsigned char));
    return h;
}

/* SEARCHS FOR INFORMATION IN A SPECIFIC CSV LINE
    Retrieves a copy of the information located at
    the given line index in the CSV file.
Params
    - hash_table: Pointer to the hash table.
    - line_id: Index of the line in the CSV file.
    - from_csv_line: Callback function that reads a
    CSV line and loads the information into main memory.
Return
    Pointer to the recovered information, or NULL
    if the line index does not exist.
*/
void *hsh_busca(Hash *hash_table, unsigned int line_id, void *(*from_csv_line)(void *))
{
    if (line_id >= hash_table->max_lines || hash_table->CSV_LINE_TABLE[line_id] == NULL)
    {
        return NULL;
    }
    return (void *)hash_table->CSV_LINE_TABLE[line_id]->data;
}

/* DELETES INFORMATION AT A SPECIFIC CSV LINE
    Removes the information located at the given
    line index in the CSV file.
Params
    - hash_table: Pointer to the hash table.
    - line_id: Index of the line in the CSV file.
Return

*/
void hsh_delete(Hash *hash_table, unsigned int line_id)
{
    if (line_id >= hash_table->max_lines || hash_table->CSV_LINE_TABLE[line_id] == NULL)
        return;

    unsigned int index = hsh_function(line_id);
    Node *current = hash_table->HASH_TABLE[index];
    Node *previous = NULL;

    while (current && current != hash_table->CSV_LINE_TABLE[line_id]) // verifica se o current não esta em um ponto nulo e se ainda não esta na linha que queremos excluir
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return;

    // Se o nó a ser removido é o primeiro da lista
    if (previous == NULL)
    {
        hash_table->HASH_TABLE[index] = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free_row_data(current->data);
    free(current);

    hash_table->CSV_LINE_TABLE[line_id] = NULL;
    hash_table->DIRTY_LINE_TABLE[line_id] = 1;
}

/* UPDATES A SPECIFIC LINE IN A CSV FILE
   Updates information in a specific line of the CSV file.
   If the line does not exist, appends the information
   after the last line.
   Otherwise, it modifies the existing line in place.
Params
   - hash_table: Pointer to the hash table.
   - info: Pointer to the information to be written.
   - to_csv_line: Callback function that generates a CSV-formatted string from the information.
   - line_id: Index of the line to be updated in the CSV file.
Return

*/
void hsh_update(Hash *hash_table, void *info, char *(*to_csv_line)(void *), unsigned int line_id)
{
    // Se o ID da linha for maior que o maximo de linhas do arquivo, retorna sem fazer nada.
    if (line_id >= hash_table->max_lines)
        return;

    // Variavel para atualizar a linha, vai receber a linha que queremos atualizar
    Node *target_node = hash_table->CSV_LINE_TABLE[line_id];

    if (target_node != NULL)
    {
        free_row_data(target_node->data); // Libera a linha antiga e atualiza com os novos dados
        target_node->data = (RowData *)info;
    }
    else
    {
        // Criando e alocando espaco para um nova linha

        unsigned int index = hsh_function(line_id); // Calculo o indice com base no ID
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->key = line_id;
        new_node->data = (RowData *)info;
        new_node->next = (Node *)hash_table->HASH_TABLE[index]; // Adiciona o novo nó na frente dos elementos existentes.
        hash_table->HASH_TABLE[index] = new_node;               // Tabela agora aponta para o novo nó criado
        hash_table->CSV_LINE_TABLE[line_id] = new_node;         // Nó agora é acessado pelo id da linha
    }
    hash_table->DIRTY_LINE_TABLE[line_id] = 1;
}

/*FREES A HASH TABLE
    Deallocates memory used by the hash table.
    Before freeing, stores any dirty (modified)
    lines into the CSV file.
Params
    - hash_table: Pointer to the hash table.
    - to_csv_line: Callback function that generates
    a CSV-formatted string from a hash table entry.
Return

*/
void hsh_free(Hash *hash_table, char *(*to_csv_line)(void *))
{
    // Lógica para salvar alterações em arquivo temporário
    if (to_csv_line != NULL)
    {
        char temp_filename[512];
        sprintf(temp_filename, "%s.tmp", hash_table->file_name);

        FILE *temp_file = fopen(temp_filename, "w");
        if (temp_file)
        {
            // Escreve o cabeçalho salvo no início do arquivo
            if (hash_table->header)
            {
                for (int i = 0; i < hash_table->num_columns; i++)
                {
                    fprintf(temp_file, "\"%s\"%s", hash_table->header[i], (i == hash_table->num_columns - 1) ? "" : ",");
                }
                fprintf(temp_file, "\n");
            }

            // Escreve o resto das linhas
            for (unsigned int i = 0; i < hash_table->max_lines; i++)
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
            printf("Erro ao criar arquivo temporario");
        }
    }

    // Liberação de toda a memória
    for (int i = 0; i < HASH_TABLE_LENGTH; i++)
    {
        Node *current = (Node *)hash_table->HASH_TABLE[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free_row_data(temp->data); // ATUALIZADO
            free(temp);
        }
    }

    // Libera a memória do cabeçalho
    if (hash_table->header)
    {
        for (int i = 0; i < hash_table->num_columns; i++)
        {
            free(hash_table->header[i]);
        }
        free(hash_table->header);
    }

    free(hash_table->HASH_TABLE);
    free(hash_table->CSV_LINE_TABLE);
    free(hash_table->DIRTY_LINE_TABLE);
    free(hash_table->file_name);
    free(hash_table);
}