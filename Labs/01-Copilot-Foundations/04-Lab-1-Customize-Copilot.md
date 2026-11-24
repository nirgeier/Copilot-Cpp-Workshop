# 4. Customize Copilot

!!! abstract "About this Lab"
    - Copilot reads repository instructions, prompts, agents, and skills from fixed locations.
    - Each customization file has a scope and a constraint that keeps generated changes grounded.


## Reference

### Customization change reference

| File | Change it to add | Constraint |
|------|------------------|------------|
| `.github/copilot-instructions.md` | Local build commands and C++ rules | Remove generic statements |
| `.github/instructions/cpp.instructions.md` | Header first, bounds and signedness rules | Keep `applyTo` scoped to C++ files |
| `.github/instructions/cmake.instructions.md` | Offline C++17 build rules | No `FetchContent` or network downloads |
| `.github/prompts/plan-implementation.prompt.md` | Evidence sources and output contract | One task per prompt file |
| `.github/agents/cpp-reviewer.agent.md` | Read-only tool scope | No `edit` in a reviewer |

- Every added rule must point to a file, command, or policy that exists here.
- The Lab 2 plan must name the files to change and the exact validation commands.

## Example

A complete prompt file at `.github/prompts/plan-implementation.prompt.md`:

```markdown
---
description: Turn an issue into a repository-grounded implementation plan for this C++ project
---

# Plan an implementation

Issue: ${input:issue_reference}

1. Restate the acceptance criteria in one sentence.
2. Find the public header and implementation that would change.
3. Find the test that would prove the change.
4. List the exact build and test commands from `CMakePresets.json`.
5. Name open questions. Do not guess answers.
6. Output: scope, file list, steps, checks, risks, open questions.

## Rules

- Cite a real file path for every repository claim.
- Do not add dependencies or network downloads.
- Do not fix the seeded defects in this lab.
- Keep prose in ASCII hyphens.
```

---

**Next:** [5. Agent Skills](05-Lab-Agent-Skills.md)
