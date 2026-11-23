---
description: Generate focused Boost.Test cases for one C++ function in this repository
agent: Edit
---

# Generate focused tests

1. Read the target header and implementation, plus the existing tests in
   `tests/`.
2. Use the same Boost.Test style as the existing suite: `BOOST_AUTO_TEST_SUITE`
   and `BOOST_AUTO_TEST_CASE`, with `boost/test/unit_test.hpp`.
3. Cover one behavior per test: the happy path, a boundary, and a failure path
   where the function has one.
4. Assert on observable results, not on implementation details.
5. Do not edit production code to make a generated test pass.
6. Add the test file to `CMakeLists.txt` if it is new, register a CTest
   entry with `--run_test=Suite/*`, then run it and paste the output.

Use the data samples in `data/` where they fit the behavior under test.
