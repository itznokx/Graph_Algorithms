#include <iostream>

struct node
{
	int val;
	char* label;
	struct node* adj;
};

struct node* new_node (int,char*);

node* get_adj (node*);

char* get_label (node*);

int insert_neighbour(node*,node*);

int remove_neighbour(node*,int);

int remove_neighbour(node*,char*);

node* get_neighbour (node*,int);

node* get_neighbour (node*,char*);

int change_index (node*,int);

int change_label (node*,char*);

