#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node* new_node(int _val, char* _label) {
    node* aux = malloc(sizeof(node));
    aux->val = _val;
    aux->label = _label;
    aux->adj = NULL;
    return aux;
}

listnode* get_adj(node* node_ptr) {
    return node_ptr->adj;
}

void print_adj(node* n) {
    if (n == NULL || n->adj == NULL) {
        printf("Empty neighborhood.\n");
        return;
    }

    listnode* current = n->adj;
    while (current != NULL) {
        printf("(%d, %s) ", current->actual->val, current->actual->label);
        current = current->next;
    }
    printf("\n");
}
