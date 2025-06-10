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

/* TREE SEARCH
   Search the first element that satisfies the condition inside the tree.

    Return:
    A pointer (Node*) to the first node that satisfies the condition.

    Parameters:
    Node* root - receives the root of the tree.
    int (condition)(void) - a callback that receives the node info
    and returns a non-zero value if the condition is satisfied.
*/
Node* tree_search(Node* root, int (condition)(void*)){
    // If tree is empty, return NULL
    if (tree_empty(root))
    {
        return NULL;
    }
    // If current node satisfies the condition, return it
    if(condition(root->info))
    {
        return root;
    }
    //Result to save result of the search
    Node * result;

    // Search in the left subtree
    result = tree_search(root->lst,condition);
    //If you found the result, ok
    if(result != NULL)
    {
        return result;
    }
    // If you haven't found it yet, try the right side
    result = tree_search(root->rst,condition);
    return result;
}

/* TREE TO FILE
   Save all elements from the tree to a text file using in-order traversal.

    Return: 
    (void) - does not return anything.

    Parameters:
    Node* root - receives the root of the tree.
    char* file_name - receives the name of the file to be created.
    char* (create_line)(void) - function that receives a node’s info,
    returns a formatted string to be saved in the file.
    This function must return a dynamically allocated string,
    which will be freed after being written.
*/

// Recursive function to write the tree to the file in-order
void write_inorder(Node *new_node, FILE *fp, char* (*create_line)(void*))
{
    if (new_node == NULL)
    return;

    write_inorder(new_node->lst,fp,create_line); //Visit left subtree
    char * line = create_line(new_node->info); 
    if (line != NULL)
    {
        fprintf(fp,"%s",line); // Write the line to the file
        free(line); // Free the memory allocated by create_line
    }
    write_inorder(new_node->rst,fp,create_line); //Visit right subtree
}
void tree_to_file(Node* root, char* file_name, char* (create_line)(void*)){
    FILE * fp = fopen(file_name,"wt"); //create an anchive
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // Start writing from the root
    write_inorder(root,fp,create_line);

    // Close the file
    fclose(fp);
    
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