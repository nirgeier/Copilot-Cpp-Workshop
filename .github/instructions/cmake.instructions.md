---
applyTo: "**/CMakeLists.txt"
---

# CMake rules for this repository

- Keep the minimum at CMake 3.20 and the language at C++17.
- Do not add `FetchContent`, vcpkg, or Conan. The workshop assumes no network.
- Keep `CMAKE_EXPORT_COMPILE_COMMANDS` on so tooling sees real compile flags.
- New targets must build with the `debug` preset and be registered with CTest
  if they are tests.
- Sanitizers are behind `ENABLE_SANITIZERS`. Do not enable them by default.
- The `USE_ONNX_RUNTIME` option is intentionally a documented stub. Do not
  replace the reference backend without a reviewed dependency plan.
- After editing, configure from scratch and run build plus tests.
