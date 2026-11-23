#include <cstdlib>
#include <iostream>
#include <string>

#include "edge_inference/benchmark.hpp"
#include "edge_inference/input_reader.hpp"
#include "edge_inference/model.hpp"
#include "edge_inference/preprocessing.hpp"

int main(int argc, char** argv) {
  if (argc < 2 || argc > 3) {
    std::cerr << "usage: edge_benchmark <input.json> [iterations]\n";
    return 2;
  }

  const auto values = edge_inference::read_values(argv[1]);
  if (!values) {
    std::cerr << "could not read a numeric array from " << argv[1] << '\n';
    return 1;
  }

  std::size_t iterations = 1000;
  if (argc == 3) {
    char* end = nullptr;
    const unsigned long parsed = std::strtoul(argv[2], &end, 10);
    if (end == argv[2] || parsed == 0) {
      std::cerr << "iterations must be a positive integer\n";
      return 2;
    }
    iterations = static_cast<std::size_t>(parsed);
  }

  const edge_inference::Tensor input = edge_inference::preprocess(*values);
  const edge_inference::Model model;
  const edge_inference::BenchmarkResult result =
      edge_inference::benchmark(model, input, iterations);

  if (result.iterations == 0) {
    std::cerr << "benchmark did not produce a valid result\n";
    return 1;
  }

  std::cout << "iterations: " << result.iterations << '\n';
  std::cout << "p50_ms: " << result.p50_ms << '\n';
  std::cout << "p95_ms: " << result.p95_ms << '\n';
  return 0;
}
