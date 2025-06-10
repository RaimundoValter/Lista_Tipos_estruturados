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
    Creates a node with an info and left and right sub-tree.
    Return
        pointer to a new node (Node*).
*/
Node* tree_create_node(void* info, Node* lst, Node* rst){
    // Allocates memory for the new node
    Node* new_node = (Node*) malloc (sizeof(Node));

    // Sets the node fields (info, lst and rst)
    new_node->info = info;
    new_node->lst = lst;
    new_node->rst = rst;
 
    // Returns the created node
    return new_node;
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
*/
void tree_map(Node* root, void (operation)(void*));

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

/* LOAD A BINARY TREE FROM A TEXT FILE 
    Reads a text file line by line, converts each line into data (using read_line),
    creates a node for each data item, and inserts it into the tree in order using the compare function.

    Parameters
        file_name: name of the file to read
        read_line: function that converts a line (char*) into generic data (void*)
        compare: function used to order nodes upon insertion
    Return
        A pointer to the root of the constructed tree (Node*)
*/
Node* tree_load_from_file(char* file_name, void* (read_line)(char*), int (compare)(void*, void*)){
    // Open the file in text mode for reading
    FILE* fp = fopen(file_name, "rt");

    // Check if the file was opened successfully
    if(!fp){
        printf("Error: file %s could not be opened.\n", file_name);
        exit(1);
    }

    // Buffer to temporarily store each line read from the file
    char recovered_line[121];

    // Create an empty tree
    Node* root = tree_create_empty();

    // Read the file line by line
    while(fgets(recovered_line, 121, fp) != NULL){
        // Remove the newline character if present
        recovered_line[strcspn(recovered_line, "\n")] = '\0';

        // Create a new node with the processed data and insert it into the tree
        Node* new_node = tree_create_node(read_line(recovered_line), NULL, NULL);
        root = tree_insert_node(root, new_node, compare);
    }

    // Close the file
    fclose(fp);

    // Return the root of the constructed tree
    return root;
}