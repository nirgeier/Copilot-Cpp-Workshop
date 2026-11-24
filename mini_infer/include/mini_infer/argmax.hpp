#pragma once

#include <cstddef>
#include <vector>

namespace mini_infer {

// Returns the index of the largest value.
// Returns zero for an empty vector. On a tie, the first maximum wins.
std::size_t argmax(const std::vector<double>& values);

}  // namespace mini_infer
