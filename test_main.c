#include "node.h"

int main (int narg,char* argc[]){
	node* a = new_node(0,"A");
	node* b = new_node(1,"B");
	node* c = new_node(2,"C");
	node* d = new_node(3,"D");
	node* e = new_node(4,"E");
	insert_neighbour(a,b);
	printf("Inserted a\n");
	insert_neighbour(a,c);
	printf("Inserted c\n");
	insert_neighbour(a,d);
	printf("Inserted d\n");
	printf("A neighbourhood\n");
	print_node_adj(a);
	insert_neighbour(e,c);
	insert_neighbour(e,a);
	printf("E neighbourhood\n");
	print_node_adj(e);
	return 0;
}
