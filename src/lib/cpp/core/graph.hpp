#pragma once

#include "core/ids.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace gv {

struct Edge {
    EdgeId id = kNoEdge;
    NodeId u = kNoNode;
    NodeId v = kNoNode;
    Weight weight = 1.0f;
    bool alive = false;
};

struct Arc {
    EdgeId edge = kNoEdge;
    NodeId to = kNoNode;
};

class Graph {
public:
    explicit Graph(bool directed = false, bool weighted = true);

    NodeId add_node(std::string label = "");
    bool remove_node(NodeId u);
    EdgeId add_edge(NodeId u, NodeId v, Weight w = 1.0f);
    bool remove_edge(EdgeId e);
    bool set_weight(EdgeId e, Weight w);
    void clear();

    bool has_node(NodeId u) const;
    bool has_edge(EdgeId e) const;
    EdgeId find_edge(NodeId u, NodeId v) const;
    const Edge& edge(EdgeId e) const;
    const std::string& label(NodeId u) const;
    const std::vector<Arc>& out_arcs(NodeId u) const;

    std::vector<NodeId> nodes() const;
    std::vector<EdgeId> edges() const;
    std::size_t node_count() const;
    std::size_t edge_count() const;
    std::size_t node_capacity() const;
    std::size_t edge_capacity() const;

    bool directed() const;
    bool weighted() const;
    bool has_negative_weight() const;
    std::uint64_t revision() const;

private:
    struct NodeRecord {
        std::string label;
        bool alive = false;
    };

    static std::string make_auto_label(int index);
    void erase_arc(NodeId u, EdgeId e);

    bool directed_ = false;
    bool weighted_ = true;
    std::vector<NodeRecord> nodes_;
    std::vector<std::vector<Arc>> adj_;
    std::vector<Edge> edges_;
    std::size_t node_count_ = 0;
    std::size_t edge_count_ = 0;
    int auto_label_seq_ = 0;
    std::uint64_t revision_ = 0;
};

}
