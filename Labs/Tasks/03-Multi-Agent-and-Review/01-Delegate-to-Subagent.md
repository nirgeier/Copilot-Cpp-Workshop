# Task - Delegate to a Subagent

!!! abstract "About this Task"
    - A subagent gets its own context window and one narrow contract.
    - You will delegate two read-only investigations about a seeded failure, compare the results, and decide as the orchestrator.
    - You do not fix the defect here.

## 1. Choose a Question With Two Hypotheses

- Use `preprocessing_tests`.
- Two plausible causes to investigate:

| Hypothesis | Where to look |
|------------|---------------|
| Normalization is applied in the wrong order | `src/preprocessing.cpp`, `tests/test_preprocessing.cpp` |
| Integer width or signedness changes the result | `include/edge_inference/types.hpp`, `src/tensor.cpp` |

- Do not tell either subagent which hypothesis is correct.
- Each gets one hypothesis and the same evidence rules.

## 2. Write the Delegation Contract

Use a prompt of this shape for each subagent:

```text
Read-only investigation. Do not edit files and do not run build commands.

Question: could <hypothesis> explain the failing preprocessing_tests case in this repository?

Steps:
1. Read AGENTS.md and .github/copilot-instructions.md.
2. Read the named header before the named implementation.
3. Quote the failing assertion from tests/test_preprocessing.cpp.
4. Give a verdict: supported, unsupported, or unknown.
5. Cite file paths for every claim. State missing evidence explicitly.

Output: verdict, three evidence bullets, one disproving check.
```

!!! tip "Narrow output"
    - Ask for a verdict and evidence, not "investigate the bug".
    - A subagent with a vague task will explore the whole repository and return guesses.

## 3. Run the Two Investigations

- [ ] Start both subagent sessions with different hypotheses.
- [ ] Keep them isolated. Do not paste one result into the other.
- [ ] Record which files each one read.
- [ ] Mark every claim that has a file and line reference.
- [ ] Mark claims that rely on memory or assumption.

## 4. Decide as the Orchestrator

Compare the two outputs against the raw CTest failure:

```sh
ctest --preset debug --output-on-failure -R preprocessing_tests
```

- [ ] The orchestrator, not a subagent, chooses the leading hypothesis.
- [ ] The decision cites evidence from the real repository.
- [ ] Conflicting claims are listed with the missing check that would resolve them.
- [ ] No file was edited by any agent.

## 5. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Both agents return the same generic answer | Hypothesis was not in the prompt | Give each one a distinct question |
| An agent edited a source file | Read-only boundary was missing | Undo and restate the contract |
| Results cannot be compared | Output format was not specified | Require verdict, evidence, disproof |
| The orchestrator accepts a guess | No file references required | Reject claims without evidence |

## 6. Definition of Done

- [ ] Two isolated subagent sessions were run with distinct hypotheses.
- [ ] Both outputs use the verdict, evidence, disproof format.
- [ ] The orchestrator decision cites real file paths and the CTest output.
- [ ] No test or source file was changed.
- [ ] Unresolved questions are listed instead of guessed.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Expected state: both seeded failures are still present.

## 7. Summary

&emsp;✅&emsp;Give each subagent one question and one output contract<br>
&emsp;✅&emsp;Compare results with repository evidence<br>
&emsp;✅&emsp;Keep the final decision with the human orchestrator

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Subagent A prompt, sent in an isolated session:

```text
Read-only investigation. Do not edit files and do not run build commands.

Question: could normalization being applied in the wrong order explain the
failing preprocessing_tests case in this repository?

Steps:
1. Read AGENTS.md and .github/copilot-instructions.md.
2. Read include/edge_inference/preprocessing.hpp before src/preprocessing.cpp.
3. Quote the failing assertion from tests/test_preprocessing.cpp.
4. Give a verdict: supported, unsupported, or unknown.
5. Cite file paths for every claim. State missing evidence explicitly.

Output: verdict, three evidence bullets, one disproving check.
```

Subagent B prompt, sent in a separate isolated session:

```text
Read-only investigation. Do not edit files and do not run build commands.

Question: could integer width or signedness in the tensor types explain the
failing preprocessing_tests case in this repository?

Steps:
1. Read AGENTS.md and .github/copilot-instructions.md.
2. Read include/edge_inference/types.hpp before src/tensor.cpp.
3. Quote the failing assertion from tests/test_preprocessing.cpp.
4. Give a verdict: supported, unsupported, or unknown.
5. Cite file paths for every claim. State missing evidence explicitly.

Output: verdict, three evidence bullets, one disproving check.
```

Orchestrator comparison command:

```sh
ctest --preset debug --output-on-failure -R preprocessing_tests
```

- Subagent A checks normalization order in `src/preprocessing.cpp` and `tests/test_preprocessing.cpp`.
- Subagent B checks integer width and signedness in `include/edge_inference/types.hpp` and `src/tensor.cpp`.
- Both return a verdict with three evidence bullets and one disproving check; neither edits a file.
- The orchestrator compares them with the raw `ctest -R preprocessing_tests` output and records the missing check that would settle any conflict.

- A generic answer with no file reference is not evidence.
- The seeded failure stays open.

</details>

---

**Back:** [Tasks (Overview)](../README.md)
