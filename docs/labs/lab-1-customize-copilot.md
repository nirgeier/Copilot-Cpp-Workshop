# Lab 1 - Customize Copilot for the workshop repository

Aligned with Module 4 of the syllabus. 45 minutes.

## Starting point

A clean checkout, a working C++17 build, and the two intentional test failures
listed in `docs/setup.md`.

## Tasks

1. Ask Copilot to map the repository: CMake targets, the include graph,
   ownership patterns, the test suites, and the exact build and test commands.
2. Review `.github/copilot-instructions.md`. Add the local conventions that are
   missing, and remove anything that is generic or untrue for this repository.
3. Extend the path-specific rules under `.github/instructions/` so changes to
   headers and CMake files respect the existing style and validation gates.
4. Use `.github/prompts/plan-implementation.prompt.md` to produce a short plan
   for Lab 2. Check every claim against the files in the repository.
5. Inspect `.github/agents/cpp-reviewer.agent.md` and the skill under
   `.github/skills/`. Confirm the tool scope is narrow and the checklist is
   specific.
6. Ask the same question before and after customization and record what
   changed.

## Definition of done

- The customization files are committed on a lab branch.
- Each rule can be traced to something real in this repository.
- The plan for Lab 2 names the files to change and the checks to run.
- No prompt or instruction claims a dependency the repository does not have.

## Evidence to record

Copy the before and after answers into your notes, plus the output of:

```bash
ctest --preset debug --output-on-failure
```
