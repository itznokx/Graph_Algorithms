#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node* new_node(TYPE_VAL _val, char* _data) {
    node* aux = malloc(sizeof(node));
    aux->val = (TYPE_VAL)_val;
	size_t size_new_data = strlen(_data) * 2;
	aux->data = malloc(size_new_data * sizeof(char));
    aux->data = strcpy(aux->data,_data);
    aux->adj = NULL;
    return aux;
}

node* create_node(TYPE_VAL _val, char* _data) {
    return new_node(_val,_data);
}

listnode* get_adj(node* node_ptr) {
    return node_ptr->adj;
}

char* get_data (node* n){
	return n->data;
}

listnode* get_neighbourhood (node* n) {
	return n->adj;
}

TYPE_VAL get_value (node* n){
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
// return first only
node* get_neighbour_by_data (node* n,char* str){
	if (n->adj == NULL) 
		return NULL;
	listnode* current = n->adj;
	while (current != NULL){
		if (current->actual != NULL 		&&
			current->actual->data != NULL 	&&
			strcmp(current->actual->data,str)==0){
				return current->actual;
			}
		current = current->next;
	}
	return NULL;
}

int insert_neighbour (node* n,node* k){
	if (get_neighbour_by_value(n,k->val) == NULL){
		listnode* current = malloc(sizeof(listnode));
		current->actual = k;
		current->next = n->adj;
		n->adj = current;
		printf("Inserted node (%s) in neighbourhood of (%s)\n",k->data,n->data);
		return 0;
	}
	printf("Fail to insert node.\n");
	return 1;
}

int remove_neighbour_by_value (node* n,TYPE_VAL k){
	if (n==NULL || n->adj  == NULL)
		return 1;
	listnode* current = n->adj;
	listnode* prev = nullptr;
	while (current != NULL){
		if (current->actual != NULL && current->actual->val == k){
			if (prev == NULL) {
				n->adj = n->adj->next;
			}
			else {
				prev->next = current->next;
			}
			free (current);
			return 0;
		}
		prev = current;
		current = current->next;
	}
	return 1;
}

int remove_neighbour_by_data (node* n,char* l){
	if (l == NULL)
		return 1;
	if (n->adj  == NULL)
		return 1;
	listnode* current = n->adj;
	listnode* prev = NULL;
	while (current != NULL){
		if (current->actual != NULL
			&& current->actual->data != NULL 
			&& (strcmp(current->actual->data,l)==0)){
			
			if (prev==NULL) {
				n->adj = n->adj->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);
			return 0;
		}
		prev = current;
		current = current->next;
	}	
	return 1;
}
void change_index (node* n,TYPE_VAL v){
	n->val = v;
}

void change_data (node* n,char* l){
	free(n->data);
	size_t size_new_data = strlen(l)+1;
	n->data = malloc(size_new_data * sizeof(char));
	n->data = strcpy(n->data,l);
}

int free_adj (node* n){
	if (n->adj == NULL)
	return 1;
	while (n->adj != NULL){
		listnode* current = n->adj;
		n->adj = current->next;
		free(current);
	}

	return 0;
}

void print_node_data (node* n){
	printf("data:%s\n",n->data);
}

void print_node_value (node* n){
	if (n == NULL) {
		printf("Node value is NULL.\n");
		return;
	}
	_Generic (
		(n->val),
		int:  printf("Node: (%d, %s)\n", n->val, n->data),
        char: printf("Node: (%c, %s)\n", n->val, n->data),
        default: printf("Invalid node value type.\n")
	);
}

void print_node_adj(node* n) {
	if (n == NULL || n->adj == NULL) {
		printf("Empty neighborhood.\n");
		return;
	}

	listnode* current = n->adj;
   	_Generic (
		(n->val),
		int:  printf("Node %d neighbourhood:\n", n->val),
        char: printf("Node %c neighbourhood:\n", n->val)
	);
	while (current != NULL) {
		print_node_value(current->actual);
    	current = current->next;
    }
    printf("\n");
}