#ifndef __TAD_HASHTABLE_H__
#define __TAD_HASHTABLE_H__

#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_LENGTH 3500

// --- ESTRUTURAS DE DADOS GENÉRICAS ---

/*
  Estrutura para representar uma linha genérica de um arquivo CSV.
  Armazena os campos como um array de strings.
 */
typedef struct RowData
{
    char **fields;  // Array de strings para os campos da linha.
    int num_fields; // Número de campos nesta linha.
} RowData;

/*
  Nó da lista encadeada para a tabela hash.
  Agora aponta para uma RowData genérica.
 */
typedef struct Node
{
    int key;           // Chave usada para indexar este nó na tabela hash.
    RowData *data;     // Ponteiro para os dados associados a essa chave (linha com vários campos).
    struct Node *next; // Ponteiro para o próximo nó da lista (caso haja colisão).
} Node;

/*
  Estrutura principal da Tabela Hash.
  Adicionados campos para armazenar o cabeçalho do CSV.
 */
typedef struct hash
{
    char *file_name;
    unsigned int max_lines; // add
    char **header;          // Novo: armazena os nomes das colunas do cabeçalho.
    int num_columns;        // Novo: armazena o número de colunas.
    void **HASH_TABLE;
    Node **CSV_LINE_TABLE;
    unsigned char *DIRTY_LINE_TABLE;
} Hash;

// --- PROTÓTIPOS DAS FUNÇÕES ---

// Funções principais do TAD
Hash *hsh_create(char *file_name, int table_length);
void hsh_free(Hash *hash_table, char *(*to_csv_line)(void *));
void hsh_update(Hash *hash_table, void *info, char *(*to_csv_line)(void *), unsigned int line_id);
void *hsh_busca(Hash *hash_table, unsigned int line_id, void *(*from_csv_line)(void *));
void hsh_delete(Hash *hash_table, unsigned int line_id);

// Funções auxiliares e de conversão
static int hsh_function(unsigned int csv_line);

/*
 * Counts how many lines there are in the CSV file.
 *
 * Parameters:
 * - filename: name of the CSV file.
 *
 * Returns:
 * - Number of lines in the file (excluding '\0').
 * - Returns -1 on error.
 */
int count_file_lines(const char *filename);
char *row_to_csv_line(void *data_ptr); // Função de conversão atualizada
void free_row_data(void *data_ptr);    // Função de liberação de memória atualizada
#include "TAD_HASHTABLE.c"
#endif