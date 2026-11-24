#include "mini_infer/argmax.hpp"
#include "mini_infer/normalize.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: mini_infer_cli <file>\n";
    return 2;
  }

  const std::string path = argv[1];
  std::ifstream input(path);
  if (!input) {
    std::cerr << "error: cannot open " << path << "\n";
    return 1;
  }

  std::vector<double> values;
  double value = 0.0;
  while (input >> value) {
    values.push_back(value);
  }
  if (input.bad()) {
    std::cerr << "error: failed while reading " << path << "\n";
    return 1;
  }
  if (values.empty()) {
    std::cerr << "error: no numbers in " << path << "\n";
    return 1;
  }

  const bool normalized = mini_infer::normalize(values);
  const std::size_t best = mini_infer::argmax(values);

  std::cout << "count: " << values.size() << "\n";
  std::cout << "normalized:";
  for (const double item : values) {
    std::cout << ' ' << item;
  }
  std::cout << "\nargmax index: " << best << "\n";
  std::cout << "normalize ok: " << (normalized ? "true" : "false") << "\n";
  return 0;
}
