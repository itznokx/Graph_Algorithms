#include "libcpp/node.hpp"

int main (int nargs, char** argv){
    Node<int>* nodeA = new Node<int>(0,"A");
    Node<int>* nodeB = new Node<int>(1,"B");
    Node<int>* nodeC = new Node<int>(2,"C");
    Node<int>* nodeD = new Node<int>(3,"D");
    Node<int>* nodeE = new Node<int>(4,"E");
    nodeA->insert_neighbour(nodeB);
    nodeA->insert_neighbour(nodeD);
    nodeA->print_node_adj();
    nodeE->insert_neighbour(nodeC);
    nodeE->insert_neighbour(nodeA);
    nodeE->print_node_adj();
    nodeA->insert_neighbour(nodeE);
    nodeA->remove_neighbour_by_value(0);
    nodeA->remove_neighbour_by_value(1);
    nodeA->print_node_adj();
    return 0;
}
