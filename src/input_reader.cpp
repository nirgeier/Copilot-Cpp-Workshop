#include "edge_inference/input_reader.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <string>

namespace edge_inference {

std::optional<std::vector<float>> read_values(const std::string& path) {
  std::ifstream stream(path);
  if (!stream) {
    return std::nullopt;
  }

  const std::string text((std::istreambuf_iterator<char>(stream)),
                         std::istreambuf_iterator<char>());
  const std::size_t open = text.find('[');
  if (open == std::string::npos) {
    return std::nullopt;
  }
  const std::size_t close = text.find(']', open + 1);
  if (close == std::string::npos) {
    return std::nullopt;
  }

  std::vector<float> values;
  const char* cursor = text.data() + open + 1;
  const char* const last = text.data() + close;

  while (cursor < last) {
    while (cursor < last &&
           (*cursor == ',' ||
            std::isspace(static_cast<unsigned char>(*cursor)) != 0)) {
      ++cursor;
    }
    if (cursor >= last) {
      break;
    }

    char* next = nullptr;
    const float value = std::strtof(cursor, &next);
    if (next == cursor) {
      return std::nullopt;
    }
    values.push_back(value);
    cursor = next;
  }

  return values;
}

}  // namespace edge_inference
