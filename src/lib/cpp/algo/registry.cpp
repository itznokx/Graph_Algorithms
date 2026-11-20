#include "algo/registry.hpp"
#include "algo/algos.hpp"
#include "trace.hpp"

namespace gv {

const std::vector<AlgoInfo>& algorithm_registry() {
    static const std::vector<AlgoInfo> reg = {
        {
            "bfs",
            "BFS",
            true,
            false,
            false,
            false,
            false,
            FrontierKind::Queue,
            {""},
            &run_bfs
        },
        {
            "dfs",
            "DFS",
            true,
            false,
            false,
            false,
            false,
            FrontierKind::Stack,
            {""},
            &run_dfs
        },
        {
            "topo",
            "Ordenacao Topologica",
            false,
            false,
            true,
            false,
            false,
            FrontierKind::Stack,
            {""},
            &run_topo
        },
        {
            "prim",
            "PRIM",
            false,
            false,
            false,
            false,
            false,
            FrontierKind::MinHeap,
            {""},
            &run_prim

        }
    };
    return reg;
}

std::string validate(const Graph& g, const AlgoInfo& info, const AlgoParams& params) {
    if (g.node_count() == 0) {
        return "grafo vazio";
    }
    if (info.needs_directed && !g.directed()) {
        return "algoritmo requer grafo direcionado";
    }
    if (info.needs_undirected && g.directed()) {
        return "algoritmo requer grafo nao direcionado";
    }
    if (info.needs_nonneg_weights && g.has_negative_weight()) {
        return "algoritmo nao aceita pesos negativos";
    }
    if (info.needs_start && !g.has_node(params.start)) {
        return "no de origem invalido";
    }
    if (params.target != kNoNode && !g.has_node(params.target)) {
        return "no de destino invalido";
    }
    return "";
}

} // namespace gv
