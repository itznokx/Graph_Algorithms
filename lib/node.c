#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
node* new_node(TYPE_VAL _val, char* _data) {
    node* aux = malloc(sizeof(node));
    aux->val = (TYPE_VAL)_val;
    aux->data = _data;
    aux->adj = NULL;
    return aux;
}
listnode* get_adj(node* node_ptr) {
    return node_ptr->adj;
}

void print_node_adj(node* n) {
	if (n == NULL || n->adj == NULL) {
        printf("Empty neighborhood.\n");
        return;
   }
	listnode* current = malloc(sizeof(listnode));
   current = n->adj;
   while (current != NULL) {
   	size_t type = sizeof(current->actual->val); 
		switch(type){
			case sizeof(int):
        		printf("Node: (%d, %s)\n", current->actual->val, current->actual->data);
				break;
			case sizeof(char):
        		printf("Node: (%c, %s)\n", current->actual->val, current->actual->data);
				break;
			default:
       		printf("Invalid node value type.\n");
        		return;
      }
      current = current->next;
    }
    printf("\n");
}

char* get_data (node* n){
	return n->data;
}

TYPE_VAL get_val (node* n){
	return n->val;
}

node* get_neighbour_by_value (node* n,TYPE_VAL val){
	if (n == NULL || n->adj == NULL)
	return NULL;
	listnode* current = n->adj;
	while (current != NULL){
		if (current->actual->val == val)
		return current->actual;
		current = current->next;
	}
	return NULL;
}
int insert_neighbour (node* n,node* k){
	if (get_neighbour_by_value(n,k->val) == NULL){
		if (n->adj == NULL){
			listnode* aux = malloc(sizeof(listnode));
			aux->actual = k;
			aux->next = NULL;
			n->adj = aux;
		}
		else{
			listnode* current = malloc(sizeof(listnode));
			current = n->adj;
			while (current->next != NULL){
				current = current->next;
			}
			current->next  = malloc(sizeof(listnode));
			current->next->actual = malloc(sizeof(node));
			current->next->actual = k;
			current->next->next = NULL;
		}
		printf("Inserted node (%s) in neighbourhood of (%s)\n",k->data,n->data);
		return 0;
	}
	printf("Fail to insert node.\n");
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
int remove_neighbour_by_data (node* n,char* l){
	if (n->adj  == NULL)
	return 0;
	if (n->adj->next == NULL){
		if (strcmp(n->adj->actual->data,l)){
			free(n->adj);
			n->adj = NULL;
			return 0;
		}
		return 1;
	}
	else {
		listnode* current = n->adj;
		while (current->next != NULL){
			if (strcmp(current->next->actual->data,l)){
				listnode* aux = current->next;
				current->next = current->next->next;
				free(aux);
				return 0;
			}
		}
	}
	return 1;
}
void change_index (node* n,TYPE_VAL v){
	n->val = v;
}
void change_data (node* n,char* l){
	n->data = NULL;
	size_t size_new_data = strlen(l);
	n->data = malloc(size_new_data * sizeof(char));
	n->data = strcpy(n->data,l);
}
int free_adj (node* n){
	if (n->adj == NULL)
	return 1;
	while (n->adj != NULL){
		listnode* current = malloc(sizeof(listnode)); 
		current = n->adj;
		while (current->next != NULL){
			current = current->next;
		}
		free(current);
	}
	return 0;
}
void print_node_data (node* n){
	printf("data:%s\n",n->data);
}

void print_node_value (node* n){
	size_t type = sizeof(n->val); 
	printf("size_t = %i\n",type);
	switch(type){
		case sizeof(int):
			printf("Node: (%d, %s)\n", n->val,n->data);
			break;
		case sizeof(char):
			printf("Node: (%c, %s)\n", n->val,n->data);
			break;
		default:
			printf("Invalid node value type.\n");
			return;
	}

}