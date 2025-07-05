#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"

#define TYPE_W float;

typedef struct edge_t {
	node* from;
	node* to;
	TYPE_W weight;
}edge;

typedef struct edge_list {
	edge* edge;
	struct edge_list next;
}listedge;

typedef struct graph{
	char type; // d - directed / u - undirected
	listnode* vertex_list;
	listedge* edge_list;
}graph;

#endif
