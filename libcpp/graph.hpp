#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include "edge.hpp"
#include "node.hpp"

template<typename T>
class Graph {
private:
    bool isDirected;
    bool isWeighted;
    std::vector<std::unique_ptr<Node<T>>> nodes;
    std::vector<std::unique_ptr<Edge<T>>> edges;
public:
    Graph (bool directed = false ,bool weighted = true): isDirected(directed), isWeighted(weighted)
    {}
    Node<T>* get_node_by_value (T val) {
        for (const auto& iter : nodes) {
            if (iter != NULL && iter->get_value() == val){
                return iter.get();
            }
        }
        return nullptr;
    }
    Node<T>* add_node (T val, const std::string data) {
        Node<T>* aux = get_node_by_value(val);
        if (aux==nullptr){
            auto new_node = std::make_unique<Node<T>>(val, data);
            Node<T>* ptr = new_node.get();
            nodes.push_back(std::move(new_node));
            return ptr;
        }
        else{
            std::cout << "Node already created.\n";
            return nullptr;
        }
    }
    void add_directed_edge (Node<T>* source_node, Node<T>* target_node, float weight = 0) {
        auto new_edge = std::make_unique<Edge<T>>(source_node,target_node,weight);
        source_node->insert_edge(new_edge.get());
        edges.push_back(std::move(new_edge));
    }
    void add_undirected_edge (Node<T>* source_node, Node<T>* target_node, float weight = 0) {
        auto new_edge1 = std::make_unique<Edge<T>>(source_node,target_node,weight);
        auto new_edge2 = std::make_unique<Edge<T>>(target_node,source_node,weight);
        source_node->insert_edge(new_edge1.get());
        target_node->insert_edge(new_edge2.get());
        edges.push_back(std::move(new_edge1));
        edges.push_back(std::move(new_edge2));
    }
    void add_edge (Node<T>* source_node, Node<T>* target_node, float weight) {
        if (isDirected){
            add_directed_edge(source_node,target_node,weight);
        }
        else {
            add_undirected_edge(source_node,target_node,weight);
        }
    }
    void print_neighbourhood (Node<T>* node){
        node->print_node_adj();
    }
    void print_all_neighbourhood(){
        for (const auto& ptr : nodes) {
            ptr.get()->print_node_adj();
        }
    }
};
