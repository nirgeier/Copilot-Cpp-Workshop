#pragma once

#include <cstddef>
#include <vector>

#include "edge_inference/types.hpp"

namespace edge_inference {

Prediction argmax(const std::vector<float>& scores);

// Returns predictions ordered by descending confidence, with softmax scores.
std::vector<Prediction> rank(const std::vector<float>& scores);

}  // namespace edge_inference
