#ifndef NODE_HPP
#define NODE_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "edge.hpp"
enum class NodeState {
    UNDISCOVERED,
    IN_PROCESSING,
    FINISHED
};
template <typename T>
class Node {
private:
    T val;
    std::string data;
    std::vector<Edge<T>*> adj;
    NodeState state;
    Node* parent;
public:
    Node(T _val, const std::string& _data)
        : val(_val), data(_data), state(NodeState::UNDISCOVERED), parent(nullptr) {}
    ~Node(){
        delete(adj);
        delete(parent);
    };

    const std::vector<Node<T>*>& get_adj() const { return adj; }
    std::string get_data() const { return data; }
    T get_value() const { return val; }
    NodeState get_state() const { return state; }
    void set_state(NodeState s) { state = s; }
    void change_index(T v) { val = v; }
    void change_data(const std::string& l) { data = l; }
    Node<T>* get_parent() { return parent;}
    void set_parent(Node<T>* _parent) {this-> parent;}
    bool compare_to_node_value (Node* _n){
        if ( _n != NULL &&
            _n->val != NULL &&
            this->val != _n->val
            ) {
            return false;
        }
        return true;
    }
    bool compare_to_node_data (Node* _n){
        if ( _n != NULL &&
            _n->data != "" &&
            this->data !=_n->data
            ) {
            return false;
        }
        return true;
    }
    Node<T>* get_neighbour_by_value(T target_val) const {
        for (Edge<T>* neighbor : adj) {
            if (neighbor->target->get_value() == target_val) return neighbor->target;
        }
        return nullptr;
    }
    Node<T>* get_neighbour_by_data(const std::string& str) const {
        for (Edge<T>* neighbor : adj) {
            if (neighbor->target->get_data() == str) return neighbor->target;
        }
        return nullptr;
    }

    bool insert_neighbour(Node<T>* k,float weight = 0) {
        if (!k) return false;
        if (get_neighbour_by_value(k->val) == nullptr) {
            Edge<T>* aux = new Edge<int>(this,k,weight);
            adj.push_back(aux);
            std::cout<< "Inserted node ("
                     << k->data
                     << ", w:"
                     << weight
                     << ") in neighbourhood of ("
                     << data
                     << ")\n";
            return true;
        }
        std::cout << "Fail to insert node.\n";
        return false;
    }

    bool remove_neighbour_by_value(T k) {
        auto iterator = std::find_if(adj.begin(),
                            adj.end(),
                            [k](Edge<T>* e) { return (e->target->get_value() == k); }
                            );
        if (iterator != adj.end()) {
            adj.erase(iterator);
            return true;
        }
        return false;
    }

    bool remove_neighbour_by_data(const std::string& l) {
        auto iterator = std::find_if( adj.begin(),
                                adj.end(),
                                [&l](Edge<T>* e) { return (e->target->get_data() == l); }
                                );
        if (iterator != adj.end()) {
            adj.erase(iterator);
            return true;
        }
        return false;
    }

    void free_adj() {
        adj.clear();
    }
    void print_node_data() const {
        std::cout   << "data:"
                    << this->get_data()
                    << '\n';
    }

    void print_node_value() const {
        std::cout   << "Node: ("
                    << this->get_value()
                    << ", "
                    << this->get_data()
                    << ")\n";
    }

    void print_node_adj() const {
        if (adj.empty()) {
            std::cout << "Empty neighborhood.\n";
            return;
        }

        std::cout << "Node " << this->val << " neighbourhood:\n";
        for (const auto& neighbor : adj) {
            neighbor->target->print_node_value();
        }
        std::cout << '\n';
    }
    Node<T>* clone () {
        Node<T>* aux = new Node<T>(this->val,this->data);
        aux->state = this->state;
        aux->adj = this->adj;
        return aux;
    }
};
#endif
