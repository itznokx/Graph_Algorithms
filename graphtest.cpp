#include "libcpp/graph.hpp"

int main (void) {
    Graph<int>* G = new Graph<int>(true,true);
    Node<int>* nodeA = G->add_node(0,"A");
    Node<int>* nodeB = G->add_node(1,"B");
    Node<int>* nodeC = G->add_node(2,"C");
    Node<int>* nodeD = G->add_node(3,"D");
    G->add_edge(nodeA, nodeB, 0);
    G->add_edge(nodeA, nodeC, 0);
    G->add_edge(nodeA, nodeD, 0);
    G->add_edge(nodeB, nodeD, 0);
    return 0;
}
