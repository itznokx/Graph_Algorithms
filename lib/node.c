#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
node* new_node(TYPE_VAL _val, char* _label) {
    node* aux = malloc(sizeof(node));
    aux->val = _val;
    aux->label = _label;
    aux->adj = NULL;
    return aux;
}
int check_type (TYPE_VAL var){
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

char* get_label (node* n){
	return n->label;
}

TYPE_VAL get_val (node* n){
	return n->val;
}
void print_node_label (node* n){
	printf("Label:%s\n",n->label);
}

void print_node_value (node* n){
	int type = check_type (n->val);
	if (type == 1)
    	printf("Value: %d\n",n->val);
    if (type == 0)
    	printf("Value: %c\n",n->val);
    else{
    	printf("Invalid node value type.\n");
    }
	return;
}

node* get_neighbour_by_value (node* n,TYPE_VAL val){
	if (n == NULL || n->adj == NULL)
		return NULL;
	listnode* current = n->adj;
	while (current != NULL){
		if (current->actual->val == val)
			return current->actual;
	}
	return NULL;
}
int insert_neighbour (node* n,node* k){
	if (get_neighbour_by_value(n,k->val) == NULL){
		if (n->adj == NULL){
			listnode* aux = malloc(sizeof(listnode));
			aux->actual = k;
			aux->next = NULL;

		}
		else{
			listnode* current = n->adj;
			while (current->next != NULL){
				current = current->next;
			}
			current->next->actual = k;
			current->next->next = NULL;
		}
		return 0;
	}
	return 1;
}
int remove_neighbour_by_value (node* n,TYPE_VAL k){
	if (n->adj  == NULL)
		return 0;
	if (n->adj->next == NULL){
		if (n->adj->actual->val == k){
			free(n->adj);
			n->adj = NULL;
			return 0;
		}
		return 1;
	}
	else{
		listnode* current = n->adj;
		while (current->next != NULL){
			if (current->next->actual->val == k){
				listnode* aux = current->next;
				current->next = current->next->next;
				free(aux);
				return 0;
			}
			current = current->next;
		}
		return 1;
	}
	return 1;
}
int remove_neighbour_by_label (node* n,char* l){
	if (n->adj  == NULL)
			return 0;
	if (n->adj->next == NULL){
		if (n->adj->actual->label == l){
			free(n->adj);
			n->adj = NULL;
			return 0;
		}
		return 1;
	}
	else {
		listnode* current = n->adj;
		while (current->next !=null){
			if ( strcmp (current->next->actual->label,l ){
				listnode* aux = current->next;
				current->next = current->next->next;
				free(aux);
				return 0
			}
		}
	}
	return 1;
}
void change_index (node* n,TYPE_VAL v){
	
}
