# Task - Ground Context with Instructions and Prompts

!!! abstract "About this Task"
    - Copilot answers only from the context you give it.
    - You will inspect the context files already in this repository, add one path scoped rule, and write a prompt file.
    - Then you will compare two answers with evidence.

## 1. Inventory the Current Context

List the files that already shape Copilot behavior in this repository:

| Path | Role |
|------|------|
| `AGENTS.md` | Repository rules for coding agents |
| `.github/copilot-instructions.md` | Repository-wide Copilot instructions |
| `.github/instructions/cpp.instructions.md` | C++ specific rules |
| `.github/instructions/cmake.instructions.md` | CMake specific rules |
| `.github/prompts/` | Reusable prompt files |

- Read each one.
- Note any rule that is already covered so you do not duplicate it.

## 2. Add a Path Scoped Rule

- Create `.github/instructions/tests.instructions.md`.
- Scope it to test files and keep it short:

```markdown
---
applyTo: "tests/**"
---

# Test rules for edge_inference

- Use Boost.Test in header-only mode. Do not add a test framework.
- Add one assertion that proves the reported behavior, not a broad smoke check.
- Never delete, skip, or weaken an assertion to get a green run.
- Keep a failing seeded test failing unless the task explicitly assigns its fix.
- Cite the source file and the failing assertion in the change description.
```

!!! tip "Rules must be checkable"
    - A rule such as "write good tests" cannot be verified.
    - A rule that names Boost.Test and forbids weakening assertions can be checked in review.

## 3. Write a Prompt File

Create `.github/prompts/triage-failing-test.prompt.md`:

```markdown
---
description: Triage one failing CTest case in the edge_inference repository without editing code
---

# Triage a failing test

1. Read `AGENTS.md` and `.github/copilot-instructions.md` first.
2. Run the failing test with `ctest --preset debug --output-on-failure -R <suite>`.
3. Quote the assertion, file, and line from the real output.
4. Read the public header before the implementation.
5. List at most three causes with repository evidence for each.
6. Name the check that would disprove each cause.
7. Stop before editing. Propose the smallest change as a plan.
```

- Use a precise `description`.
- Copilot selects a prompt file from that text.

## 4. Run a Before and After Comparison

- [ ] Ask Copilot to explain the `preprocessing_tests` failure with no prompt file selected. Record the answer.
- [ ] Invoke `triage-failing-test` with the same question. Record the answer.
- [ ] Compare both against `docs/review-checklist.md`.
- [ ] Mark every claim that cites a real file and line.
- [ ] Mark every claim that is a guess.

- Do not fix the defect in this task.
- The goal is to observe how context changes the answer.

## 5. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| The new rule is ignored | `applyTo` does not match the file path | Check the glob against `tests/**` |
| The prompt is never offered | Description is vague | Name the repository and the task |
| Copilot invents an API | No instruction to read headers first | Keep the header before implementation rule |
| The diff contains a defect fix | Prompt did not say stop before editing | Restore the seeded failure and rerun |

## 6. Definition of Done

- [ ] `.github/instructions/tests.instructions.md` exists and is scoped to `tests/**`.
- [ ] `.github/prompts/triage-failing-test.prompt.md` has a unique `description`.
- [ ] Both before and after answers are recorded with the exact prompt used.
- [ ] The comparison cites `docs/review-checklist.md`.
- [ ] No C++ source or test file was changed.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Expected state: the same two seeded failures as in the setup task.

## 7. Summary

&emsp;✅&emsp;Inventory the instructions and prompts already in the repository<br>
&emsp;✅&emsp;Add a scoped rule and a selectable prompt file<br>
&emsp;✅&emsp;Compare answers using repository evidence

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

`.github/instructions/tests.instructions.md`:

```yaml
---
applyTo: "tests/**"
---
```

```markdown
# Boost.Test rules for this repository

- One assertion per observable behavior.
- Cover a happy path, a boundary, and a failure path where relevant.
- Never delete or weaken an assertion to get a green run.
- Name the exact header and source that define the behavior.
```

`.github/prompts/triage-failing-test.prompt.md`:

```markdown
---
description: Triage one failing CTest case in this repository and propose a scoped fix
---

# Triage one failing CTest case

1. Run `ctest --preset debug --output-on-failure`.
2. Quote the exact assertion with file and line.
3. List at most three causes, each citing a file.
4. Stop before editing anything.
5. Output: assertion, evidence, causes, smallest next check.
```

1. The existing context is `AGENTS.md`, `.github/copilot-instructions.md`, `.github/instructions/cpp.instructions.md`, `.github/instructions/cmake.instructions.md`, and the files in `.github/prompts/`.
2. A scoped `.github/instructions/tests.instructions.md` uses `applyTo: "tests/**"` and names Boost.Test, one assertion per behavior, and the no-weakening rule.
3. `.github/prompts/triage-failing-test.prompt.md` has a precise `description` and an output contract: quote the assertion, cite files, list at most three causes, and stop before editing.
4. The before answer is generic; the after answer names `src/preprocessing.cpp`, `tests/test_preprocessing.cpp`, and the exact CTest command. Mark any claim without a file reference as a guess.

- The seeded failures must still fail.
- No C++ file changes.

</details>

---

**Back:** [Tasks (Overview)](../README.md)
