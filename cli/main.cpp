#include <iostream>
#include <string>

#include "edge_inference/input_reader.hpp"
#include "edge_inference/model.hpp"
#include "edge_inference/preprocessing.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: edge_inference_cli <input.json>\n";
    return 2;
  }

  const auto values = edge_inference::read_values(argv[1]);
  if (!values) {
    std::cerr << "could not read a numeric array from " << argv[1] << '\n';
    return 1;
  }

  const edge_inference::Tensor input = edge_inference::preprocess(*values);
  const edge_inference::Model model;
  const edge_inference::InferenceResult result = model.infer(input);

  if (!result.ok()) {
    std::cerr << result.error << '\n';
    return 1;
  }

  std::cout << "model: " << model.name() << '\n';
  for (const auto& prediction : result.rankings) {
    std::cout << "class " << prediction.label << " confidence "
              << prediction.confidence << '\n';
  }
  return 0;
}
