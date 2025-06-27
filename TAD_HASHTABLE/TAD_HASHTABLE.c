#include "TAD_HASHTABLE.c"
#include <stdlib.h>
#include <stdio.h>

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
Hash* hsh_create(char* file_name, int table_length);

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
void hsh_free(Hash* hash_table, char* (to_csv_line)(void*));

/*CALCULATES THE HASH OF A CSV LINE
    Determines the index in the hash table where
    the given CSV line (representing a record to 
    be recovered) should be stored.
Params
    - csv_line: Pointer to the CSV line representing the record.
Return
    The hash table index corresponding to the line.
*/
static int hsh_function(unsigned int csv_line);

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
void hsh_update(Hash* hash_table, void* info, char* (to_csv_line)(void*), unsigned int line_id);

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
void* hsh_busca(Hash* hash_table, unsigned int line_id, void* (from_csv_line)(void*));

/* DELETES INFORMATION AT A SPECIFIC CSV LINE
    Removes the information located at the given
    line index in the CSV file.
Params
    - hash_table: Pointer to the hash table.
    - line_id: Index of the line in the CSV file.
Return
    
*/
void hsh_delete(Hash* hash_table, unsigned int line_id);