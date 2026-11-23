# 3. Lab 2 - Plan, Build and Validate

!!! abstract "About this Lab"
    **Time:** 14:15-15:00 (45 minutes). Close the preprocessing gap with a controlled agent workflow. Issue #2 is your task record.

## 1. Problem Statement

`preprocess` copies raw values into a fixed width tensor but never normalizes them. `PreprocessingTest.NormalizesToUnitRange` fails on a clean checkout.

## 2. Acceptance Criteria

- [ ] Values are mapped into the `[0, 1]` range using the input minimum and maximum.
- [ ] A constant input does not divide by zero and stays finite.
- [ ] Inputs shorter than eight values are padded before normalization.
- [ ] The public interface in `include/edge_inference/preprocessing.hpp` is unchanged.
- [ ] No new dependency is introduced.

!!! warning "Capture the minimum by value"
    `std::minmax_element` returns iterators into the vector you are about to modify. Read the minimum and maximum into local values before the normalization loop.

## 3. Workflow

1. Open issue #2 and use the Plan agent to turn the criteria into a short plan.
2. If the GitHub MCP server is approved, use it to read the issue as grounded context. Read-only scopes are enough.
3. Approve the plan, then implement in one small increment.
4. Inspect the diff. Run the build and paste real failures back to the agent.
5. Challenge any invented API or unsupported assumption.
6. Run the sanitizer preset and record the result.

## 4. Definition of Done

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure -R preprocessing_tests
cmake --preset sanitizers && cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

- [ ] `preprocessing_tests` passes; `model_tests` still passes.
- [ ] `postprocessing_tests` still fails on the seeded argmax defect.
- [ ] No test was changed and no interface was broken.
- [ ] The approved plan, final diff, and test output are recorded.

## 5. One Sentence to Record

Explain why the constant-input guard is necessary and what would happen without it.

---

**Next:** [Lab 03: Multi-Agent and Review](../03-Multi-Agent-and-Review/README.md)
