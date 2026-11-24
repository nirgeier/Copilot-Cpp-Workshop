# Task - Create an Agent Skill

!!! abstract "About this Task"
    - Package a repeatable C++ triage procedure as an agent skill.
    - You will inspect the shipped skill, author a new one, and prove that Copilot loads it only for a matching task.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [5. Agent Skills](../../01-Copilot-Foundations/05-Lab-Agent-Skills.md) |
| Scope | Files under `.github/skills/` only. No C++ source changes. |
| Inputs | `.github/skills/add-boost-test-suite/SKILL.md`, two chat prompts, current CTest output |
| Constraints | `SKILL.md` naming rules, precise `description`, no pre-approved shell, no secrets |
| Deliverable | One new skill folder, the skill diff, and a before-and-after answer pair |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Explain how Copilot decides to load a skill.
- Write frontmatter that is valid and a description that matches the intended task.
- Keep tool permissions narrow and verify the result with evidence.

## The Task

- Create `.github/skills/cpp-defect-triage/SKILL.md`.
- It must describe how to triage a failing CTest case without editing code.
- Then show that Copilot follows it for a matching prompt and does not load it for an unrelated prompt.

## Task Steps

### Step 1 - Inspect the existing skill

- Read `.github/skills/add-boost-test-suite/SKILL.md`.
- List each frontmatter key and map every procedure step to a file or command that exists in this repository.

**Expected evidence:** a short table with skill step and repository file.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- Frontmatter keys: `name: add-boost-test-suite` and `description`.
- There is no `allowed-tools`, so Copilot must ask before running terminal commands.

| Skill step | Repository file |
|------------|-----------------|
| Read header and implementation | `include/edge_inference/`, `src/` |
| Create `test_<area>.cpp` | `tests/` |
| Use `BOOST_AUTO_TEST_SUITE` | Existing Boost.Test suites |
| Add target to CMake | `CMakeLists.txt` |
| Configure, build, test | `CMakePresets.json` |

</details>

### Step 2 - Author the new skill

- Create the folder and `SKILL.md`.
- Use lowercase hyphenated `name`, a description that names the repository and the task, and a numbered procedure with an output contract.

**Expected evidence:** the file exists with valid YAML frontmatter.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

```markdown
---
name: cpp-defect-triage
description: Triage a failing CTest case in the edge_inference C++ repository. Use when a build or test fails and the cause is not yet known.
---

# C++ defect triage

1. Reproduce with the commands in `CMakePresets.json`.
2. Capture the failing assertion, file, and line. Do not paraphrase.
3. Read the public header before the implementation.
4. List at most three causes with evidence for each.
5. State the command that would disprove each cause.
6. Propose the smallest change. Do not edit until the cause is confirmed.

## Rules

- Never weaken a test.
- Do not add a dependency or a network download.
- Keep prose in ASCII hyphens.
```

- The description names both the repository and the trigger, so Copilot can select it.
- No `allowed-tools` field is present.

</details>

### Step 3 - Prove selective loading

- Ask an unrelated question, then ask a triage question.
- Record whether the skill appears in Copilot's context.

**Expected evidence:** two prompt and response excerpts.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

Unrelated prompt: "Summarize the purpose of the benchmark target." The skill should not load.

- Matching prompt: "Triage the failing `preprocessing_tests` case in this repository.
- Do not edit code." The skill should load and the answer should follow the six numbered steps, cite `src/preprocessing.cpp`, and name `ctest --preset debug --output-on-failure`.
- If the skill never loads, tighten the trigger words in `description`.
- If it loads for everything, narrow the description.

</details>

### Step 4 - Add a supporting resource

Add one small reference file to the skill folder and reference it by exact relative path from `SKILL.md`.

**Expected evidence:** the skill folder contains `SKILL.md` plus one resource, and the body links to it.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- Create `.github/skills/cpp-defect-triage/checklist.md` with this full content:

```markdown
# Triage gate

Copy this gate into the answer before proposing a fix.

- [ ] Every claimed API exists in the included headers. No invented STL calls.
- [ ] Indexing is bounds checked before use.
- [ ] Integer widths and signedness are safe for the input sizes in `data/`.
- [ ] `CMakeLists.txt` and presets still configure without network access.
- [ ] No test was deleted, skipped, or weakened to make the run green.
- [ ] Build and `ctest --preset debug --output-on-failure` output is attached.
- [ ] No secret, client data, or model binary was added.
- [ ] Text uses ASCII hyphens, never em dashes.
```

- In `SKILL.md`, add: "Before proposing a fix, read `checklist.md` in this skill folder and include the gate in the output." Copilot discovers all files in the skill directory, so no special registration is needed.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- Expected state: `model_tests` passes, `preprocessing_tests` and `postprocessing_tests` still fail.
- No C++ file changed.

## Definition of Done

- [ ] The skill folder contains a correctly named `SKILL.md` and one referenced resource.
- [ ] `name` is unique, lowercase, and hyphenated. `description` names the trigger.
- [ ] Neither `shell` nor `bash` appears in `allowed-tools`.
- [ ] One matching and one non-matching prompt were recorded.
- [ ] No secret, token, or personal path was committed.
- [ ] The two seeded failures are unchanged.

## Summary

&emsp;✅&emsp;Inspect a shipped skill and map it to repository files<br>
&emsp;✅&emsp;Author a scoped skill with a precise description<br>
&emsp;✅&emsp;Demonstrate selective loading with two prompt excerpts
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

`.github/skills/cpp-defect-triage/SKILL.md`:

```markdown
---
name: cpp-defect-triage
description: Triage a failing CTest case in the edge_inference C++ repository. Use when a build or test fails and the cause is not yet known.
metadata:
  author: workshop
  version: "1.0"
---

# C++ defect triage

1. Reproduce with the presets in `CMakePresets.json`.
2. Quote the failing assertion, file, and line. Do not paraphrase.
3. Read the public header before the implementation.
4. List at most three causes with file and line evidence.
5. State the command that would disprove each cause.
6. Propose the smallest change. Do not edit until a cause is confirmed.

## Rules

- Never weaken a test.
- Do not add a dependency or a network download.
- Keep prose in ASCII hyphens.
```

The optional `metadata` values are quoted strings. No `allowed-tools` entry is present, so no shell is pre-approved.

- One valid solution creates `.github/skills/cpp-defect-triage/SKILL.md` with `name: cpp-defect-triage` and a description naming failing CTest cases in `edge_inference`.
- The body reproduces the failure with the preset commands, quotes the assertion, reads the header before the implementation, lists at most three causes with evidence, and stops before editing.
- It adds a supporting checklist referenced by relative path.
- No `shell` tool is allowed.
- The skill does not load for unrelated questions and does load for the `preprocessing_tests` prompt; both chats and the unchanged build and test output are recorded.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Create a Custom Agent](03-Custom-Agents.md)
