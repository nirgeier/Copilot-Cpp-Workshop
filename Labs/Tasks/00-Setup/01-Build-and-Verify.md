# Task - Build and Verify the Starter Repository

!!! abstract "About this Task"
    - Establish a baseline before you ask Copilot to change anything.
    - You will configure the project, build it, run the tests and the CLI, and record the exact starting state.

## 1. Prepare a Branch

```sh
git switch -c tasks/baseline
git status --short
```

- The working tree should contain only your task notes.
- Do not start from a dirty checkout.

## 2. Configure and Build

- The project has no network dependency at configure time.
- Use the presets from `CMakePresets.json`.

```sh
cmake --preset debug
cmake --build --preset debug
```

- Capture the full output.
- Note the compiler and the Boost.Test headers that were found locally.

## 3. Run the Tests

```sh
ctest --preset debug --output-on-failure
```

Expected starting state:

| Suite | Result |
|-------|--------|
| `model_tests` | Pass |
| `preprocessing_tests` | Fail, seeded |
| `postprocessing_tests` | Fail, seeded |

- Do not fix either seeded failure in this task.
- They are the starting points for later labs.

## 4. Run the CLI and the Benchmark

```sh
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_inference_cli data/invalid.json
./build/debug/edge_benchmark data/valid.json 500
```

- The invalid sample must be rejected through the documented error path.
- Read `data/README.md` before you describe the three samples.

## 5. Check the Sanitizer Preset

If the local toolchain supports it, run the sanitizer build as well.

```sh
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

- Skip this step if AddressSanitizer is not available.
- State that explicitly in your notes instead of inventing a result.

## 6. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Configure fails on Boost headers | Boost.Test headers below 1.70 or not installed | Install headers from the approved offline source |
| CLI prints a parse error for `valid.json` | Build ran from the wrong directory | Run from the repository root |
| Both seeded suites pass | Local changes are already present | Reset to the clean baseline and rerun |
| Sanitizer configure fails | Toolchain lacks sanitizer support | Record the limitation and continue |

## 7. Definition of Done

- [ ] `cmake --preset debug` and the debug build completed without errors.
- [ ] `ctest --preset debug --output-on-failure` output is attached.
- [ ] The two seeded failures and the passing `model_tests` are identified by name.
- [ ] CLI output for the valid and invalid samples is attached.
- [ ] Benchmark output is attached.
- [ ] Sanitizer status is recorded as run or unavailable.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

## 8. Summary

&emsp;✅&emsp;Configure and build with the repository presets<br>
&emsp;✅&emsp;Record the seeded failures as a baseline<br>
&emsp;✅&emsp;Run the CLI and benchmark with real samples

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_inference_cli data/invalid.json
./build/debug/edge_benchmark data/valid.json 500
```

Expected summary: `model_tests` passes, `preprocessing_tests` and `postprocessing_tests` fail.

- The baseline is a clean debug build with `model_tests` green and the two seeded suites red.
- Keep the raw output:

- [x] `cmake --preset debug` and `cmake --build --preset debug` complete without errors.
- [x] `ctest --preset debug --output-on-failure` shows `model_tests` passing and `preprocessing_tests` plus `postprocessing_tests` failing.
- [x] `edge_inference_cli data/valid.json` returns a result and `data/invalid.json` is rejected.
- [x] `edge_benchmark data/valid.json 500` prints p50 and p95.
- [x] Sanitizers are recorded as run or unavailable.

- Do not change any source file.
- If both seeded suites pass, the checkout was not clean.

</details>

---

**Back:** [Tasks (Overview)](../README.md)
