#ifndef __TAD_TREE_H__
    #define __TAD_TREE_H__
    typedef struct node{
        void* info;
        struct node* lst;
        struct node* rst;
    }Node;

    typedef struct nodelist{
        void* info;
        struct nodelist* next;
    }Nodelist;

    int tree_empty(Node* root);
    Node* tree_create_empty();
    void tree_free(Node* root);
 
    Node* tree_create_node(void* info, Node* lst, Node* rst); // Santana
    void tree_map(Node* root, void (operation)(void*)); // Linhares
    Node* tree_search(Node* root, int (condition)(void*)); // Damasceno
    int tree_update(Node* root, void (update)(void*)); // Silva
    Node* tree_load_from_file(char* file_name, void* (read_line)(char*)); // Santana
    void tree_to_file(Node* root, char* file_name, char* (create_line)(void*)); // Damasceno
 
    Node* tree_filter(Node* root, int (condition)(void*));
    Node* tree_delete_node(Node* root, int (condition)(void*));
    Node* tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*));

    Node* tree_insert_balanced(Node* root, Node* new_node, int (compare)(void*, void*)); //Ribeiro
    Node* tree_delete_balanced(Node* root, Node* new_node, int (compare)(void*, void*)); //Medonça

    #include "TAD_TREE.c"
#endif