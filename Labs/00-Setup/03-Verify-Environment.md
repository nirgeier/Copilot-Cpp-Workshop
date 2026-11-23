# 3. Verifying the Environment

!!! abstract "About this Guide"
    Clone the repository, build it, and record the baseline behavior. This check proves that any later failure comes from your changes, not from a broken workstation.

## 1. Clone the Repository

```sh
git clone https://github.com/nirgeier/Copilot-Cpp-Workshop.git
cd Copilot-Cpp-Workshop
git checkout -b lab/my-name
```

!!! tip "Approved Git flow"
    Use your organization's Git process if cloning through a proxy or mirror is required. Do not substitute a random external repository for the workshop material.

## 2. Configure and Build

```sh
cmake --preset debug
cmake --build --preset debug
```

`compile_commands.json` is generated in `build/debug/`. Point the VS Code C/C++ extension at it so Copilot sees the same flags the compiler uses.

## 3. Run the Tests

```sh
ctest --preset debug --output-on-failure
```

| CTest entry | Expected on a clean checkout |
|-------------|------------------------------|
| `model_tests` | Pass |
| `preprocessing_tests` | Fail in `NormalizesToUnitRange` |
| `postprocessing_tests` | Fail in `ArgmaxIncludesFirstClass` |

!!! warning "`No tests were found` is a failure"
    CTest must discover all three entries. If it reports no tests, stop and fix the configure step before continuing.

## 4. Run the CLI and the Benchmark

```sh
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_inference_cli data/invalid.json
./build/debug/edge_benchmark data/valid.json 500
```

- The valid sample prints three confidence ordered classes.
- The invalid sample contains `1e309` and must be rejected with an error and a non-zero exit code.
- The benchmark prints `p50_ms` and `p95_ms`.

## 5. Optional Sanitizer Check

```sh
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

The same two tests fail under sanitizers. No sanitizer report should appear.

## 6. Record Your Baseline

Save the following in your notes:

- Compiler and CMake versions
- The CTest summary line
- The invalid-input error message
- The benchmark output

---

**Next:** [Lab 01: Copilot Foundations](../01-Copilot-Foundations/README.md)
