#include "algo/algos.hpp"

#include <cstdint>
#include <queue>
#include <vector>

namespace gv {

Trace run_bfs(const Graph& g, const AlgoParams& params) {
    Trace trace;
    trace.algo_id = "bfs";
    trace.graph_revision = g.revision();
    trace.frontier_kind = FrontierKind::Queue;

    const std::size_t ncap = g.node_capacity();
    const std::size_t ecap = g.edge_capacity();
    trace.result.parent.assign(ncap, kNoNode);
    trace.result.parent_edge.assign(ncap, kNoEdge);
    trace.result.dist.assign(ncap, kInf);

    if (!g.has_node(params.start)) {
        trace.ok = false;
        trace.error = "no de origem invalido";
        return trace;
    }

    enum class Color : std::uint8_t { White, Gray, Black };
    std::vector<Color> color(ncap, Color::White);
    std::vector<bool> edge_done(ecap, false);
    std::queue<NodeId> q;

    const NodeId start = params.start;
    color[start] = Color::Gray;
    trace.result.dist[start] = 0.0;
    q.push(start);

    trace.steps.push_back(Step{StepType::SetLabel, start, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 0, true, {}});
    trace.steps.push_back(Step{StepType::Discover, start, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 0, true, {}});
    trace.steps.push_back(Step{StepType::Push, start, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 0, false, {}});

    while (!q.empty()) {
        NodeId u = q.front();
        q.pop();

        trace.result.visit_order.push_back(u);
        trace.steps.push_back(Step{StepType::Pop, u, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 2, true, {}});
        trace.steps.push_back(Step{StepType::Visit, u, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 2, false, {}});

        for (const Arc& arc : g.out_arcs(u)) {
            EdgeId e = arc.edge;
            NodeId v = arc.to;
            if (!g.directed()) {
                if (edge_done[e]) {
                    continue;
                }
                edge_done[e] = true;
            }

            trace.steps.push_back(Step{StepType::ExamineEdge, u, v, e, LabelSlot::Dist, 0.0, 3, false, {}});

            if (color[v] == Color::White) {
                color[v] = Color::Gray;
                trace.result.parent[v] = u;
                trace.result.parent_edge[v] = e;
                trace.result.dist[v] = trace.result.dist[u] + 1.0;
                q.push(v);

                trace.steps.push_back(Step{StepType::Discover, v, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 5, true, {}});
                trace.steps.push_back(Step{StepType::SetLabel, v, kNoNode, kNoEdge, LabelSlot::Dist, trace.result.dist[v], 5, true, {}});
                trace.steps.push_back(Step{StepType::Push, v, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 5, true, {}});
                trace.steps.push_back(Step{StepType::TreeEdge, kNoNode, kNoNode, e, LabelSlot::Dist, 0.0, 5, false, {}});
            } else {
                trace.steps.push_back(Step{StepType::RejectEdge, kNoNode, kNoNode, e, LabelSlot::Dist, 0.0, 4, false, {}});
            }
        }

        color[u] = Color::Black;
        trace.steps.push_back(Step{StepType::Finish, u, kNoNode, kNoEdge, LabelSlot::Dist, 0.0, 6, false, {}});
    }

    return trace;
}

}
