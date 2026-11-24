#pragma once

#include <vector>

namespace mini_infer {

// Maps values into [0, 1] using the observed min and max.
// Returns false for an empty or constant input and leaves values unchanged.
bool normalize(std::vector<double>& values);

}  // namespace mini_infer
