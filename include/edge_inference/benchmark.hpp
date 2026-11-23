#pragma once

#include <cstddef>

#include "edge_inference/model.hpp"
#include "edge_inference/types.hpp"

namespace edge_inference {

struct BenchmarkResult {
  std::size_t iterations = 0;
  double p50_ms = 0.0;
  double p95_ms = 0.0;
};

BenchmarkResult benchmark(const Model& model, const Tensor& input,
                          std::size_t iterations);

}  // namespace edge_inference
