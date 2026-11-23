# AI-Assisted Development with GitHub Copilot - C++ Workshop Repository

This is the prepared practice repository for the CodeWizard full-day workshop
for C++ development teams. The workshop teaches GitHub Copilot. C++ is the
working codebase, not the subject of the course.

The repository is intentionally small and self contained. It builds offline with
CMake and a C++17 compiler, needs no downloaded packages, and contains a small
library, a CLI, a benchmark, and a CTest suite with seeded gaps and defects for
the three hands-on labs.

## What is in here

| Path | Purpose |
| --- | --- |
| `include/edge_inference/`, `src/` | Small inference library with a deterministic reference backend |
| `cli/` | Command line tool that runs one input through the inference path |
| `benchmark/` | Latency benchmark with p50 and p95 reporting |
| `tests/` | CTest suite with two intentional failures for the labs |
| `data/` | Valid, boundary, and invalid input samples |
| `models/` | Notes on the model artifact and the optional ONNX Runtime path |
| `docs/labs/` | The three lab guides, aligned with the workshop syllabus |
| `.github/` | Copilot instructions, prompt files, a reviewer agent, and a skill |

## Quick start

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_benchmark data/valid.json
```

With a preset-free flow:

```bash
cmake -S . -B build/local -DBUILD_TESTING=ON
cmake --build build/local
ctest --test-dir build/local --output-on-failure
```

Expect the build to succeed and `preprocessing_tests` and
`postprocessing_tests` to fail on a clean checkout. Those failures are the
starting point for Lab 2 and Lab 3. `model_tests` should pass from the start.
See `docs/setup.md` for the exact list of seeded gaps.

## Labs

| Lab | Guide | Outcome |
| --- | --- | --- |
| 1 | `docs/labs/lab-1-customize-copilot.md` | A version controlled Copilot customization layer for this repository |
| 2 | `docs/labs/lab-2-agent-mode-mcp.md` | The preprocessing gap closed and all validation gates green |
| 3 | `docs/labs/lab-3-multi-agent-review.md` | The seeded argmax defect fixed, tested, and reviewed |

## Definition of done

A change is complete only when all of the following pass:

```bash
cmake --build --preset debug
ctest --preset debug --output-on-failure
cmake --preset sanitizers && cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

Code review is still a human decision. Treat every Copilot change as a
proposal and check it against `docs/review-checklist.md`.

## Notes

- No model binary is committed. `models/README.md` explains the reference
  backend and how to wire in a real ONNX Runtime build.
- Tests use Boost.Test (header only). Boost headers 1.70 or newer are required.
- Text in this repository uses ASCII hyphens, never em dashes.

Based on the CodeWizard syllabus `AI-Assisted Development with GitHub Copilot`,
full day, 09:00-17:00, three hands-on labs.
