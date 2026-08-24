#ifndef NODE_H
#define NODE_H
#define nullptr NULL
#define TYPE_VAL int // char or int type

enum NODE_STATE {
	UNDISCOVERED,
	IN_PROCESSING,
	FINISHED
};

typedef struct listnode_t{
	struct node* actual;
	struct listnode_t* next;
}listnode;

typedef struct node
{
	TYPE_VAL val;
	char* data;
	listnode* adj;
	enum NODE_STATE state;
	
}node;


node* new_node (TYPE_VAL,char*); //done

listnode* get_adj (node*); //done

void print_node_adj (node*); //done

char* get_data (node*); //done

TYPE_VAL get_value (node*); // done

void print_node_data (node*); // done

void print_node_value (node*); // done

node* get_neighbour_by_value (node*,TYPE_VAL); // done

node* get_neighbour_by_data (node*,char*); // done

int insert_neighbour(node*,node*); // done

int remove_neighbour_by_value(node*,TYPE_VAL); // done

int remove_neighbour_by_data(node*,char*); // done

void change_index (node*,TYPE_VAL); // done

void change_data (node*,char*); // done

int free_adj (node*); // done

#endif
