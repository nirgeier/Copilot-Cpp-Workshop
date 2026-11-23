#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace edge_inference {

struct Tensor {
  std::vector<float> data;
  std::vector<std::size_t> shape;
};

struct Prediction {
  std::size_t label = 0;
  float confidence = 0.0f;
};

struct InferenceResult {
  std::vector<Prediction> rankings;
  std::string error;

  bool ok() const noexcept { return error.empty(); }
};

}  // namespace edge_inference
