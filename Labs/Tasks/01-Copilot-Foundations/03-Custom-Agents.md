# Task - Create a Custom Agent

!!! abstract "About this Task"
    - Build two specialist roles with narrow tool scopes: a planner that cannot edit and a reviewer that cannot write.
    - Then run a plan, implement, review handoff.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [6. Custom Agents](../../01-Copilot-Foundations/06-Lab-Custom-Agents.md) |
| Scope | `.github/agents/` plus one seeded defect fix in `src/`, `include/edge_inference/`, and `tests/` |
| Inputs | `.github/agents/cpp-reviewer.agent.md`, `docs/review-checklist.md`, issue #1 |
| Constraints | Reviewer must not have write tools. Planner must not edit or run mutating commands. |
| Deliverable | A tightened reviewer profile, a new planner profile, one C++ defect fix with its test, and a handoff transcript |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Distinguish a custom agent profile from a subagent.
- Scope tools to the role instead of granting a generic tool set.
- Carry evidence between plan, implementation, and review steps.

## The Task

- Remove the edit capability from the shipped reviewer.
- Add `cpp-planner.agent.md` that researches and plans without changing files.
- Then use both profiles in a three-step handoff and record where the chain succeeded or broke.

## Task Steps

### Step 1 - Audit the reviewer profile

- Open `.github/agents/cpp-reviewer.agent.md`.
- Identify any tool that allows modification and decide whether the role needs it.

**Expected evidence:** the exact frontmatter line to change.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

Replace `.github/agents/cpp-reviewer.agent.md` with this complete profile:

```markdown
---
description: Reviews C++ changes in this workshop repository against the team checklist
tools: ["codebase", "search"]
---

# C++ reviewer

You review proposed changes to this repository. You do not implement them.

## Scope

- Only the current diff and directly related files.
- C++ headers and sources, CMake files, and tests.

## Checklist

Use `docs/review-checklist.md` as the authoritative list. Pay particular
attention to:

- Ownership, lifetimes, and exception safety.
- Bounds checks, signedness, and integer width.
- Invented or unsupported APIs.
- Public interface stability and `const`-correctness.
- New dependencies or files that should not be in the repository.
- Tests that were weakened instead of fixed.

## Output

Report blocking findings first, with file and line references. Then list
non-blocking suggestions. State clearly when validation evidence is missing.
Never approve a diff solely because tests pass.
```


</details>

### Step 2 - Write the planner profile

Create `.github/agents/cpp-planner.agent.md` with a description, read only tools, a procedure, and rules.

**Expected evidence:** the new file exists and contains no write tool.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

```markdown
---
description: Produce a repository-grounded implementation plan for a C++ task without editing files
tools: ["codebase", "search"]
---

# C++ planner

You plan. You do not edit files and you do not run mutating commands.

## Procedure

1. Restate the task and acceptance criteria.
2. Find the public header and implementation that would change.
3. Find the test that would prove the change.
4. List the build and test commands from `CMakePresets.json`.
5. Name open questions. Do not guess answers.
6. Output: scope, file list, steps, checks, risks.

## Rules

- Cite a file path for every claim about this repository.
- Do not add dependencies or network downloads.
- Keep prose in ASCII hyphens.
```

- Tool names vary by surface.
- Check the configuration reference for the IDE or CLI you use.

</details>

### Step 3 - Run the handoff

Plan issue #1 with `cpp-planner`, implement the plan in the normal agent, then review only the diff with `cpp-reviewer`.

**Expected evidence:** three short excerpts, one from each role.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- Planner output names `include/edge_inference/` and `src/`, the failing CTest entry, and `cmake --preset debug` plus `ctest --preset debug --output-on-failure`.
- It asks open questions instead of guessing.

- Implementer output changes only the files in the plan.
- It stops after one defect and its test.

- Reviewer output lists blocking findings first with file and line, then non-blocking suggestions, and states when validation evidence is missing.
- It does not edit anything.

- Record any role that drifted, for example a reviewer offering a patch.
- That is a finding for the next iteration of the profile.

</details>

### Step 4 - Confirm custom agent versus subagent

Explain to a teammate why you did not need to author a profile to use a subagent.

**Expected evidence:** one paragraph in your notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- A custom agent is a definition of a specialist.
- A subagent is an agent doing delegated work in a separate context window.
- The main agent can delegate to a built-in agent such as `explore` or `code-review`, or run a specialist using a custom profile.
- Separate context and parallel work come from delegation, not from authoring a profile.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

Expected state: the defect assigned by issue #1 is fixed and its test passes. The other seeded failure remains.

## Definition of Done

- [ ] `cpp-reviewer.agent.md` has no edit or write tool.
- [ ] `cpp-planner.agent.md` has no write or command tool.
- [ ] Both profiles have precise descriptions.
- [ ] A plan, implementation, and review excerpt is recorded.
- [ ] The handoff carried issue #1, acceptance criteria, and validation commands.
- [ ] Only the defect assigned by issue #1 was fixed, and its test passes.
- [ ] The other seeded failure is still present.

## Summary

&emsp;✅&emsp;Remove write access from the reviewer role<br>
&emsp;✅&emsp;Define a read only planner with an output contract<br>
&emsp;✅&emsp;Run a three role handoff with evidence at each step
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

`.github/agents/cpp-reviewer.agent.md` after removing the write tool:

```yaml
---
description: Reviews C++ changes in this workshop repository against the team checklist
tools: ["codebase", "search"]
---
```

`.github/agents/cpp-planner.agent.md`:

```markdown
---
description: Produce a repository-grounded implementation plan for a C++ task without editing files
tools: ["codebase", "search"]
---

# C++ planner

You plan. You do not edit files and you do not run mutating commands.

1. Restate the task and its acceptance criteria.
2. Find the public header and implementation that would change.
3. Find the test that would prove the change.
4. List the build and test commands from `CMakePresets.json`.
5. Name open questions. Do not guess.
6. Output: scope, file list, steps, checks, risks.
```

- Remove `edit` from the `cpp-reviewer.agent.md` tools list so it only reads and searches; keep `docs/review-checklist.md` and the file and line output contract.
- Add `.github/agents/cpp-planner.agent.md` with `tools: ["codebase", "search"]` and a procedure that cites headers, sources, the failing test, and the preset commands.
- Run plan, then implement, then review.
- The plan cites real files, the review reports blocking findings first, and the final diff contains only customization files.
- The two seeded failures remain.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Choose the Right Model](04-Choosing-the-Right-Model.md)
