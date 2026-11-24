# Project - Build a Workshop Repository

!!! abstract "About this Task"
    - Build a complete C++17 git repository from scratch using the Copilot customization layer from this workshop.
    - The repository contains build presets, a library, a CLI, Boost.Test suites, prompt files, custom agents, a skill, hooks, and recorded evidence.
    - This is the capstone task. It combines the theory and practice from every section.

## Solution download

The complete `mini_infer` solution is available as a single archive. It contains the
C++17 library, CLI, Boost.Test suites, demo, Docker setup and documentation.

[Download mini_infer-solution.zip](../../assets/solutions/mini_infer-solution.zip){ .md-button .md-button--primary }

Regenerate the archive with `./scripts/package-solution.sh` inside `mini_infer/`. The
script also refreshes the copy published on this site.

## 1. Task Definition

| Field | Details |
|-------|---------|
| Lab | All sections |
| Scope | A new git repository outside the starter checkout |
| Inputs | This workshop repository as the reference, Copilot CLI or IDE, an approved MCP server if policy allows |
| Constraints | No secrets, no model binaries, no network downloads in CMake, no weakening tests to make them pass |
| Deliverable | A committed git repository that builds, tests clean, and contains the full customization layer plus an evidence log |
| Validation | Configure, build, CTest, sanitizers where available, and a CLI run against a sample file |

## 2. Goals

- Apply repository guidance so generated code follows real project conventions.
- Use prompt files, plan mode, custom agents, a skill, hooks, and subagents to write C++ code.
- Produce a repository a reviewer can clone, build, and test without local secrets.
- Record evidence for every claim, including an AI generated change that was rejected.

## 3. Project Brief

Create a small offline C++17 project named `mini_infer`. It normalizes a list of numbers and finds the index of the largest value. Keep the scope tiny so the customization layer, not the algorithm, is the point.

```text
mini_infer/
├── .github/
│   ├── agents/
│   │   ├── cpp-planner.agent.md
│   │   └── cpp-reviewer.agent.md
│   ├── hooks/project-hooks.json
│   ├── instructions/
│   │   ├── cpp.instructions.md
│   │   └── cmake.instructions.md
│   ├── prompts/
│   │   ├── plan-implementation.prompt.md
│   │   ├── generate-tests.prompt.md
│   │   └── review-diff.prompt.md
│   ├── skills/add-boost-test-suite/SKILL.md
│   └── copilot-instructions.md
├── AGENTS.md
├── CMakeLists.txt
├── CMakePresets.json
├── PROJECT_NOTES.md
├── README.md
├── data/sample.txt
├── include/mini_infer/
│   ├── normalize.hpp
│   └── argmax.hpp
├── src/
│   ├── normalize.cpp
│   └── argmax.cpp
├── cli/main.cpp
└── tests/
    ├── test_normalize.cpp
    └── test_argmax.cpp
```

- `normalize` maps values into `[0, 1]` using the observed range. A constant input stays finite.
- `argmax` returns the index of the largest value and starts at index zero.
- The CLI reads a whitespace separated list from `data/sample.txt` and prints both results.
- All tests pass in the final repository. This is different from the seeded starter repository.

## 4. Steps

### Step 1 - Create the repository skeleton

- Run `git init`, create a branch, and add the folder tree shown in the brief.
- Add a `.gitignore` for `build/`, logs, and local settings.
- Write a `README.md` that names the build and test commands.

**Expected evidence:** `git status` on a named branch and the first commit hash.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

```sh
git init mini-infer-workshop
cd mini-infer-workshop
git switch -c project/copilot-workshop
mkdir -p include/mini_infer src cli tests data \
  .github/agents .github/hooks .github/instructions .github/prompts \
  .github/skills/add-boost-test-suite .github/copilot
```

Add a `.gitignore` with at least:

```text
build/
logs/
.github/copilot/settings.local.json
```

</details>

### Step 2 - Write the repository guidance

- Create `AGENTS.md` with the real build and test commands, C++ rules, and validation gates.
- Create `.github/copilot-instructions.md` for repository wide behavior.
- Add path scoped rules for C++ and CMake files.
- Every rule must point to a file, command, or policy that exists in this new repository.

**Expected evidence:** the guidance diff and a short note on which local fact each rule came from.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

Ground the guidance in files you just created:

| Rule | Source |
|------|--------|
| Use C++17 and no third party libraries | `CMakeLists.txt` |
| Export compile commands | `CMakePresets.json` |
| Header first, check bounds and signedness | `include/mini_infer/` |
| Add a Boost.Test case for each behavior | `tests/` |
| Never add a network download | `CMakeLists.txt` |

Avoid generic statements such as "write clean code". They do not change an answer.

</details>

### Step 3 - Plan the implementation with AI

- Start in plan mode and invoke `.github/prompts/plan-implementation.prompt.md`.
- Ask for a plan that names files, commands, tests, and open questions.
- Check every claim against the files you created. Reject any plan that invents a dependency or a command.
- Save the accepted plan in `PROJECT_NOTES.md`.

**Expected evidence:** the prompt, the plan, and a list of claims marked verified or rejected.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

A grounded plan names `src/normalize.cpp`, `src/argmax.cpp`, `tests/test_normalize.cpp`, `tests/test_argmax.cpp`, `CMakeLists.txt`, and `CMakePresets.json`. It names `cmake --preset debug`, `cmake --build --preset debug`, and `ctest --preset debug --output-on-failure` as the checks. A plan that adds FetchContent or a JSON dependency is rejected.

</details>

### Step 4 - Write C++ with the custom agents

- Use the read only planner to refine the file list.
- Switch to agent mode and implement the library and CMake files.
- Confirm or reject each command. Undo edits that drift from the plan.
- Hand the diff to the read only reviewer and fix only grounded findings.

**Expected evidence:** the accepted diff, the reviewer output, and the build and test result after the review.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

Keep the API small:

```cpp
// include/mini_infer/normalize.hpp
#pragma once
#include <vector>

namespace mini_infer {
bool normalize(std::vector<double>& values);
}
```

```cpp
// include/mini_infer/argmax.hpp
#pragma once
#include <cstddef>
#include <vector>

namespace mini_infer {
std::size_t argmax(const std::vector<double>& values);
}
```

`normalize` returns `false` for an empty or constant input and leaves the vector unchanged. `argmax` returns zero for an empty vector and uses `<` comparisons so the first maximum wins. Both functions avoid integer overflow by using `std::size_t` for indexes. The reviewer must not have write tools.

</details>

### Step 5 - Author and use an agent skill

- Create `.github/skills/add-boost-test-suite/SKILL.md` with a precise `name` and `description`.
- The procedure must name the header, the test folder, the Boost.Test macro, the CMake entry, and the validation commands.
- Do not add `shell` or `bash` to `allowed-tools`.
- Ask an unrelated question and then a test generation question. Record whether the skill loads.

**Expected evidence:** the skill file and two prompt excerpts.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

The description names the repository and the trigger, for example: "Add a Boost.Test case to the mini_infer C++ project. Use when a new behavior needs a regression test." An unrelated question about the README must not load the skill.

</details>

### Step 6 - Generate tests with the skill

- Invoke the skill for the `normalize` and `argmax` behaviors.
- Cover a normal range, a constant input, an empty input, and a tie for the maximum.
- Build and run CTest. All tests must pass.
- Reject any suggestion that weakens an assertion.

**Expected evidence:** the test files, the CTest summary line, and one rejected suggestion with the checklist item it failed.

<details class="note" markdown="1">
<summary>Suggested solution - Step 6</summary>

Register the suites in `CMakeLists.txt` with `enable_testing()`, one executable per test file, and `add_test(...)`. Keep assertions on exact values and indexes. A suggestion that deletes a failing assertion is rejected under the rule against weakening tests.

</details>

### Step 7 - Add hooks and prove enforcement

- Add `.github/hooks/project-hooks.json` with a `preToolUse` guard and a `postToolUse` audit entry.
- The guard denies destructive shell commands and edits under `build/`.
- The audit entry appends selected fields to `logs/tool-results.jsonl`.
- Show one denied command and one allowed command.

**Expected evidence:** the hook file, the deny reason, and two log lines.

<details class="note" markdown="1">
<summary>Suggested solution - Step 7</summary>

Use `matcher: "bash"` for the guard and `matcher: "edit|create"` for the generated path check. Write the decision as `{"permissionDecision":"deny","permissionDecisionReason":"..."}` on stdout. Add `logs/` to `.gitignore` and keep the audit script to non sensitive fields such as `toolName` and `cwd`.

</details>

### Step 8 - Delegate the CLI to a subagent

- Give a subagent a narrow handoff contract: write `cli/main.cpp`, read only the two public headers and `data/sample.txt`, and do not edit tests.
- Review the result with the custom reviewer before accepting it.
- Run the CLI against the sample file.

**Expected evidence:** the handoff contract, the subagent output, the review, and the CLI output.

<details class="note" markdown="1">
<summary>Suggested solution - Step 8</summary>

The contract states the input format, the two functions to call, the output format, and the forbidden files. The CLI reads whitespace separated doubles from the path given as its first argument, prints the normalized vector and the argmax index, and returns a nonzero exit code on a read error.

</details>

### Step 9 - Configure MCP under least privilege

- Only if policy allows, configure one read only MCP server, for example the GitHub server.
- Classify each exposed tool as needed, useful, or unnecessary.
- Grant only the needed tools and confirm no token appears in a file or prompt.

**Expected evidence:** the tool classification note and a boundary test showing an unneeded tool rejected.

<details class="note" markdown="1">
<summary>Suggested solution - Step 9</summary>

For a project that does not use issues, the correct answer may be to configure no MCP server at all. If one is approved, keep it read only and store credentials in the approved secret store, never in `.github/` or `PROJECT_NOTES.md`.

</details>

### Step 10 - Validate and commit

- Run the full validation sequence and attach the output to `PROJECT_NOTES.md`.
- Confirm that no generated file, secret, or personal path is staged.
- Commit the repository with a clear message.

**Expected evidence:** the final commit hash and the validation output.

<details class="note" markdown="1">
<summary>Suggested solution - Step 10</summary>

The notes contain the configure, build, CTest, sanitizer, and CLI output plus the accepted and rejected AI suggestions. `git status --short` is clean before the final commit. The repository has no network downloads in CMake.

</details>

## 5. Validation

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure

cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure

./build/debug/mini_infer_cli data/sample.txt
```

- Expected state: every test passes in both presets and the CLI prints the normalized values and the argmax index.
- If sanitizers are unavailable locally, record that and keep the debug results.

## 6. Definition of Done

- [ ] The repository clones and builds without secrets or network downloads.
- [ ] The library, CLI, and Boost.Test suites are present and all tests pass.
- [ ] `AGENTS.md`, instructions, prompts, agents, a skill, and hooks are committed and grounded in this repository.
- [ ] C++ code was written with AI, reviewed by a narrow reviewer agent, and backed by accepted and rejected evidence.
- [ ] The skill loads for a matching task and not for an unrelated one.
- [ ] A hook denied one action and the deny reason was recorded.
- [ ] MCP tools were classified and granted least privilege, or MCP was intentionally omitted.
- [ ] `PROJECT_NOTES.md` contains the plan, evidence, and validation output.
- [ ] No generated file, secret, model binary, or personal path was committed.

## 7. Evidence to Record

- The accepted plan and the claims that were rejected as ungrounded.
- The C++ diff, the reviewer output, and one rejected AI suggestion.
- Two prompt excerpts for skill loading and one denied hook decision.
- The subagent handoff contract and its result.
- The configure, build, CTest, sanitizer, and CLI output.

## 8. Summary

Create a buildable C++ repository from scratch with presets and tests<br>
Use the customization layer to write and review code with AI<br>
Prove that skills, hooks, agents, and least privilege tools work as intended

**Back:** [Tasks (Overview)](../README.md)
