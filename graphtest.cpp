#include "libcpp/graph.hpp"

int main (void) {
    Graph<int>* G = new Graph<int>(true,true);
    Node<int>* nodeA = G->add_node(0,"A");

    return 0;
}
