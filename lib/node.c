#include "node.h"
#include <stdlib.h>
#include <stdio.h>

node* new_node(TYPE_T _val, char* _label) {
    node* aux = malloc(sizeof(node));
    aux->val = _val;
    aux->label = _label;
    aux->adj = NULL;
    return aux;
}
int check_type (TYPE_T var){
	switch(sizeof(var)){
		case sizeof(int):
			return 1;
		case sizeof(char):
			return 0;
		default:
			return -1;
	}
}
listnode* get_adj(node* node_ptr) {
    return node_ptr->adj;
}

void print_node_adj(node* n) {
    if (n == NULL || n->adj == NULL) {
        printf("Empty neighborhood.\n");
        return;
    }

    listnode* current = n->adj;
    while (current != NULL) {
    	int type = check_type(current->actual->val);
    	if (type == 1)
        	printf("(%d, %s) ", current->actual->val, current->actual->label);
        if (type == 0)
        	printf("(%c, %s) ", current->actual->val, current->actual->label);
        else{
        	printf("Invalid node value type.\n");
        	return;
        }
        current = current->next;
    }
    printf("\n");
}