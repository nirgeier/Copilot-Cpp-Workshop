---
name: add-boost-test-suite
description: Add a focused Boost.Test suite for one C++ function in the edge_inference library
---

# Add a Boost.Test suite

Use this skill when the task is to add tests for a function in
`include/edge_inference/` or `src/`.

## Procedure

1. Identify one function and its observable behavior. Read its header and
   implementation.
2. Create or edit one file under `tests/`, named `test_<area>.cpp`.
3. Include `boost/test/unit_test.hpp` and wrap cases in
   `BOOST_AUTO_TEST_SUITE` and `BOOST_AUTO_TEST_CASE`.
4. Write one case per behavior. Cover the happy path, a boundary, and a
   failure path where relevant.
5. If the file is new, add it to the `edge_unit_tests` target in
   `CMakeLists.txt`.
6. Register a CTest entry with `--run_test=Suite/*` when using the default
   harness.
7. Configure, build, and run the new CTest entry. Paste the output.

## Rules

- Never edit production code to make a new test pass.
- Never weaken an existing test.
- Do not add a download based test framework. Boost headers are a prerequisite.
- Keep prose in ASCII hyphens.
