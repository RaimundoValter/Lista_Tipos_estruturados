#include "TAD_TREE.h"
#include <stdlib.h>

/* IS IT EMPTY?
    Return
        True if the tree is empty, otherwise false.
*/
int tree_empty(Node* root){
    return root == NULL;
}

/* CREATE AN ENPTY TREE
    Return
        (Node*)NULL, representing a empty tree.
*/
Node* tree_create_empty(){
    return (Node*)NULL;
}

/* CREATE A NODE
    Creates a node with an info ans left and right sub-tree.
    Return
        pointer to a new node (Node*).
*/
Node* tree_create_node(void* info, Node* lst, Node* rst){

}

/* INSERT A NODE
    Inserts a node in a tree based on a comparison.
    If it's true, the new_node will be placed in the left sub-tree, 
    if it's false, the new_node will be in the right sub-tree.
    Return
        True if the new_node was placed in the tree,
        otherwise false.
*/
int tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*));

/* FREE A TREE
    free memory of all elements in a tree/subtree starting from the "root" node.
Params
    root: a node of a tree/subtree that you would like to free.
*/
void tree_free(Node* root){
    if(root != NULL){
        tree_free(root->lst);
        tree_free(root->rst);
        free(root->info);
        free(root);
    }
}

/* PERFORM OPERATION IN A TREE
    perform an operation in all elements of a tree.
*/
void tree_map(Node* root, void (operation)(void*));

/* FILTER ELEMENTS IN THE TREE
    Gather togeter a set of elements that satisfy condition inside 
    the tree, creating a tree with those elements.
Params
    root: A node pointer to the root
    operation: A callback [int codition(void*)] that determines if a node 
        pass in the condition to become a node of the resulting tree.
Return
    Pointer to the head of a list composed by the elements
    that satisfy the condition.
*/
Nodelist* tree_filter(Node* root, int (condition)(void*), void* (copy_info)(void*)){
    // Create a empty list in this level.
    Nodelist* list_in_this_level = NULL;
    // Create an aux pointer called "p"
    Nodelist* p = NULL;

    // If there is a node in recursion level.
    if(root != NULL){
        // Check the left subtree for new elements to insert in list_in_this_level.
        Nodelist* lst_list = tree_filter(root->lst, condition, copy_info);
        // Check the right subtree for new elements to insert in list_in_this_level.
        Nodelist* rst_list = tree_filter(root->rst, condition, copy_info);

        if (lst_list){
            list_in_this_level = lst_list;
        }

        // If this level element pass in the condition
        if(condition(root->info)){
            Nodelist* new_element = (Nodelist*)malloc(sizeof(Nodelist));
            new_element->info = copy_info(root->info);
            new_element->next = NULL;

            // Update "p" with the address to the last element in list_in_this_level.
            for(p=list_in_this_level; p->next != NULL; p = p->next);

            // Insert the new element in the list_in_this_level
            p->next = new_element;
            // Update the "p" with the pointer to the last element in list_in_this_level.
            p = p->next;
        }

        // If there is a 
        if (rst_list){
            // Update "p" with the address to the last element in list_in_this_level.
            for(p=list_in_this_level; p->next != NULL; p = p->next);
            p->next = rst_list;
        }
    }

    return list_in_this_level;
}

/* SEARH AN ELEMENT IN THE TREE
    Search the first element that satisfy condition inside the tree.
 Params
    ...
 Return
    A pointer (Node*) to the first node that satisfied the conditino.
*/
Node* tree_search(Node* root, int (condition)(void*)){


}