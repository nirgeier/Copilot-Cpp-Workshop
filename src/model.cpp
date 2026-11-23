#include "edge_inference/model.hpp"

#include <array>
#include <utility>
#include <vector>

#include "edge_inference/postprocessing.hpp"
#include "edge_inference/preprocessing.hpp"
#include "edge_inference/tensor.hpp"

namespace edge_inference {
namespace {

constexpr std::size_t kClasses = 3;
const std::array<std::array<float, kInputSize>, kClasses> kWeights{{
    {{0.9f, 0.1f, 0.4f, 0.2f, 0.7f, 0.3f, 0.6f, 0.5f}},
    {{0.1f, 0.8f, 0.3f, 0.9f, 0.2f, 0.7f, 0.4f, 0.6f}},
    {{0.3f, 0.2f, 0.9f, 0.4f, 0.1f, 0.8f, 0.5f, 0.7f}},
}};

}  // namespace

Model::Model(std::string name) : name_(std::move(name)) {}

InferenceResult Model::infer(const Tensor& input) const {
  InferenceResult result;

  const std::string problem = validate_tensor(input);
  if (!problem.empty()) {
    result.error = "invalid tensor: " + problem;
    return result;
  }
  if (input.shape[1] != kInputSize) {
    result.error = "unexpected input width";
    return result;
  }

  std::vector<float> scores(kClasses, 0.0f);
  for (std::size_t label = 0; label < kClasses; ++label) {
    for (std::size_t index = 0; index < kInputSize; ++index) {
      scores[label] += input.data[index] * kWeights[label][index];
    }
  }

  result.rankings = rank(scores);
  return result;
}

}  // namespace edge_inference
