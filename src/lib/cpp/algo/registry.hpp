#pragma once

#include "algo/trace.hpp"
#include "core/graph.hpp"

#include <string>
#include <vector>

namespace gv {

using AlgoFn = Trace (*)(const Graph&, const AlgoParams&);

struct AlgoInfo {
    const char* id;
    const char* name;
    bool needs_start;
    bool accepts_target;
    bool needs_directed;
    bool needs_undirected;
    bool needs_nonneg_weights;
    FrontierKind frontier_kind;
    std::vector<std::string> pseudocode;
    AlgoFn run;
};

const std::vector<AlgoInfo>& algorithm_registry();
std::string validate(const Graph& g, const AlgoInfo& info, const AlgoParams& params);

} // namespace gv
