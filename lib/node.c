#include "node.h"

node* new_node (int _val,char* _label){
	node* aux = malloc(sizeof(node));
	aux->val = _val;
	aux->label = _label;
	aux-> adj = nullptr;
	return aux;
}

listnode* get_adj (node* node_ptr){
	return (listnode*)node_ptr->adj;
}

void print_adj (listnode* list_adj){
	return;
}