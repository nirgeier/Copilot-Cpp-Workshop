# Agent guidance for mini_infer

This file is for AI coding agents and for humans reviewing their work.

## Project shape

- C++17 library `mini_infer`, one CLI, one CTest executable with two suites.
- Public headers live in `include/mini_infer/`, implementations in `src/`.
- No network downloads at configure time. Only Boost.Test headers are required.
- `solution.zip` is a generated archive. Regenerate it with `scripts/package-solution.sh`.

## Commands an agent must run

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

If sanitizers are available locally, also run:

```bash
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

## C++ rules

- Keep the header and implementation split. Headers declare, sources define.
- Prefer value semantics and `std::vector`. No raw `new` or `delete`.
- Respect `const`-correctness and keep the two public signatures stable.
- Validate sizes before indexing. Use `std::size_t` for indexes.
- Do not invent STL or third-party APIs. Check the headers in this repository first.
- Keep changes small and reviewable. One issue, one diff, one validation run.

## Validation gates

A proposed change is not done until build, tests, and, where available, AddressSanitizer
and UBSan have been run. Include the actual command output as evidence. A passing test
count alone is not evidence of correct behavior.

## Style

- Use ASCII hyphens in prose. Never use em dashes.
- Keep documentation short and factual. No invented metrics or dates.
- Every generated change is a proposal. A human approves it.
