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
    bool check_nodes (T val) {
        for (const auto& iter : nodes) {
            if (iter != NULL && iter->get_value() == val){
                return true;
            }
        }
        return false;
    }
    Node<T>* add_node (T val, const std::string data) {
        auto new_node = std::make_unique<Node<T>>(val, data);
        nodes.push_back(std::move(new_node));
        return new_node.get();
    }
    void add_directed_edge (Node<T>* source_node, Node<T>* target_node, float weight = 0) {
        auto new_edge = std::make_unique<Edge<T>>(source_node,target_node,weight);
        source_node->insert_edge(new_edge);
        edges.push_back(std::move(new_edge));
    }
    void add_undirected_edge (Node<T>* source_node, Node<T>* target_node, float weight = 0) {
        auto new_edge1 = std::make_unique<Edge<T>>(source_node,target_node,weight);
        auto new_edge2 = std::make_unique<Edge<T>>(target_node,source_node,weight);
        edges.push_back(std::move(new_edge1));
        edges.push_back(std::move(new_edge2));
        source_node->insert_edge(new_edge1);
        target_node->insert_edge(new_edge2);
    }
    void add_edge (Node<T>* source_node, Node<T>* target_node, float weight) {
        if (isDirected){
            add_directed_edge(source_node,target_node,weight);
        }
        else {
            add_undirected_edge(source_node,target_node,weight);
        }
    }


};
