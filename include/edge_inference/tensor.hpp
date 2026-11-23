#pragma once

#include <cstddef>
#include <string>

#include "edge_inference/types.hpp"

namespace edge_inference {

std::size_t element_count(const Tensor& tensor);

bool is_finite(float value) noexcept;

// Returns an empty string when the tensor is valid.
std::string validate_tensor(const Tensor& tensor);

}  // namespace edge_inference
