# 4. Lab 1 - Customize Copilot

!!! abstract "About this Lab"
    **Time:** 11:35-12:20 (45 minutes). Create a version-controlled Copilot customization layer that reasons correctly about this C++ repository, then produce a plan for Lab 2.

## 1. Starting Point

- A clean checkout that builds, with `model_tests` passing and two seeded failures.
- The customization files already in `.github/` and `AGENTS.md`.
- Issue #1 in this repository.

## 2. Tasks

- [ ] Ask Copilot to map the repository: CMake targets, include graph, ownership patterns, Boost.Test suites, and the exact build and test commands.
- [ ] Review `.github/copilot-instructions.md`. Add missing local facts and remove generic statements.
- [ ] Extend `.github/instructions/cpp.instructions.md` and `cmake.instructions.md` so generated changes respect the existing conventions.
- [ ] Use `.github/prompts/plan-implementation.prompt.md` to plan Lab 2. Check every claim against repository files.
- [ ] Inspect `.github/agents/cpp-reviewer.agent.md` and the skill under `.github/skills/`. Confirm the tool scope is narrow.
- [ ] Ask the same question before and after customization and record what changed.

!!! tip "Good evidence"
    A useful before-and-after question is: "What does `preprocess` do, and which command proves it?" The after answer should name the real build and test commands without guessing.

## 3. Guardrails

- Do not fix the seeded defects in this lab.
- Do not claim dependencies the repository does not have.
- Do not add network downloads to CMake.
- Keep prose in ASCII hyphens, matching the repository convention.

## 4. Definition of Done

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- [ ] Customization files are committed on your lab branch.
- [ ] Every rule traces to something real in the repository.
- [ ] The Lab 2 plan names the files to change and the checks to run.
- [ ] The two seeded failures are still present.

## 5. Evidence to Record

- Before and after answers
- The customization diff
- The CTest summary line

---

**Next:** [Lab 02: Agent Mode and MCP](../02-Agent-Mode-and-MCP/README.md)
