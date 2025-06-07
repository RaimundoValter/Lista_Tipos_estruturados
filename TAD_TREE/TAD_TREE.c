#include "TAD_TREE.h"

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
int tree_insert_node(Node* root, Node* new_node, int (compare)(void*, void*)){

}
/* FREE A TREE
    free memory of all elements in a tree/subtree starting from the "root" node.
*/
void tree_free(Node* root);

/* PERFORM OPERATION IN A TREE 
perform an operation in all elements of a tree. 
Node* root = receives the head of the tree 
void (operation)(void*) = callback operation that will be applied to the intere tree */ 
void tree_map(Node* root, void (operation)(void*)){
    if (empty_tree(root)) return; //checks if the tree is empty, if it is, returns null
  tree_map(root->lst,operation);//do the operation only on the left side of the root 
  operation(root->info);//apply to the current node 
  tree_map(root->rst,operation);//do all the same but on the right side }
}

/* FILTER ELEMENTS IN THE TREE
 Gather togeter a set of elements that satisfy condition inside the tree.
 Return
    Pointer to the head of a list composed by the elements
    that satisfy the condition.
*/
Node* tree_filter(Node* root, int (condition)(void*));

/* SEARH AN ELEMENT IN THE TREE
 Search the first element that satisfy condition inside the tree.
 Return
    A pointer (Node*) to the first node that satisfied the conditino.
*/
Node* tree_search(Node* root, int (condition)(void*)){


}