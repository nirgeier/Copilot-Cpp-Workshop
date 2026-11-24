# Task - Prompt Files and Custom Instructions

!!! abstract "About this Task"
    Add a path scoped rule and a reusable prompt file, then show with a before and after answer how instructions change Copilot's output.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [11. Prompt Files and Custom Instructions](../../01-Copilot-Foundations/11-Lab-Prompt-Files-and-Custom-Instructions.md) |
| Scope | `.github/instructions/` and `.github/prompts/` only |
| Inputs | Two fresh chats, the same prompt, the shipped instruction files |
| Constraints | No C++ source changes. No secrets or personal paths in customization files. |
| Deliverable | Two customization files and a before and after comparison |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Distinguish automatic instructions from invoked prompt files.
- Keep path rules narrow and checkable.
- Write a prompt file with evidence sources and an output contract.

## The Task

- Create `.github/instructions/tests.instructions.md` scoped to `tests/**` and `.github/prompts/triage-cpp-failure.prompt.md`.
- Ask the same question with and without the prompt file and compare the answers against repository evidence.

## Task Steps

### Step 1 - Inventory the current layers

List the files that already shape Copilot behavior and the scope of each.

**Expected evidence:** a table with path and scope.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

| Path | Scope |
|------|-------|
| `.github/copilot-instructions.md` | Repository wide |
| `.github/instructions/cpp.instructions.md` | C++ sources and headers |
| `.github/instructions/cmake.instructions.md` | CMake files |
| `AGENTS.md` | All coding agents, not only Copilot |
| `.github/prompts/` | Invoked per interaction |

- Do not duplicate a rule already present.
- Add only what is missing.

</details>

### Step 2 - Add a path scoped rule

Create `.github/instructions/tests.instructions.md` with `applyTo: "tests/**"` and four short, checkable rules.

**Expected evidence:** the new file with a valid `applyTo` glob.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

```markdown
---
applyTo: "tests/**"
---

# Test rules for edge_inference

- Use Boost.Test in header-only mode. Do not add a test framework.
- Add one assertion that proves the reported behavior.
- Never delete, skip, or weaken an assertion to get a green run.
- Keep a seeded failure failing unless a task explicitly assigns its fix.
```

- A rule such as "write good tests" is not checkable.
- The rules above can be verified in review.

</details>

### Step 3 - Write the prompt file

Create `.github/prompts/triage-cpp-failure.prompt.md` with a description, evidence sources, steps, and an output contract.

**Expected evidence:** the new file with one task and a precise description.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

```markdown
---
description: Triage one failing CTest case in this repository and propose a scoped fix
---

# Triage one CTest failure

Task: ${input:test_name}

1. Run `ctest --preset debug --output-on-failure` and quote the exact assertion.
2. Read the public header before the implementation.
3. List at most three causes. Cite file and line for each.
4. Name the command that would disprove each cause.
5. Propose the smallest change. Do not edit in this step.
6. Output: failure, evidence, causes, disproof commands, scope.

Rules:
- Do not weaken a test or change expected values without a contract change.
- Do not add dependencies or network downloads.
- Keep prose in ASCII hyphens.
```

- Variable syntax differs between surfaces.
- If `${input:...}` is not supported in your IDE, replace it with a plain instruction to ask for the test name.

</details>

### Step 4 - Run the before and after comparison

- Use the identical prompt in two fresh chats.
- One has no prompt file selected.
- The other invokes the new prompt file with `preprocessing_tests`.

**Expected evidence:** two responses and a comparison table.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

Question: "Explain the `preprocessing_tests` failure and tell me which command proves it."

| Check | Without prompt file | With prompt file |
|-------|--------------------|------------------|
| Names the real test | Maybe | Yes |
| Quotes the exact assertion | No | Yes |
| Cites a file and line | Sometimes | Yes |
| Names `ctest --preset debug --output-on-failure` | Sometimes | Yes |
| Stops before editing | No | Yes |

- Mark claims without a file reference as guesses.
- Do not fix the defect in this task.

</details>

### Step 5 - Confirm the diff is customization only

Check that no C++ source or test file changed and that no credential appears in the new files.

**Expected evidence:** `git status` output limited to `.github/`.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Run `git status --short` and confirm only `.github/instructions/tests.instructions.md` and `.github/prompts/triage-cpp-failure.prompt.md` are new.
- If a chat agent edited production code, restore it.
- The seeded failures must still fail.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Expected state: two seeded failures and one passing `model_tests`.

## Definition of Done

- [ ] The scoped instruction file exists with `applyTo: "tests/**"`.
- [ ] The prompt file has a precise description, evidence sources, and an output contract.
- [ ] Both before and after answers are recorded with the identical prompt.
- [ ] Every claim without a file reference is marked as a guess.
- [ ] No C++ file was changed.
- [ ] No secret or personal path was added.

## Summary

&emsp;✅&emsp;Inventory instruction layers before adding a rule<br>
&emsp;✅&emsp;Add a scoped rule and an invokable prompt file<br>
&emsp;✅&emsp;Prove the effect with a before and after comparison
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Path rule in `.github/instructions/tests.instructions.md`:

```yaml
---
applyTo: "tests/**"
---
```

New `.github/prompts/triage-cpp-failure.prompt.md`:

```markdown
---
description: Triage one failing CTest case in this repository and propose a scoped fix
agent: cpp-planner
---

# Triage one failing CTest case

Task: ${input:test_name}

1. Run `ctest --preset debug --output-on-failure` and quote the exact assertion.
2. Read the public header before the implementation.
3. List at most three hypotheses with file and line references.
4. State the command that would disprove each hypothesis.
5. Propose the smallest change. Do not edit files in this step.
6. Output: failure, evidence, hypotheses, disproof commands, scope.

Rules:
- Do not weaken a test or change an expected value without a contract change.
- Do not add dependencies or network downloads.
```

- The shipped layers are `.github/copilot-instructions.md`, the `applyTo` scoped files in `.github/instructions/`, and the reusable files in `.github/prompts/`.
- Add a prompt file with one task, named evidence sources, and an output contract, for example triage one failing CTest case.
- Show a before and after answer after changing one line in `cpp.instructions.md`, and confirm the after answer names real files and the real CTest command.
- No secret or personal path goes into a prompt file; build and test state is unchanged.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - MCP and Connectors](09-MCP-and-Connectors.md)
