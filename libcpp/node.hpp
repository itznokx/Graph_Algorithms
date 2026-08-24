#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    std::vector<Node<T>*> adj;
    NodeState state;

public:
    Node(T _val, const std::string& _data)
        : val(_val), data(_data), state(NodeState::UNDISCOVERED) {}
    ~Node() = default;

    const std::vector<Node<T>*>& get_adj() const { return adj; }
    std::string get_data() const { return data; }
    T get_value() const { return val; }
    NodeState get_state() const { return state; }
    void set_state(NodeState s) { state = s; }
    void change_index(T v) { val = v; }
    void change_data(const std::string& l) { data = l; }
    Node<T>* get_neighbour_by_value(T target_val) const {
        for (Node<T>* neighbor : adj) {
            if (neighbor->val == target_val) return neighbor;
        }
        return nullptr;
    }
    Node<T>* get_neighbour_by_data(const std::string& str) const {
        for (Node<T>* neighbor : adj) {
            if (neighbor->data == str) return neighbor;
        }
        return nullptr;
    }

    bool insert_neighbour(Node<T>* k) {
        if (!k) return false;

        if (get_neighbour_by_value(k->val) == nullptr) {
            adj.push_back(k);
            std::cout << "Inserted node (" << k->data << ") in neighbourhood of (" << data << ")\n";
            return true;
        }
        std::cout << "Fail to insert node.\n";
        return false;
    }

    bool remove_neighbour_by_value(T k) {
        auto iterator = std::find_if(adj.begin(),
                            adj.end(),
                            [k](Node<T>* n) { return n->val == k; }
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
                                [&l](Node<T>* n) { return n->data == l; }
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
        std::cout << "data:" << data << '\n';
    }

    void print_node_value() const {
        std::cout << "Node: (" << val << ", " << data << ")\n";
    }

    void print_node_adj() const {
        if (adj.empty()) {
            std::cout << "Empty neighborhood.\n";
            return;
        }

        std::cout << "Node " << val << " neighbourhood:\n";
        for (Node<T>* neighbor : adj) {
            neighbor->print_node_value();
        }
        std::cout << '\n';
    }
};
#endif
