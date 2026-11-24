# Task - Copilot CLI

!!! abstract "About this Task"
    Run the workshop workflow from the terminal: trusted session, file context, plan mode, scoped review, and careful permission choices.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [15. Copilot CLI](../../01-Copilot-Foundations/15-Lab-Copilot-CLI.md) |
| Scope | Local CLI session in this repository. No persistent approvals for destructive commands. |
| Inputs | `CMakePresets.json`, the failing CTest output, the diff to review |
| Constraints | Session only trust. No token pasted into the CLI. No saved `rm` approval. |
| Deliverable | A session transcript with plan, review, and permission decisions |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Start a CLI session with explicit trust scope.
- Use `@` file context, plan mode, and `/review`.
- Understand the cost of saved tool approvals.

## The Task

- Start Copilot CLI in the workshop repository with session only trust.
- Ask about the build presets, plan a task, implement nothing, run `/review`, and challenge the result with a built-in agent.

## Task Steps

### Step 1 - Start a trusted session

- Run `copilot` from the repository root and choose session only trust.
- Log in if prompted.

**Expected evidence:** the trust choice recorded in your notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

```sh
cd /Users/nirg/repositories/Copilot-Cpp-Workshop
copilot
```

- Choose "Yes" for this session only.
- Copilot may read, modify, and execute files in and below the folder.
- Do not choose the remember option unless the location is always safe.
- If not logged in, use `/login`.

</details>

### Step 2 - Add file context

Use `@CMakePresets.json` to ask which presets exist.

**Expected evidence:** an answer that names `debug`, `release`, and `sanitizers`.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- Prompt: "Using @CMakePresets.json, list each configure preset and what it enables.
- Which preset produces `compile_commands.json`?" The answer should name the three presets, note that `base` is hidden and exports compile commands, and that `sanitizers` enables `ENABLE_SANITIZERS`.
- If the file is not attached, the answer will be generic.

</details>

### Step 3 - Use plan mode

- Press Shift+Tab to enter plan mode.
- Ask for a plan for the failing `postprocessing_tests` case.

**Expected evidence:** a plan with named files and validation commands.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- Prompt: "Plan a fix for the failing `postprocessing_tests` case.
- Name the header, source, and test files, and list the validation commands.
- Do not edit." Check that the plan names `src/postprocessing.cpp`, its header, `tests/test_postprocessing.cpp`, and `ctest --preset debug --output-on-failure`.
- Exit plan mode without implementing.

</details>

### Step 4 - Review changes with a slash command

- Run `/review` scoped to the changed files from an earlier task.
- Approve only the commands needed to inspect the diff.

**Expected evidence:** review feedback and a command approval decision.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- Type `/review` with an optional path such as `src/preprocessing.cpp`.
- Copilot may propose a command to inspect the diff.
- Read the command before choosing Yes.
- Read each comment and classify it as grounded or unproven against `docs/review-checklist.md`.

</details>

### Step 5 - Challenge and stop cleanly

- Ask the CLI `rubber-duck` agent to argue against the diff.
- Stop a running operation with Esc twice if needed.
- Do not save a persistent approval for a destructive command.

**Expected evidence:** one challenge finding and the exit state.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Prompt: "Use rubber-duck to argue against this diff using `docs/review-checklist.md`.
- Cite file and line." If a tool permission prompt offers "don't ask again" for `rm`, choose No for this session.
- Saved approvals persist for the directory and future sessions.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No C++ changes are expected if you did not implement the plan.

## Definition of Done

- [ ] Session trust was set to session only.
- [ ] An `@` file reference was used and the answer cited that file.
- [ ] Plan mode was used before any implementation.
- [ ] `/review` feedback was classified against the checklist.
- [ ] No persistent approval was saved for a destructive command.
- [ ] Build and test output is attached.

## Summary

&emsp;✅&emsp;Start CLI sessions with narrow trust<br>
&emsp;✅&emsp;Use `@` context, plan mode, and `/review` deliberately<br>
&emsp;✅&emsp;Keep saved approvals out of destructive commands
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Session commands used in the terminal:

```sh
cd /path/to/Copilot-Cpp-Workshop
copilot
# Choose "Yes (this session only)" when asked to trust the folder
```

```text
> @CMakePresets.json which presets exist and what does each enable?
> Shift+Tab, then: plan a scoped fix for postprocessing_tests. Do not edit.
> /review src/postprocessing.cpp
> Use rubber-duck to argue against this diff.
```

- Start a session with session only trust, add `@CMakePresets.json` to context, enter plan mode for `postprocessing_tests`, then implement only the scoped fix.
- Run `/review` and classify the feedback as grounded or unproven.
- Ask `rubber-duck` to argue against the diff and use rollback if the review is unconvincing.
- Do not save persistent approval for a destructive command.
- Build and test gates pass on the final diff.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Hooks and Guardrails](13-Hooks-and-Guardrails.md)
