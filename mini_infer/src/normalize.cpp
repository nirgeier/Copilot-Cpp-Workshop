#include "mini_infer/normalize.hpp"

#include <algorithm>
#include <cmath>

namespace mini_infer {

bool normalize(std::vector<double>& values) {
  if (values.empty()) {
    return false;
  }

  const auto bounds = std::minmax_element(values.begin(), values.end());
  const double lo = *bounds.first;
  const double hi = *bounds.second;

  if (!std::isfinite(lo) || !std::isfinite(hi) || hi == lo) {
    return false;
  }

  const double span = hi - lo;
  for (double& value : values) {
    value = (value - lo) / span;
  }
  return true;
}

}  // namespace mini_infer
