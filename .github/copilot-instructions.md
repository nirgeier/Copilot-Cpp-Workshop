# Repository-wide Copilot instructions

This is a teaching repository for a GitHub Copilot workshop. C++ is the working
codebase; the course subject is Copilot. Keep changes small and explainable.

## Facts about this repository

- C++17, CMake 3.20 or newer, one library, one CLI, one benchmark, one CTest
  executable. No network download at configure time.
- Configure: `cmake --preset debug`
- Build: `cmake --build --preset debug`
- Test: `ctest --preset debug --output-on-failure`
- Tests use Boost.Test in header-only mode. Boost headers 1.70 or newer are
  required and must be available offline.
- Two test failures are seeded on purpose. Do not fix them unless the task asks
  for preprocessing normalization (Lab 2) or the argmax defect (Lab 3).

## How to propose changes

- Read the relevant headers and sources before editing. Ground every claim in
  repository evidence.
- Prefer RAII, standard containers, `const`-correctness, and clear error paths.
  No raw `new` or `delete` in new code.
- Validate sizes before indexing. Watch signedness and integer width.
- Do not invent APIs. If a call is uncertain, check the available headers first.
- Do not add dependencies, model binaries, secrets, or client data.
- Keep the public interface in `include/edge_inference/` stable unless asked.
- Keep prose in ASCII hyphens. Do not use em dashes.

## Definition of done

A change is complete only after build, tests, and, where available, the
sanitizer preset have been run. Include the actual command output as evidence.
Treat all generated code as a proposal for a human reviewer.
