#include "edge_inference/benchmark.hpp"

#include <algorithm>
#include <chrono>
#include <vector>

namespace edge_inference {

BenchmarkResult benchmark(const Model& model, const Tensor& input,
                          std::size_t iterations) {
  BenchmarkResult result;
  result.iterations = iterations;
  if (iterations == 0) {
    return result;
  }

  std::vector<double> samples;
  samples.reserve(iterations);

  for (std::size_t iteration = 0; iteration < iterations; ++iteration) {
    const auto started = std::chrono::steady_clock::now();
    const InferenceResult inference = model.infer(input);
    const auto finished = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration<double, std::milli>(
        finished - started);
    samples.push_back(elapsed.count());
    if (!inference.ok()) {
      return {};
    }
  }

  std::sort(samples.begin(), samples.end());
  result.p50_ms = samples[samples.size() / 2];
  const std::size_t p95_index =
      std::min(samples.size() - 1, samples.size() * 95 / 100);
  result.p95_ms = samples[p95_index];
  return result;
}

}  // namespace edge_inference
