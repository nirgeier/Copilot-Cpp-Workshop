# Lab 2 - Plan, build, and validate with agent mode and MCP

Aligned with Module 7 of the syllabus. 45 minutes.

## Starting point

`preprocessing_tests` fails in `NormalizesToUnitRange`. The preprocessing
function copies input values into a fixed width tensor but does not normalize
them.

## Acceptance criteria

- `preprocess` maps values into the `[0, 1]` range using the input minimum and
  maximum.
- A constant input does not divide by zero. The result stays finite.
- Inputs shorter than eight values are padded before normalization.
- The public interface in `include/edge_inference/preprocessing.hpp` is
  unchanged.
- No new dependency is introduced.

## Workflow

1. Open the Lab 2 issue and use the Plan agent to turn the acceptance criteria
   into a small, repository-grounded plan. Approve the plan before edits.
2. If the GitHub MCP server is approved and configured, use it to read the
   issue and any related pull requests as context. Do not grant write scope.
3. Implement in one small increment. Inspect the diff, then run the build.
4. Feed the actual compiler or test output back to the agent. Do not paste a
   guess or edit the test to make it pass.
5. Challenge any invented API or unsupported assumption before accepting it.
6. Run the sanitizer preset and record the result.

## Definition of done

```bash
cmake --build --preset debug
ctest --preset debug --output-on-failure
cmake --preset sanitizers && cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

All tests pass, including the two that failed at the start of the day only if
Lab 3 has also been completed. In this lab, only the preprocessing gate is
required to turn green.

## Evidence to record

The approved plan, the final diff, the test output, and one sentence explaining
why the constant-input guard is necessary.
