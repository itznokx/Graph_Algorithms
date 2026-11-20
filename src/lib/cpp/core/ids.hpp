#pragma once

#include <limits>

namespace gv {

using NodeId = int;
using EdgeId = int;
using Weight = float;

constexpr NodeId kNoNode = -1;
constexpr EdgeId kNoEdge = -1;
constexpr double kInf = std::numeric_limits<double>::infinity();

}
