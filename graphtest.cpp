#include "libcpp/graph.hpp"

int main (void) {
    Graph<int>* G = new Graph<int>(true,true);
    Node<int>* nodeA = G->add_node(0,"A");
    Node<int>* nodeB = G->add_node(0,"B");
    return 0;
}
