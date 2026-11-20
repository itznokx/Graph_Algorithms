#include "algo/algos.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace gv {

namespace {

enum class DfsColor : std::uint8_t { White, Gray, Black };

struct DfsContext {
    const Graph& g;
    Trace& trace;
    std::vector<DfsColor> color;
    std::vector<bool> edge_done;
    int time = 0;

    void visit(NodeId u) {
        ++time;
        trace.result.disc[u] = time;
        color[u] = DfsColor::Gray;
        trace.result.visit_order.push_back(u);

        trace.steps.push_back(Step{StepType::Discover, u, kNoNode, kNoEdge, LabelSlot::Disc, 0.0, 3, true, {}});
        trace.steps.push_back(Step{StepType::SetLabel, u, kNoNode, kNoEdge, LabelSlot::Disc, static_cast<double>(time), 3, true, {}});
        trace.steps.push_back(Step{StepType::Push, u, kNoNode, kNoEdge, LabelSlot::Disc, 0.0, 3, true, {}});
        trace.steps.push_back(Step{StepType::Visit, u, kNoNode, kNoEdge, LabelSlot::Disc, 0.0, 3, false, {}});

        for (const Arc& arc : g.out_arcs(u)) {
            EdgeId e = arc.edge;
            NodeId v = arc.to;
            if (!g.directed()) {
                if (edge_done[e]) {
                    continue;
                }
                edge_done[e] = true;
            }

            trace.steps.push_back(Step{StepType::ExamineEdge, u, v, e, LabelSlot::Disc, 0.0, 4, false, {}});

            if (color[v] == DfsColor::White) {
                trace.result.parent[v] = u;
                trace.result.parent_edge[v] = e;
                trace.steps.push_back(Step{StepType::TreeEdge, kNoNode, kNoNode, e, LabelSlot::Disc, 0.0, 5, false, {}});
                visit(v);
                trace.steps.push_back(Step{StepType::Visit, u, kNoNode, kNoEdge, LabelSlot::Disc, 0.0, 4, false, {}});
            } else if (color[v] == DfsColor::Gray) {
                if (g.directed()) {
                    trace.result.has_cycle = true;
                    trace.steps.push_back(Step{StepType::BackEdge, kNoNode, kNoNode, e, LabelSlot::Disc, 0.0, 4, false, {}});
                } else {
                    trace.steps.push_back(Step{StepType::RejectEdge, kNoNode, kNoNode, e, LabelSlot::Disc, 0.0, 4, false, {}});
                }
            } else {
                if (g.directed()) {
                    StepType edge_type = (trace.result.disc[u] < trace.result.disc[v])
                        ? StepType::ForwardEdge
                        : StepType::CrossEdge;
                    trace.steps.push_back(Step{edge_type, kNoNode, kNoNode, e, LabelSlot::Disc, 0.0, 4, false, {}});
                } else {
                    trace.steps.push_back(Step{StepType::RejectEdge, kNoNode, kNoNode, e, LabelSlot::Disc, 0.0, 4, false, {}});
                }
            }
        }

        ++time;
        trace.result.fin[u] = time;
        color[u] = DfsColor::Black;
        trace.steps.push_back(Step{StepType::SetLabel, u, kNoNode, kNoEdge, LabelSlot::Fin, static_cast<double>(time), 6, true, {}});
        trace.steps.push_back(Step{StepType::Pop, u, kNoNode, kNoEdge, LabelSlot::Fin, 0.0, 6, true, {}});
        trace.steps.push_back(Step{StepType::Finish, u, kNoNode, kNoEdge, LabelSlot::Fin, 0.0, 6, false, {}});
    }
};

} // namespace

Trace run_dfs(const Graph& g, const AlgoParams& params) {
    Trace trace;
    trace.algo_id = "dfs";
    trace.graph_revision = g.revision();
    trace.frontier_kind = FrontierKind::Stack;

    const std::size_t ncap = g.node_capacity();
    const std::size_t ecap = g.edge_capacity();
    trace.result.parent.assign(ncap, kNoNode);
    trace.result.parent_edge.assign(ncap, kNoEdge);
    trace.result.disc.assign(ncap, 0);
    trace.result.fin.assign(ncap, 0);

    if (!g.has_node(params.start)) {
        trace.ok = false;
        trace.error = "no de origem invalido";
        return trace;
    }

    std::vector<NodeId> roots;
    auto all_nodes = g.nodes();
    roots.reserve(all_nodes.size());
    roots.push_back(params.start);

    if (params.legacy_dfs_root_order) {
        for (auto it = all_nodes.rbegin(); it != all_nodes.rend(); ++it) {
            if (*it != params.start) {
                roots.push_back(*it);
            }
        }
    } else {
        for (NodeId id : all_nodes) {
            if (id != params.start) {
                roots.push_back(id);
            }
        }
    }

    DfsContext ctx{
        g,
        trace,
        std::vector<DfsColor>(ncap, DfsColor::White),
        std::vector<bool>(ecap, false),
        0
    };

    for (NodeId r : roots) {
        if (ctx.color[r] == DfsColor::White) {
            ctx.visit(r);
        }
    }

    return trace;
}

} // namespace gv
