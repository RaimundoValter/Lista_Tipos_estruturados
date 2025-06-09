#include "TAD_TREE.c"

typedef struct Pessoa {
  int idade;
  char nome[50];
  char profissao[50];
} Pessoa;

int compare(void* a, void* b) {
  return ((Pessoa*)a)->idade < ((Pessoa*)b)->idade;
}

void print(void* a) { printf("Idade: %d\n", ((Pessoa*)a)->idade); }

int main() {
  Node* root_balanced = tree_create_empty();
  Node* root = tree_create_empty();

  Pessoa pessoas[] = {
      {10, "Yan", "Estudante"},
      {30, "Valter", "Professor"},
      {20, "Joao", "Estudante"},
  };

  for (int i = 0; i < 3; i++) {
    Node* node = tree_create_node(&pessoas[i], NULL, NULL);
    root = tree_insert_node(root, node, compare);
  }

  for (int i = 0; i < 3; i++) {
    Node* node = tree_create_node(&pessoas[i], NULL, NULL);
    root_balanced = tree_insert_balanced(root_balanced, node, compare);
  }

  printf("Arvore desbalanceada:\n\n");
  tree_print(root, print, 0);
  printf("\nArvore balanceada:\n\n");
  tree_print(root_balanced, print, 0);

  return 0;
}