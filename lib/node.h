#include <stdlib.h>
#include <stdio.h>
#define nullptr NULL

typedef struct listnode_t{
	struct node* actual;
	struct listnode* next;
}listnode;

typedef struct node_t
{
	int val;
	char* label;
	struct listnode* adj;
}node;

node* new_node (int,char*);

listnode* get_adj (node*);

void print_adj (listnode*);

char* get_label (node*);

int insert_neighbour(node*,node*);

int remove_neighbour_by_value(node*,int);

int remove_neighbour_by_label(node*,char*);

node* get_neighbour_by_value (node*,int);

node* get_neighbour_by_label (node*,char*);

int change_index (node*,int);

int change_label (node*,char*);

int free_adj (node*);