#include "TAD_TREE.h"
#include <stdlib.h>
#include <stdio.h>

/* IS IT EMPTY?
    Return
@@ -22,7 +24,13 @@ Node* tree_create_empty(){
        pointer to a new node (Node*).
*/
Node* tree_create_node(void* info, Node* lst, Node* rst){
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->info = info;
    new_node->lst = lst;
    new_node->rst = rst;

    return new_node;
}

/* INSERT A NODE
@@ -33,8 +41,16 @@ Node* tree_create_node(void* info, Node* lst, Node* rst){
        True if the new_node was placed in the tree,
        otherwise false.
*/
int tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*)){
Node* tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*)) {
    if (tree_empty(root)) return new_node;

    if (compare(new_node->info, root->info)) {
        root->lst = tree_insert_node(root->lst, new_node, compare);
    } else {
        root->rst = tree_insert_node(root->rst, new_node, compare);
    }

    return root;
}
/* FREE A TREE
    free memory of all elements in a tree/subtree starting from the "root" node.
@@ -59,7 +75,113 @@ Node* tree_filter(Node* root, int (condition)(void*));
 Return
    A pointer (Node*) to the first node that satisfied the conditino.
*/
Node* tree_search(Node* root, int (condition)(void*)){
Node* tree_search(Node* root, int (condition)(void*));

/* PRINT THE ELEMENTS OF THE TREE
 Shows the elements of the tree as if it were lying down, elements of the right
 going up and the elements of the left going down   
 */
void tree_print(Node* root, void (print)(void*), int depth) {
    if (tree_empty(root)) return;

    tree_print(root->rst, print, depth + 1);

    // Indentação proporcional à profundidade
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    print(root->info);

    tree_print(root->lst, print, depth + 1);
}

/* VERIFIES THE HEIGHT OF THE NODE
 Receives a node that calculates his height on the tree
 Return
    An integer for the height 
*/
int tree_get_height(Node* node) {
    if (tree_empty(node)) return -1; // Altura de NULL é -1 (por convenção)

    int left_height = tree_get_height(node->lst);
    int right_height = tree_get_height(node->rst);

    return 1 + (left_height > right_height ? left_height : right_height);
}

/* ROTATES THE TREE TO THE RIGHT
 Executes a rotation to the right, to fix the imbalance
 when the left subtree is heavier
 Return
    A pointer (Node*) to the new root
*/
Node* rotate_right(Node* root) {
    Node* node_lst = root->lst;          // node_lst é o filho da esquerda de root
    Node* node_lst_rst = node_lst->rst;  // node_lst_rst é a subárvore a direita de node_lst (filho esquerdo de root)

    node_lst->rst = root;                // a direita de node_lst agora aponta para root
    root->lst = node_lst_rst;            // a esquerda de root agora aponta para node_lst_rst (subárvore a direita do filho a esquerda de root)

    return node_lst;                     // node_lst se torna a nova raiz do subárvore
}

/* ROTATES THE TREE TO THE LEFT
 Executes a rotation to the left, to fix the imbalance
 when the right subtree is heavier
 Return
    A pointer (Node*) to the new root
*/
Node* rotate_left(Node* root) {
    Node* node_rst = root->rst;          // node_rst é o filho a direita de root
    Node* node_rst_lst = node_rst->lst;  // node_rst_lst é a subárvore a esquerda de node_rst (filho a direita de root) 

    node_rst->lst = root;                // node_rst agora aponta para root
    root->rst = node_rst_lst;            // a direita de root agora aponta para node_rst_lst (subárvore a esquerda do filho a direita de root)

    return node_rst;                     // node_lst se torna a nova raiz do subárvore
}

/* INSERTS A NEW NODE WHILE BALANCING THE TREE 
 Inserts a new node like a BST, but balancing the tree
 after each insertion to keep it balanced
 Return
    A pointer (Node*) to the new root
*/
Node* tree_insert_balanced(Node* root, Node* new_node, int (compare)(void*, void*)) {
    // Se a arvore estiver vazia, adiciona o novo nó na raiz
    if (tree_empty(root)) return new_node;

    // Insire o novo nó como uma BST normal
    if (compare(new_node->info, root->info)) {
        root->lst = tree_insert_balanced(root->lst, new_node, compare);
    } else {
        root->rst = tree_insert_balanced(root->rst, new_node, compare);
    }

    // Calcula o fator de balanceamento
    // balance_factor > 1: subárvore esquerda muito pesada
    // balance_factor < -1: subárvore direita muito pesada
    int balance_factor = root ? tree_get_height(root->lst) - tree_get_height(root->rst) : 0;

    // Caso Left Left
    if (balance_factor > 1 && compare(new_node->info, root->lst->info))
        return rotate_right(root);

    // Caso Right Right 
    if (balance_factor < -1 && !compare(new_node->info, root->rst->info))
        return rotate_left(root);

    // Caso Left Right 
    if (balance_factor > 1 && !compare(new_node->info, root->lst->info)) {
        root->lst = rotate_left(root->lst);
        return rotate_right(root);
    }

    // Caso Right Left 
    if (balance_factor < -1 && compare(new_node->info, root->rst->info)) {
        root->rst = rotate_right(root->rst);
        return rotate_left(root);
    }

    return root;
}

/* DELETES A NODE WHILE BALANCING THE TREE
Removes a node from an AVL tree using rotations to maintain balance.
Uses the comparison function to locate the correct node.

Cases handled:
    Node with no children (leaf)
    Node with one child
    Node with two children (replaced by in-order successor)

Params  
    root: pointer to the root of the tree
    new_node: pointer to the node containing the value to be removed
    compare: callback function that compares two elements
Return
    A pointer (Node*) to the new root after removal and rebalancing.
*/

Node* tree_delete_balanced(Node* root, Node* new_node, int (compare)(void*, void*)) {
    //verifica se a arvore esta vazia se sim retorna um  nó na raiz
    if (tree_empty(root)) return root;

    // Busca o nó a ser removido
    if (compare(new_node->info, root->info)) {
        root->lst = tree_delete_balanced(root->lst, new_node, compare);
    } else if (compare(root->info, new_node->info)) {
        root->rst = tree_delete_balanced(root->rst, new_node, compare);
    } else {
        // Encontrou o nó a remover
        if (tree_empty(root->lst) || tree_empty(root->rst)) {
            Node* temp = root->lst ? root->lst : root->rst;
            free(root);
            return temp;
        } else {
            // Encontrar o menor da subárvore direita
            Node* temp = root->rst;
            while (temp->lst)
                temp = temp->lst;

            root->info = temp->info;
            root->rst = tree_delete_balanced(root->rst, temp, compare);
        }
    }

    // Balanceamento
    int balance = tree_get_height(root->lst) - tree_get_height(root->rst);

    // Caso Left Left
    if (balance > 1 && 
        (tree_get_height(root->lst->lst) >= tree_get_height(root->lst->rst)))
        return rotate_right(root);

    // Caso Left Right
    if (balance > 1 && (tree_get_height(root->lst->lst) < tree_get_height(root->lst->rst))) {
        root->lst = rotate_left(root->lst);
        return rotate_right(root);
    }

    // Caso Right Right
    if (balance < -1 && (tree_get_height(root->rst->rst) >= tree_get_height(root->rst->lst)))
        return rotate_left(root);

    // Caso Right Left
    if (balance < -1 && (tree_get_height(root->rst->rst) < tree_get_height(root->rst->lst))) {
        root->rst = rotate_right(root->rst);
        return rotate_left(root);
    }

    return root;
}