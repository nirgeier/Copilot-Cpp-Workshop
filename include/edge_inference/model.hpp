#pragma once

#include <string>

#include "edge_inference/types.hpp"

namespace edge_inference {

// A deterministic reference backend with the shape of a small runtime wrapper.
// It deliberately avoids any binary model artifact or network dependency.
class Model {
 public:
  explicit Model(std::string name = "reference-3class");

  InferenceResult infer(const Tensor& input) const;

  const std::string& name() const noexcept { return name_; }

 private:
  std::string name_;
};

}  // namespace edge_inference
