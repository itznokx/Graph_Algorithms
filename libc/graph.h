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


int insert_vertex (graph* g,node* n);

int remove_vertex_by_value (graph* g, TYPE_VAL v);

int remove_vertex_by_label (graph* g, char* l);

int insert_edge (graph* g, node* a, node* b);

int remove_edge (graph* g, node* a, node* b);

int remove_edge_by_value (graph* g, node* a, TYPE_VAL v);

int remove_edge_by_label (graph* g, node* a, char* l);

int remove_edge_value_to_value (graph* g, TYPE_VAL a, TYPE_VAL b);

void print_vertexes (graph* g);

void print_edges (graph* g);

void print_vertex_adj (graph* g, TYPE_VAL v);

void free_vertex_list (graph* g);

void free_edge_lest (graph* g);

#endif
