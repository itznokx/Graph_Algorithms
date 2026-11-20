#include "core/graph.hpp"

#include <algorithm>
#include <stdexcept>

namespace gv {

Graph::Graph(bool directed, bool weighted)
    : directed_(directed), weighted_(weighted) {}

std::string Graph::make_auto_label(int index) {
    std::string out;
    int n = index;
    do {
        out.push_back(static_cast<char>('A' + (n % 26)));
        n = n / 26 - 1;
    } while (n >= 0);
    std::reverse(out.begin(), out.end());
    return out;
}

void Graph::erase_arc(NodeId u, EdgeId e) {
    auto& arcs = adj_[u];
    arcs.erase(
        std::remove_if(arcs.begin(), arcs.end(), [e](const Arc& a) { return a.edge == e; }),
        arcs.end());
}

NodeId Graph::add_node(std::string label) {
    NodeId id = static_cast<NodeId>(nodes_.size());
    if (label.empty()) {
        label = make_auto_label(auto_label_seq_++);
    }
    nodes_.push_back(NodeRecord{std::move(label), true});
    adj_.emplace_back();
    ++node_count_;
    ++revision_;
    return id;
}

bool Graph::remove_node(NodeId u) {
    if (!has_node(u)) {
        return false;
    }
    for (const auto& e : edges_) {
        if (e.alive && (e.u == u || e.v == u)) {
            remove_edge(e.id);
        }
    }
    nodes_[u].alive = false;
    nodes_[u].label.clear();
    adj_[u].clear();
    --node_count_;
    ++revision_;
    return true;
}

EdgeId Graph::add_edge(NodeId u, NodeId v, Weight w) {
    if (!has_node(u) || !has_node(v) || u == v) {
        return kNoEdge;
    }
    if (find_edge(u, v) != kNoEdge) {
        return kNoEdge;
    }
    Weight effective_w = weighted_ ? w : 1.0f;
    EdgeId id = static_cast<EdgeId>(edges_.size());
    edges_.push_back(Edge{id, u, v, effective_w, true});
    adj_[u].push_back(Arc{id, v});
    if (!directed_) {
        adj_[v].push_back(Arc{id, u});
    }
    ++edge_count_;
    ++revision_;
    return id;
}

bool Graph::remove_edge(EdgeId e) {
    if (!has_edge(e)) {
        return false;
    }
    Edge& ed = edges_[e];
    ed.alive = false;
    erase_arc(ed.u, e);
    if (!directed_) {
        erase_arc(ed.v, e);
    }
    --edge_count_;
    ++revision_;
    return true;
}

bool Graph::set_weight(EdgeId e, Weight w) {
    if (!weighted_ || !has_edge(e)) {
        return false;
    }
    edges_[e].weight = w;
    ++revision_;
    return true;
}

void Graph::clear() {
    nodes_.clear();
    adj_.clear();
    edges_.clear();
    node_count_ = 0;
    edge_count_ = 0;
    auto_label_seq_ = 0;
    ++revision_;
}

bool Graph::has_node(NodeId u) const {
    return u >= 0 && static_cast<std::size_t>(u) < nodes_.size() && nodes_[u].alive;
}

bool Graph::has_edge(EdgeId e) const {
    return e >= 0 && static_cast<std::size_t>(e) < edges_.size() && edges_[e].alive;
}

EdgeId Graph::find_edge(NodeId u, NodeId v) const {
    if (!has_node(u) || !has_node(v)) {
        return kNoEdge;
    }
    for (const auto& arc : adj_[u]) {
        if (arc.to == v) {
            return arc.edge;
        }
    }
    return kNoEdge;
}

const Edge& Graph::edge(EdgeId e) const {
    if (!has_edge(e)) {
        throw std::out_of_range("Invalid EdgeId");
    }
    return edges_[e];
}

const std::string& Graph::label(NodeId u) const {
    if (!has_node(u)) {
        throw std::out_of_range("Invalid NodeId");
    }
    return nodes_[u].label;
}

const std::vector<Arc>& Graph::out_arcs(NodeId u) const {
    if (!has_node(u)) {
        throw std::out_of_range("Invalid NodeId");
    }
    return adj_[u];
}

std::vector<NodeId> Graph::nodes() const {
    std::vector<NodeId> result;
    result.reserve(node_count_);
    for (std::size_t i = 0; i < nodes_.size(); ++i) {
        if (nodes_[i].alive) {
            result.push_back(static_cast<NodeId>(i));
        }
    }
    return result;
}

std::vector<EdgeId> Graph::edges() const {
    std::vector<EdgeId> result;
    result.reserve(edge_count_);
    for (std::size_t i = 0; i < edges_.size(); ++i) {
        if (edges_[i].alive) {
            result.push_back(static_cast<EdgeId>(i));
        }
    }
    return result;
}

std::size_t Graph::node_count() const {
    return node_count_;
}

std::size_t Graph::edge_count() const {
    return edge_count_;
}

std::size_t Graph::node_capacity() const {
    return nodes_.size();
}

std::size_t Graph::edge_capacity() const {
    return edges_.size();
}

bool Graph::directed() const {
    return directed_;
}

bool Graph::weighted() const {
    return weighted_;
}

bool Graph::has_negative_weight() const {
    for (const auto& e : edges_) {
        if (e.alive && e.weight < 0.0f) {
            return true;
        }
    }
    return false;
}

std::uint64_t Graph::revision() const {
    return revision_;
}

} // namespace gv
