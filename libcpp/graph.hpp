#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <queue>
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
    std::vector<Node<T>*>topological_order;
    std::vector<T>DFS_auxiliar;
    int time;
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
    Node<T>* add_node (T val, const std::string data,float _x = 0.0f, float _y = 0.0f) {
        Node<T>* aux = get_node_by_value(val);
        if (aux==nullptr){
            auto new_node = std::make_unique<Node<T>>(val, data,_x,_y);
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
    int get_nodes_size() {
        return nodes.size();
    }
    int get_edges_size() {
        return edges.size();
    }
    std::vector<std::unique_ptr<Node<T>>> get_nodes () {
        return this->nodes;
    }
    std::vector<std::unique_ptr<Edge<T>>> get_edges () {
        return this->edges;
    }
    void BFS (Node<T>* start,bool verbose = false) {
        for (const auto& node : nodes) {
            //if (verbose) std::cout << "Started: " << node->get_value() << "\n";
            node->set_state(NodeState::UNDISCOVERED);
        }
        std::queue<Node<T>*> nodeQueue;
        start->set_state(NodeState::IN_PROCESSING);
        nodeQueue.push(start);
        while (!nodeQueue.empty()){
            Node<T>* actual = nodeQueue.front();
            nodeQueue.pop();
        if (verbose) std::cout << "Discovered: " << actual->get_value() << "\n";
            for (Edge<T>* edge : actual->get_full_neighbour()){
                if (edge->target->get_state() == NodeState::UNDISCOVERED) {
                    nodeQueue.push(edge->target);
                    edge->target->set_state(NodeState::IN_PROCESSING);
                    if (edge->target->get_parent() == nullptr) {edge->target->set_parent(actual);}
                }
            }
            actual->set_state(NodeState::FINISHED);
        }
    }
    void DFS (Node<T>* start,bool verbose = false) {
        this->time = 0;
        DFS_auxiliar.clear();
        for (const auto& node : nodes) {
            node->set_state(NodeState::UNDISCOVERED);
            node->set_init_time(0);
            node->set_finish_time(0);
            if (node.get() != start)
                DFS_auxiliar.push_back(node->get_value());
        }
        DFS_auxiliar.push_back(start->get_value());
        while (!DFS_auxiliar.empty()) {
            T next_val = DFS_auxiliar.back();
            DFS_auxiliar.pop_back();
            Do_DFS(get_node_by_value(next_val), verbose);
        }

    }
    void Do_DFS (Node<T>* actual,bool verbose = false) {
        if (actual == nullptr) return;
        this->time = this->time + 1;
        actual->set_state(NodeState::IN_PROCESSING);
        if (verbose) std::cout << "Discovered: " << actual->get_value() << " in time " << this->time << "\n";
        for (int i = 0; i < DFS_auxiliar.size();i++){
            if (DFS_auxiliar.at(i) == actual->get_value()){
                DFS_auxiliar.erase(DFS_auxiliar.begin()+i);
            }
        }
        actual->set_init_time(this->time);
        for (Edge<T>* edge : actual->get_full_neighbour()){
            if (edge->target->get_state() == NodeState::UNDISCOVERED) {
                if (edge->target->get_parent() == nullptr) {edge->target->set_parent(actual);}
                Do_DFS(edge->target,verbose);
            }
        }
        this->time = this->time + 1;
        actual->set_finish_time(this->time);
        if (verbose) std::cout << "Finished: " << actual->get_value() << " in time " << this->time << "\n";
    }
    Node<T>* get_node_with_max_finish_time (std::vector<Node<T>*> ignore_vector) {
        Node<T>* max = nullptr;
        for (const auto& node : this->nodes) {
            Node<T>* aux = node.get();
            auto iterator = std::find_if(
                ignore_vector.begin(),
                ignore_vector.end(),
                [aux](Node<T>* comparator) { return comparator->get_value() == aux->get_value(); }
            );
            if (iterator == ignore_vector.end()) {
                if (max == nullptr){max = aux;}
                else {
                    if (max->get_finish_time() < aux->get_finish_time())max = aux;
                }
            }
        }
        return max;
    }
    std::vector<Node<T>*> get_topological_order (bool verbose = false) {
        if (topological_order.empty()) {this->DFS(nodes.at(0).get());}
        for (int i=0;i<nodes.size();i++) {
            Node<T>* aux = this->get_node_with_max_finish_time(topological_order);
            if (verbose) std::cout << "Iter: " << i << " ,max finish time: " << aux->get_finish_time() << "\n";
            topological_order.push_back(aux);
        }
        return topological_order;
    }
    void print_topological_order() {
        if (topological_order.empty())get_topological_order(true);
        std::cout << "Topological order: (Node)(FinishTime) " << nodes.size() <<"\n" ;
        for (const auto& node : this->topological_order) {
            std::cout << " Node(" << node->get_value() << "),(" << node->get_finish_time() << "), ";
        }
    }
};
