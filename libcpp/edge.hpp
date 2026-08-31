#ifndef EDGE_HPP
#define EDGE_HPP

template <typename T>
class Node;

template <typename T>
struct Edge {
    Node<T>* source;
    Node<T>* target;
    float weight;
    Edge(Node<T>* s, Node<T>* t, float w) : source(s), target(t), weight(w) {}
};

#endif
