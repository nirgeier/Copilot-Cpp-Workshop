# Agent guidance for this repository

This file is for AI coding agents and for humans reviewing their work.

## Project shape

- C++17 library `edge_inference`, one CLI, one benchmark, one CTest executable.
- Public headers live in `include/edge_inference/`, implementations in `src/`.
- No network downloads at configure time. Do not add `FetchContent`, vcpkg, or
  Conan dependencies without an approved offline mirror.
- `models/` documents the artifact. Do not commit binaries or secrets.

## Commands an agent must run

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

If sanitizers are available locally, also run the `sanitizers` preset.

## C++ rules

- Keep the header and implementation split. Headers declare, sources define.
- Prefer value semantics, RAII, and `std::vector` / `std::array`. No raw
  `new` / `delete` in new code.
- Respect `const`-correctness and keep interfaces stable for existing callers.
- Validate sizes before indexing. Watch integer width and signedness.
- Do not invent STL or third-party APIs. If an API is uncertain, check the
  headers in this repository or ask before using it.
- Keep changes small and reviewable. One issue, one diff, one validation run.

## Validation gates

A proposed change is not done until build, tests, and, where available,
AddressSanitizer and UBSan have been run. Include the actual command output as
evidence. A passing test count alone is not evidence of correct behavior.

## Style

- Use ASCII hyphens in prose. Never use em dashes.
- Keep documentation short and factual. No invented metrics or dates.
- Every generated change is a proposal. A human approves it.
