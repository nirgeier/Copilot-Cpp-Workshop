# Task - Debug with Real Evidence

!!! abstract "About this Task"
    - Work the `preprocessing_tests` failure from a pasted assertion to a scoped fix.
    - This is the one foundations task that assigns a seeded defect.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [8. Debugging with Copilot](../../01-Copilot-Foundations/08-Lab-Debugging-with-Copilot.md) |
| Scope | `src/`, `include/edge_inference/`, `tests/` for one defect, plus one new test |
| Inputs | Full CTest output, the public header, the implementation, the review checklist |
| Constraints | Never weaken a test. Keep `postprocessing_tests` failing. No new dependencies. |
| Deliverable | A scoped fix, one focused test, and validation output |
| Validation | Build, CTest, and sanitizers where available |

## Lab Goals

- Feed exact evidence into the debug loop instead of a paraphrase.
- Demand hypotheses and disproof commands before editing.
- Close a fix with CTest, the review checklist, and sanitizers.

## The Task

- Fix `preprocessing_tests` using Copilot as a partner.
- Add one boundary case with the shipped skill.
- Leave `postprocessing_tests` failing for a later lab.

## Task Steps

### Step 1 - Capture the real failure

Run the test command and copy the complete assertion block into chat, with file, line, and expected versus actual values.

**Expected evidence:** the raw terminal block in your notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

```sh
ctest --preset debug --output-on-failure
```

- The output points at `tests/test_preprocessing.cpp` lines 22 and 23: the minimum is not 0.0 and the maximum is not 1.0 for `NormalizesToUnitRange`.
- Paste both assertions verbatim.
- Do not write "normalization is wrong" instead.

</details>

### Step 2 - Ask for hypotheses and disproof commands

- Attach the header and source.
- Ask for at most three causes, each tied to a line, and one command that would disprove each.

**Expected evidence:** three hypotheses with file and line references.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- A good prompt: "Using `include/edge_inference/preprocessing.hpp` and `src/preprocessing.cpp`, give at most three causes for these assertions.
- Cite file and line for each.
- For each cause, name the command or test that would disprove it.
- Do not edit yet."

- Typical grounded causes include wrong divisor during normalization, a missing handling of the all-equal input, or an off-by-one in the bounds scan.
- A cause without a line reference is a guess.

</details>

### Step 3 - Apply the smallest fix

Choose one hypothesis, change the minimum amount of code, and rerun the same command.

**Expected evidence:** a diff with a clear before and after.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

Replace `src/preprocessing.cpp` with this complete implementation:

```cpp
#include "edge_inference/preprocessing.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace edge_inference {

Tensor preprocess(const std::vector<float>& values) {
  Tensor output;
  output.shape = {1, kInputSize};
  output.data.assign(kInputSize, 0.0f);

  const std::size_t count = std::min(values.size(), kInputSize);
  for (std::size_t index = 0; index < count; ++index) {
    output.data[index] = values[index];
  }

  // Normalize into [0, 1] using the observed range. A constant or invalid
  // range has no meaningful normalization, so keep the zero filled tensor.
  const auto bounds =
      std::minmax_element(output.data.begin(), output.data.end());
  const float minimum = *bounds.first;
  const float maximum = *bounds.second;
  const float range = maximum - minimum;

  if (!std::isfinite(range) ||
      range <= std::numeric_limits<float>::epsilon()) {
    output.data.assign(kInputSize, 0.0f);
    return output;
  }

  for (float& value : output.data) {
    value = (value - minimum) / range;
  }
  return output;
}

}  // namespace edge_inference
```


After editing:

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- `preprocessing_tests` and `model_tests` should pass.
- `postprocessing_tests` should still fail.

</details>

### Step 4 - Add a focused test with the skill

Invoke the `add-boost-test-suite` skill to add one boundary case for the function you changed.

**Expected evidence:** a new or extended Boost.Test case with a boundary input.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

Ask Copilot: "Use the `add-boost-test-suite` skill to add a boundary case for `preprocess`." The resulting `tests/test_preprocessing.cpp` should be this complete file. The added case covers a constant input, where the range is zero:

```cpp
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

#include "edge_inference/preprocessing.hpp"

BOOST_AUTO_TEST_SUITE(PreprocessingTest)

BOOST_AUTO_TEST_CASE(ProducesFixedWidthTensor) {
  const edge_inference::Tensor tensor =
      edge_inference::preprocess({0.1f, 0.2f, 0.3f});
  BOOST_CHECK_EQUAL(tensor.shape.size(), 2u);
  BOOST_CHECK_EQUAL(tensor.shape[1], edge_inference::kInputSize);
  BOOST_CHECK_EQUAL(tensor.data.size(), edge_inference::kInputSize);
}

BOOST_AUTO_TEST_CASE(NormalizesToUnitRange) {
  const edge_inference::Tensor tensor = edge_inference::preprocess(
      {0.2f, 0.4f, 0.6f, 0.8f, 0.3f, 0.5f, 0.7f, 0.9f});
  const auto bounds = std::minmax_element(tensor.data.begin(), tensor.data.end());
  BOOST_CHECK(std::fabs(*bounds.first - 0.0f) < 1e-5f);
  BOOST_CHECK(std::fabs(*bounds.second - 1.0f) < 1e-5f);
}

BOOST_AUTO_TEST_CASE(ConstantInputMapsToZero) {
  const edge_inference::Tensor tensor = edge_inference::preprocess(
      std::vector<float>(edge_inference::kInputSize, 2.5f));
  BOOST_CHECK_EQUAL(tensor.data.size(), edge_inference::kInputSize);
  for (float value : tensor.data) {
    BOOST_CHECK(std::fabs(value) < 1e-5f);
  }
}

BOOST_AUTO_TEST_SUITE_END()
```

Do not edit production code to satisfy the new test.

</details>

### Step 5 - Challenge and sanitize

Ask a second opinion agent to argue against the diff, then run sanitizers where available.

**Expected evidence:** one rejected suggestion and sanitizer output.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Use Copilot CLI's `rubber-duck` agent: "Argue against this diff using `docs/review-checklist.md`.
- Cite file and line." Then run:

```sh
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

- If sanitizers hang or are unavailable in your environment, record that fact instead of claiming a pass.
- Do not suppress a finding without an explanation.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- Expected state: two of three CTest entries pass.
- `postprocessing_tests` remains failed.

## Definition of Done

- [ ] The raw failing assertion is in your notes.
- [ ] Three hypotheses with file and line were recorded before any edit.
- [ ] The fix changes only the files named in the chosen hypothesis.
- [ ] One focused boundary test was added with the skill.
- [ ] A second opinion was challenged and one suggestion was rejected with a reason.
- [ ] Sanitizers were run or their unavailability was recorded.
- [ ] `postprocessing_tests` still fails.

## Summary

Debug from exact output, not a description<br>
Prove a cause before editing and add a focused test<br>
Close with review checklist and sanitizer evidence
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

The smallest fix in `src/preprocessing.cpp` captures the range by value before it is modified, then guards a constant or non-finite input:

```cpp
#include <algorithm>
#include <cmath>
#include <limits>

const auto bounds =
    std::minmax_element(output.data.begin(), output.data.end());
const float minimum = *bounds.first;
const float maximum = *bounds.second;
const float range = maximum - minimum;

if (!std::isfinite(range) ||
    range <= std::numeric_limits<float>::epsilon()) {
  output.data.assign(kInputSize, 0.0f);
  return output;
}

for (float& value : output.data) {
  value = (value - minimum) / range;
}
```

The prompt that produces it must include the raw assertion:

```text
Using include/edge_inference/preprocessing.hpp and src/preprocessing.cpp,
give at most three causes for the two failing assertions. Cite file and line
for each. Name the command that would disprove each cause. Do not edit yet.
```

- Paste the real Boost.Test assertion and line, then `src/preprocessing.cpp` and its header.
- Three hypotheses tied to code lines and one disproving command each lead to the smallest fix.
- Add one boundary case with the `add-boost-test-suite` skill, rerun the full CTest set, and confirm `model_tests` still passes.
- Ask a second opinion to argue against the fix and use `/review` on the uncommitted diff.
- Run the sanitizer preset where available.
- Leave `postprocessing_tests` for Lab 3.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Review Copilot Usage Internally](06-Reviewing-Copilot-Usage.md)
