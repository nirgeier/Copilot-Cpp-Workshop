# Task - Configure Agent Guardrails

!!! abstract "About this Task"
    - Agent mode can edit files and run commands.
    - You will keep approval checkpoints on, run one small supervised edit, and use keep or undo to inspect the result.
    - No seeded defect is in scope.

## 1. Set the Starting Controls

Before you open agent mode, confirm these settings in your approved Copilot surface:

| Control | Setting for this task |
|---------|----------------------|
| Tool approval | On for edits and terminal commands |
| Auto-approval rules | None beyond read-only commands |
| Request limit | Low enough to stop a runaway session |
| Todo list | Enabled for multi-step work |

!!! warning "Do not pre-approve the shell"
    - Automatic shell approval lets an unreviewed command run.
    - Keep the confirmation step for anything that changes the working tree.

## 2. Give a Narrow Task

- Ask the agent to add one sentence to `models/README.md` stating that no model binary is committed.
- The file already documents that rule, so the edit is small and easy to inspect.

Use a prompt with an acceptance criterion:

```text
Add one sentence to models/README.md that says no model binary is committed.
Change only that file. Do not run build or test commands. Show me the diff before
I accept it.
```

## 3. Inspect the Checkpoints

- [ ] The agent proposed a plan or a single edit before touching the file.
- [ ] Every tool call that would write a file asked for approval.
- [ ] Review the todo list. Compare it with the acceptance criterion.
- [ ] Reject the first edit if it changes more than one file.
- [ ] Accept a corrected edit and record what changed between attempts.

## 4. Use Keep or Undo

- Ask for a second, deliberately poor edit, for example one that rewrites the whole file.
- Reject it with undo.
- Confirm the working tree returns to the accepted state.

```sh
git diff -- models/README.md
git status --short
```

The final diff must contain only the accepted sentence.

## 5. Feed a Real Failure Back

Ask the agent to run `ctest --preset debug --output-on-failure` and to explain the two failing suites from the raw output.

- Paste the assertion and file reference, not a summary.
- Ask it to identify which suites are seeded.
- Stop it before it proposes a fix.

!!! warning "Never weaken a test"
    If the agent changes an assertion or deletes a test to get a green run, undo the edit and record it as a failed checkpoint.

## 6. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Agent edited several files | Acceptance criterion was too broad | Restate the single file in the prompt |
| No approval prompt appeared | Auto-approval rule is too wide | Remove the rule and rerun |
| Agent guessed the test state | It did not see real output | Paste the exact CTest lines |
| Agent started a defect fix | Prompt did not say stop | Undo and restate the boundary |

## 7. Definition of Done

- [ ] Tool approval stayed on for edits and commands.
- [ ] One small edit was accepted and one was rejected with undo.
- [ ] The final diff contains only `models/README.md`.
- [ ] The two seeded suites were identified from real CTest output.
- [ ] No test was changed and no seeded defect was fixed.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

## 8. Summary

&emsp;✅&emsp;Keep approval checkpoints on during agent work<br>
&emsp;✅&emsp;Use keep and undo to inspect a proposed edit<br>
&emsp;✅&emsp;Ground the agent with real test output

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

The accepted one sentence diff in `models/README.md`:

```diff
+ The workshop does not commit a model binary. Each participant uses the
+ approved hosted model through Copilot.
```

Prompt used when pasting a real failure back into the session:

```text
This is the raw ctest output, pasted verbatim. Identify which test is a
seeded failure and which assertion is expected to fail. Do not propose a
fix and do not edit any file. State your evidence as file and line.
```

Expected outcome:

- Approval prompts appeared for the edit to `models/README.md`; no shell command ran automatically.
- The accepted diff is one sentence stating that no model binary is committed. The deliberately poor rewrite was rejected with undo.
- `git diff -- models/README.md` shows only that sentence.
- A pasted `ctest` failure led the agent to identify `preprocessing_tests` and `postprocessing_tests` as seeded, with no proposed fix.

If the agent weakened a test, undo it and record the checkpoint failure.

</details>

---

**Back:** [Tasks (Overview)](../README.md)
