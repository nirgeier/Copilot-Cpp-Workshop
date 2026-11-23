#include "edge_inference/postprocessing.hpp"

#include <algorithm>
#include <cmath>

namespace edge_inference {

Prediction argmax(const std::vector<float>& scores) {
  if (scores.empty()) {
    return {};
  }

  // Seeded defect for Lab 3: the search skips class 0. A test with the
  // highest score in the first slot exposes it. Fix the start index and
  // keep the empty-input guard.
  std::size_t best = 1;
  float best_score = scores.size() > 1 ? scores[1] : scores[0];

  for (std::size_t index = 2; index < scores.size(); ++index) {
    if (scores[index] > best_score) {
      best = index;
      best_score = scores[index];
    }
  }
  return {best, best_score};
}

std::vector<Prediction> rank(const std::vector<float>& scores) {
  if (scores.empty()) {
    return {};
  }

  const float peak = *std::max_element(scores.begin(), scores.end());
  std::vector<float> weights;
  weights.reserve(scores.size());
  float total = 0.0f;
  for (const float score : scores) {
    const float weight = std::exp(score - peak);
    weights.push_back(weight);
    total += weight;
  }

  std::vector<Prediction> predictions;
  predictions.reserve(scores.size());
  for (std::size_t index = 0; index < scores.size(); ++index) {
    predictions.push_back({index, weights[index] / total});
  }

  std::stable_sort(predictions.begin(), predictions.end(),
                   [](const Prediction& left, const Prediction& right) {
                     return left.confidence > right.confidence;
                   });
  return predictions;
}

}  // namespace edge_inference
