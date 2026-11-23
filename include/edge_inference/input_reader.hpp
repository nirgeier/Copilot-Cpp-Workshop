#pragma once

#include <optional>
#include <string>
#include <vector>

namespace edge_inference {

// Reads a JSON style array of numbers such as {"values": [0.1, 0.2]}.
// Returns no value when the file or the array cannot be read.
std::optional<std::vector<float>> read_values(const std::string& path);

}  // namespace edge_inference
