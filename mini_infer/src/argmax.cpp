#include "mini_infer/argmax.hpp"

namespace mini_infer {

std::size_t argmax(const std::vector<double>& values) {
  std::size_t best = 0;
  for (std::size_t i = 1; i < values.size(); ++i) {
    if (values[i] > values[best]) {
      best = i;
    }
  }
  return best;
}

}  // namespace mini_infer
