# Workshop setup

## Prerequisites

- C++17 compiler (MSVC, GCC, or Clang)
- CMake 3.20 or newer and CTest
- VS Code with GitHub Copilot and the C/C++ and CMake Tools extensions, subject
  to the organization allowlist
- An approved GitHub account with access to this private repository
- Boost headers 1.70 or newer, available offline (Boost.Test is used in
  header-only mode)

No packages are downloaded at configure time. The reference backend needs no
ONNX Runtime installation and no model binary.

## Configure, build, test

Using presets:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Without presets:

```bash
cmake -S . -B build/local -DBUILD_TESTING=ON
cmake --build build/local
ctest --test-dir build/local --output-on-failure
```

`compile_commands.json` is generated in the build directory. Point the C/C++
extension at it so Copilot sees the same compile flags the compiler uses.

## Expected clean-checkout state

The build succeeds. Three CTest entries are registered:

| CTest name | Expected result on a clean checkout |
| --- | --- |
| `model_tests` | Pass |
| `preprocessing_tests` | Fail in `NormalizesToUnitRange` (Lab 2) |
| `postprocessing_tests` | Fail in `ArgmaxIncludesFirstClass` (Lab 3) |

Those two failures are intentional. `No tests were found` is a failure, not a
success.

## Optional local modes

```bash
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

Boost.Test is header only in this repository, so there is no separate test mode.
If Boost headers are installed in a non-standard location, configure with
`-DBOOST_ROOT=/path/to/boost`. A real ONNX Runtime backend is not configured
by default; see `models/README.md`.

## Run the tools

```bash
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_inference_cli data/invalid.json
./build/debug/edge_benchmark data/valid.json 2000
```

The invalid sample must produce an error, not a silent prediction.

## Before the workshop

1. Fork or clone through the approved Git flow and open the folder in VS Code.
2. Confirm Copilot is signed in and enabled for this repository.
3. Run the configure, build, and test commands above and record the output.
4. Read `AGENTS.md`, `.github/copilot-instructions.md`, and the three lab guides.
