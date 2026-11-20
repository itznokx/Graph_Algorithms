#pragma once

#include "algo/trace.hpp"
#include "core/graph.hpp"

namespace gv {

Trace run_bfs(const Graph& g, const AlgoParams& params);
Trace run_dfs(const Graph& g, const AlgoParams& params);
Trace run_topo(const Graph& g, const AlgoParams& params);
Trace run_prim(const Graph& g, const AlgoParams& params);

}
