# 3. Plan, Build and Validate

!!! abstract "About this Lab"
    - The preprocessing gap is defined by a failing test and a controlled workflow.
    - The acceptance criteria name the evidence a solution must provide.


## 1. Problem Statement

- `preprocess` copies raw values into a fixed width tensor but never normalizes them.
- `PreprocessingTest.NormalizesToUnitRange` fails on a clean checkout.

## 2. Acceptance Criteria

- Values are mapped into the `[0, 1]` range using the input minimum and maximum.
- A constant input does not divide by zero and stays finite.
- Inputs shorter than eight values are padded before normalization.
- The public interface in `include/edge_inference/preprocessing.hpp` is unchanged.
- No new dependency is introduced.

!!! warning "Capture the minimum by value"
    - `std::minmax_element` returns iterators into the vector you are about to modify.
    - Read the minimum and maximum into local values before the normalization loop.

## Reference

### Acceptance criteria reference

| Criterion | Proof in this repository |
|-----------|--------------------------|
| Values map into `[0, 1]` | `PreprocessingTest.NormalizesToUnitRange` passes |
| Constant input stays finite | No division by zero in the normalization loop |
| Short inputs padded first | Existing boundary test and added evidence |
| Public interface unchanged | `include/edge_inference/preprocessing.hpp` has no diff |
| No new dependency | `CMakeLists.txt` has no download based target |

- Capture the input minimum and maximum by value before modifying the vector. `std::minmax_element` returns iterators into that vector.
- Use the GitHub MCP server read only if it is approved. Read only scopes are enough to read issue #2.

```sh
ctest --preset debug --output-on-failure -R preprocessing_tests
```

!!! note "Definition of done"
    - `preprocessing_tests` and `model_tests` pass. `postprocessing_tests` still fails on the seeded argmax defect.
    - No test was changed and no interface was broken.

---

## Example

```text
Plan for issue #1

Scope: normalize the tensor produced by preprocess.
Files: src/preprocessing.cpp, tests/test_preprocessing.cpp
Proof: ctest --preset debug --output-on-failure
Steps:
  1. Read include/edge_inference/preprocessing.hpp.
  2. Paste the failing assertion from test_preprocessing.cpp:22.
  3. Normalize by the observed range; guard a constant input.
  4. Add a boundary case. Do not weaken existing assertions.
Checks: cmake --build --preset debug, ctest --preset debug --output-on-failure
Risks: padded zero slots must not change the documented tensor contract.
Open questions: should a constant input map to zero or to 0.5?
```

---

**Next:** [Lab 03: Multi-Agent and Review](../03-Multi-Agent-and-Review/README.md)
