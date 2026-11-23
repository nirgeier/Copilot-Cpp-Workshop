#pragma once

#include <cstddef>
#include <vector>

#include "edge_inference/types.hpp"

namespace edge_inference {

constexpr std::size_t kInputSize = 8;

// Maps raw sample values onto the fixed width tensor the model expects.
Tensor preprocess(const std::vector<float>& values);

}  // namespace edge_inference
