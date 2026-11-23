# Model artifact

No binary model is committed to this repository.

The labs run against `edge_inference::Model`, a deterministic reference backend
with the shape of a small ONNX Runtime C++ wrapper. It computes three scores
from eight inputs using fixed weights in `src/model.cpp`, then produces
confidence ordered predictions through `src/postprocessing.cpp`. This keeps the
workshop reproducible on an air-gapped workstation.

To use a real model:

1. Obtain an approved ONNX model through the organization process. Do not
   download one during the workshop.
2. Point `onnxruntime_DIR` at an approved local package and implement the
   `USE_ONNX_RUNTIME` branch in `CMakeLists.txt`. Keep the public interface in
   `include/edge_inference/model.hpp` unchanged.
3. Validate that the model input shape is `{1, 8}` and that preprocessing
   produces the same scale the model was trained with.
4. Recheck all three data samples and record before and after benchmark numbers.

An agent that proposes a new third party API without checking the available
headers should be challenged. See `docs/review-checklist.md`.
