# Task - Agent Mode and Plan Mode

!!! abstract "About this Task"
    Plan a scoped change in read only mode, review the plan, then switch to agent mode and steer the implementation with approvals.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [13. Agent Mode and Plan Mode](../../01-Copilot-Foundations/13-Lab-Agent-Mode-and-Plan-Mode.md) |
| Scope | Issue #1 as written in the repository. No task assigns a new defect fix here. |
| Inputs | A task prompt, `CMakePresets.json`, the plan agent, the agent mode selector |
| Constraints | Plan agent must not edit. Commands need approval. No new dependencies. |
| Deliverable | A saved plan and an implementation transcript with approval decisions |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Use plan mode to research before any file changes.
- Review a plan against real files and validation commands.
- Steer agent mode with approvals, checkpoints, and bounded scope.

## The Task

- Ask the plan agent for a plan for issue #1.
- Verify its claims.
- If the plan is grounded, hand it to agent mode for a bounded implementation; if you are working through labs in order and already fixed the defect, use a documentation or test task instead so you do not change seeded state unexpectedly.

## Task Steps

### Step 1 - Enter plan mode

Select Plan in the mode selector and submit a task prompt that forbids edits.

**Expected evidence:** the exact prompt used.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

```text
Plan a fix for issue #1 in this repository. Use read only tools only.
Find the failing CTest case, read the public header before the source,
name the exact files to change, list the build and test commands from
CMakePresets.json, and state open questions. Do not edit anything.
```

- Plan mode is available in VS Code, JetBrains, Xcode, and Eclipse.
- It is not available in Visual Studio at the time of writing.
- The plan agent does not change code until you approve the plan.

</details>

### Step 2 - Verify the plan

- Check every repository claim against a file.
- Mark each as verified or guessed.

**Expected evidence:** the plan plus a verification table.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

| Plan claim | Check |
|------------|-------|
| Failing test is `postprocessing_tests` | Rerun the CTest entry |
| Header is under `include/edge_inference/` | Open the path |
| Build command is `cmake --preset debug` | Read `CMakePresets.json` |
| New dependency is needed | Should be false; reject if true |

- Answer the open questions before implementation.
- Do not start if the plan still guesses about files or commands.

</details>

### Step 3 - Switch to agent mode

- Choose Agent in the mode selector and hand over the approved plan.
- Approve or reject each proposed terminal command.

**Expected evidence:** a transcript with at least one approval decision.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- Reject a command that is not in the plan, for example a network install or a broad delete.
- By default commands need approval, but administrator or editor settings can allow some to run automatically.
- If the agent drifts from the named files, send a follow up prompt to redirect it before it finishes.
- Review streamed edits and undo any that exceed the scope.

</details>

### Step 4 - Close with validation and review

Run build and test, then ask for a code review of the diff.

**Expected evidence:** CTest summary line and review comments.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- Ask Copilot to review only the diff against `docs/review-checklist.md`.
- A passing test run is not approval.
- State which seeded failures changed and why.
- If you chose a documentation task instead, all seeded state should be unchanged.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Record the CTest summary line and note which tests you expected to pass.

## Definition of Done

- [ ] A plan was produced and saved with the workshop notes.
- [ ] Every plan claim was marked verified or guessed.
- [ ] Open questions were answered before implementation.
- [ ] At least one command approval was an explicit decision.
- [ ] The final diff matches the named file list.
- [ ] Build, test, and review evidence are attached.

## Summary

Research in plan mode before any edits<br>
Verify plan claims against real files<br>
Steer agent mode with approvals and bounded scope
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Plan prompt submitted in read only mode:

```text
Plan a fix for issue #1 in this repository. Use read only tools only.
Find the failing CTest case, read the public header before the source,
name the exact files to change, list the build and test commands from
CMakePresets.json, and state open questions. Do not edit anything.
```

Validation gates recorded with the plan:

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
git diff --check
```

- Produce and save a plan that cites real file paths, names the failing test and the preset commands, and lists open questions.
- Reject any plan that guesses.
- Switch to Agent mode with that plan, confirm or reject each command, undo edits that drift from the file list, and request a code review on completion.
- Record the seeded test state before and after and apply `docs/review-checklist.md` to the final diff.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Subagents and Delegation](11-Subagents-and-Delegation.md)
