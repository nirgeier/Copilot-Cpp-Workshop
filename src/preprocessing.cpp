#include "edge_inference/preprocessing.hpp"

#include <algorithm>

namespace edge_inference {

Tensor preprocess(const std::vector<float>& values) {
  Tensor output;
  output.shape = {1, kInputSize};
  output.data.assign(kInputSize, 0.0f);

  const std::size_t count = std::min(values.size(), kInputSize);
  for (std::size_t index = 0; index < count; ++index) {
    output.data[index] = values[index];
  }

  // TODO(Lab 2): normalize output.data into the [0, 1] range using its
  // minimum and maximum. Guard against a constant input, validate the
  // result, then run ctest and report the evidence in the issue.
  return output;
}

}  // namespace edge_inference
