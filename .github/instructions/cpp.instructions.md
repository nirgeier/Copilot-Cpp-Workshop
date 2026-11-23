---
applyTo: "**/*.cpp, **/*.hpp"
---

# C++ rules for this repository

- Declare in `include/edge_inference/*.hpp`, define in `src/*.cpp`.
- Use C++17 only. No compiler extensions and no C++20 features.
- Prefer `std::vector`, `std::array`, and value semantics. No raw `new` or
  `delete`.
- Check sizes before indexing and return a clear error for malformed input.
- Keep existing signatures stable. Add a new function instead of changing a
  public contract without an explicit request.
- Never weaken or delete a test to obtain a green run.
- After editing, run `cmake --build --preset debug` and
  `ctest --preset debug --output-on-failure`.
