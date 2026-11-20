#pragma once

#include "core/ids.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace gv {

enum class StepType : std::uint8_t {
    Discover,
    Visit,
    Finish,
    Push,
    Pop,
    ExamineEdge,
    TreeEdge,
    BackEdge,
    ForwardEdge,
    CrossEdge,
    RejectEdge,
    Relax,
    SetLabel,
    ResultNode,
    ResultEdge,
    Note
};

enum class LabelSlot : std::uint8_t {
    Dist = 0,
    Key = 1,
    Disc = 2,
    Fin = 3,
    TopoIndex = 4
};

enum class FrontierKind : std::uint8_t {
    None,
    Queue,
    Stack,
    PriorityQueue,
    MinHeap
};

struct Step {
    StepType type;
    NodeId node = kNoNode;
    NodeId other = kNoNode;
    EdgeId edge = kNoEdge;
    LabelSlot slot = LabelSlot::Dist;
    double value = 0.0;
    int line = -1;
    bool chain = false;
    std::string text;
};

struct AlgoParams {
    NodeId start = kNoNode;
    NodeId target = kNoNode;
    bool legacy_dfs_root_order = false;
};

struct AlgoResult {
    std::vector<NodeId> visit_order;
    std::vector<NodeId> parent;
    std::vector<EdgeId> parent_edge;
    std::vector<double> dist;
    std::vector<int> disc;
    std::vector<int> fin;
    std::vector<NodeId> topo_order;
    std::vector<EdgeId> tree_edges;
    std::vector<NodeId> path;
    double total_weight = 0.0;
    bool has_cycle = false;
};

struct Trace {
    std::string algo_id;
    bool ok = true;
    std::string error;
    std::uint64_t graph_revision = 0;
    FrontierKind frontier_kind = FrontierKind::None;
    std::vector<Step> steps;
    AlgoResult result;
};

}
