#ifndef NODE_H
#define NODE_H
#include <stdlib.h>
#include <stdio.h>

#define nullptr NULL
typedef struct listnode_t{
	struct node* actual;
	struct listnode_t* next;
}listnode;

typedef struct node
{
	int val;
	char* label;
	listnode* adj;
}node;


node* new_node (int,char*);

listnode* get_adj (node*);

void print_adj (node*);

char* get_label (node*);

int get_value (node*);

int insert_neighbour(node*,node*);

int remove_neighbour_by_value(node*,int);

int remove_neighbour_by_label(node*,char*);

node* get_neighbour_by_value (node*,int);

node* get_neighbour_by_label (node*,char*);

int change_index (node*,int);

int change_label (node*,char*);

int free_adj (node*);

#endif