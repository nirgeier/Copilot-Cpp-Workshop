#include "edge_inference/tensor.hpp"

#include <cmath>

namespace edge_inference {

std::size_t element_count(const Tensor& tensor) {
  std::size_t count = 1;
  for (const std::size_t dimension : tensor.shape) {
    count *= dimension;
  }
  return count;
}

bool is_finite(float value) noexcept { return std::isfinite(value); }

std::string validate_tensor(const Tensor& tensor) {
  if (tensor.shape.size() != 2) {
    return "expected a rank-2 tensor";
  }
  if (element_count(tensor) != tensor.data.size()) {
    return "shape and data length differ";
  }
  for (const float value : tensor.data) {
    if (!is_finite(value)) {
      return "non-finite tensor value";
    }
  }
  return {};
}

}  // namespace edge_inference
