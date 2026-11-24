# Task - Subagents and Delegation

!!! abstract "About this Task"
    - Delegate an isolated investigation to a subagent and use a second opinion to challenge a conclusion.
    - Keep write access out of the review role.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [14. Subagents and Delegation](../../01-Copilot-Foundations/14-Lab-Subagents-and-Delegation.md) |
| Scope | Chat sessions only. No repository code changes. |
| Inputs | A proposed fix or conclusion, `docs/review-checklist.md`, the `runSubagent` tool |
| Constraints | Delegated output is untrusted. Review roles must not write. |
| Deliverable | A handoff contract, two delegated results, and an accepted and rejected finding |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Explain when delegation helps and when a main session question is better.
- Write a handoff contract with evidence, validation, and output format.
- Challenge a conclusion with a second opinion without treating it as approval.

## The Task

- Take a conclusion from an earlier task, for example the fix in task 05.
- Delegate a checklist based challenge and a parallel read only survey.
- Record one finding you accept and one you reject.

## Task Steps

### Step 1 - Enable the tool

- Enable `runSubagent` in your IDE chat tools.
- If you use custom agents or prompt files, add `runSubagent` to their `tools` frontmatter property.

**Expected evidence:** the tool appears as enabled.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- In VS Code, open the tools control in Copilot Chat and enable `runSubagent`.
- In JetBrains, enable Subagent under Copilot chat settings; at least one custom agent must be configured there.
- Copilot CLI provides built-in agents such as `explore`, `code-review`, `rubber-duck`, and `security-review`, so no profile is needed to delegate there.

</details>

### Step 2 - Write the handoff contract

Prepare a short prompt that carries the task reference, evidence to read, validation command, and output format.

**Expected evidence:** the prompt in your notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

```text
Task: challenge the proposed fix for preprocessing_tests.
Evidence: docs/review-checklist.md, src/preprocessing.cpp, its header,
and tests/test_preprocessing.cpp.
Validation: cmake --build --preset debug and ctest --preset debug --output-on-failure.
Output: at most three blocking findings, each with file and line.
State clearly when evidence is missing. Do not edit files.
```

The contract prevents a vague delegation that returns an opinion instead of evidence.

</details>

### Step 3 - Delegate the challenge

Send the handoff to a subagent or to the CLI `rubber-duck` agent.

**Expected evidence:** three or fewer findings with file and line.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- A useful challenge cites a missing bounds check, a signedness issue, or a weakened test.
- A finding with no file reference is not usable.
- If the agent proposes a patch, reject that part of the output and ask for findings only.
- A subagent uses the same tools and model as the main session, cannot create subagents, and does not pause for feedback.

</details>

### Step 4 - Delegate a parallel survey

Ask a second subagent to list every public header that mentions normalization, while the main session continues with its own question.

**Expected evidence:** the survey result plus a note on main context size.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- Prompt: "Use a subagent to list every file under `include/edge_inference/` that mentions normalization, with a one line description of each.
- Return only the list." The main session should not contain the intermediate file reads.
- That is the point of a separate context window.
- Compare with a run where you asked the same question in the main chat and observe how much intermediate detail appeared.

</details>

### Step 5 - Decide and record

Mark each finding accepted or rejected with a reason tied to the repository.

**Expected evidence:** a two row decision table.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

| Finding | Decision | Reason |
|---------|----------|--------|
| Missing bounds check at `src/preprocessing.cpp:NN` | Accepted | Line indexes without a size check |
| Rename a public function | Rejected | Breaks the interface in `include/edge_inference/` |

- A second opinion is a challenge, not an approval.
- Human review still decides what ships.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No repository code changes are expected in this task.

## Definition of Done

- [ ] `runSubagent` is enabled and used.
- [ ] One handoff contract includes task, evidence, validation, and output format.
- [ ] One challenge and one parallel survey were completed.
- [ ] Every finding has file and line or is marked unusable.
- [ ] One accepted and one rejected finding have reasons.
- [ ] No delegated output was merged without human checking.

## Summary

&emsp;✅&emsp;Enable and invoke a subagent with a handoff contract<br>
&emsp;✅&emsp;Use separate context for parallel read only work<br>
&emsp;✅&emsp;Treat a second opinion as a challenge, not approval
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Second opinion prompt:

```text
Use a subagent to argue against this diff using docs/review-checklist.md.
Cite file and line for every claim. State when evidence is missing.
Do not edit files.
```

Parallel read only investigation prompt:

```text
Use a subagent to list every public header in include/edge_inference/
that mentions normalization. Return the file paths and the exact symbol
names only. Do not edit files and do not propose a fix.
```

Triage record:

```markdown
| Finding | Outcome | Reason |
|---------|---------|--------|
| Missing constant input guard | accepted | Header contract and test line confirm it |
| Switch to a larger tensor type | rejected | No evidence in types.hpp or the contract |
```

- Delegate a second opinion on the `postprocessing_tests` fix using `docs/review-checklist.md` and file and line references, and in parallel delegate a read-only list of public headers mentioning normalization.
- Compare main context size with and without delegation.
- Record one accepted and one rejected finding with reasons.
- The final diff still passes build and CTest.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Copilot CLI](12-Copilot-CLI.md)
