#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stdio.h>

#define nullptr NULL

#define TYPE_VAL int // char or int type

typedef struct listnode_t{
	struct node* actual;
	struct listnode_t* next;
}listnode;

typedef struct node
{
	TYPE_VAL val;
	char* label;
	listnode* adj;
}node;


node* new_node (TYPE_VAL,char*); //done

int check_type (TYPE_VAL var); //done

listnode* get_adj (node*); //done

void print_adj (node*); //done

char* get_label (node*); //done

TYPE_VAL get_value (node*); // done

void print_node_label (node*); //done

void print_node_value (node*); //done

node* get_neighbour_by_value (node*,TYPE_VAL);

node* get_neighbour_by_label (node*,char*);

int insert_neighbour(node*,node*);

int remove_neighbour_by_value(node*,TYPE_VAL);

int remove_neighbour_by_label(node*,char*);

int change_index (node*,TYPE_VAL);

int change_label (node*,char*);

int free_adj (node*);

#endif
