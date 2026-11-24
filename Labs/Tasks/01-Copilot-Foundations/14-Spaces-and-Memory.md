# Task - Spaces and Copilot Memory

!!! abstract "About this Task"
    Build a shared Space for the workshop and classify facts into the right home: Space, instructions, agent profile, skill, or memory.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [17. Spaces and Copilot Memory](../../01-Copilot-Foundations/17-Lab-Spaces-and-Copilot-Memory.md) |
| Scope | One Copilot Space and, if needed, one repository instruction file |
| Inputs | This repository, `docs/review-checklist.md`, one issue, one pull request, workshop notes |
| Constraints | No private or customer source in a shared Space. No memory as a substitute for review. |
| Deliverable | A tested Space and a fact classification table |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Use a Space for curated context that outlives a chat.
- Decide where a durable fact belongs.
- Set sharing access deliberately.

## The Task

- Create a Space containing this repository, the review checklist, one issue, and one pull request.
- Ask a question that needs all four sources.
- Then classify five facts and store each in the right place.

## Task Steps

### Step 1 - Create the Space

Add four reviewed sources to a new Space named after the workshop.

**Expected evidence:** the Space source list.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- Add this repository, `docs/review-checklist.md`, the issue referenced by Lab 01, and one pull request.
- GitHub sourced content stays in sync as the project changes.
- Do not add a private customer repository or a local secret file.
- Anyone with a Copilot license, including Free, can create a Space.

</details>

### Step 2 - Ask a grounded question

Ask one question that cannot be answered from a single source.

**Expected evidence:** the question and the answer with source references.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- Question: "Which validation gates apply to issue #1, and where is each one defined?" A good answer names the build and test commands from `CMakePresets.json`, points at the review checklist, and cites the issue.
- Check every claim against the original source.
- A Space makes context available, it does not make a claim correct.

</details>

### Step 3 - Set sharing access

Choose an owner and viewer access level deliberately.

**Expected evidence:** the sharing setting recorded.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- An organization owned Space can grant admin, editor, or viewer access, or no access to members.
- An individual owned Space can be public, shared with specific users, or private; public is view only by default.
- Viewers only see sources they can already access.
- If a Space mixes private and organization data, or data from several organizations, chat use in the cloud can be affected.

</details>

### Step 4 - Classify five facts

For each fact, choose Space, instructions, agent profile, skill, or memory.

**Expected evidence:** a five row table with a reason.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

| Fact | Home | Reason |
|------|------|--------|
| Use `cmake --preset debug` before every test run | Repository instructions | Durable project rule |
| The reviewer must not have edit tools | Agent profile | Role constraint |
| Always add a boundary case | Skill | Packaged procedure |
| Workshop syllabus and checklist | Space | Curated shared context |
| I prefer findings before suggestions | Copilot Memory | Personal preference |

- Version controlled files are reviewable in a pull request.
- A memory is not.
- Durable project rules belong in `AGENTS.md` or `.github/copilot-instructions.md`.

</details>

### Step 5 - Verify no sensitive source was stored

Check the Space source list and any memory entries for secrets or customer data.

**Expected evidence:** a short check note.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Confirm there is no token, password, customer name, or private path in a Space source or a memory.
- If one is present, remove it and rotate the credential if it was real.
- Questions in a Space count as chat requests and consume credits, so record that in your cost notes.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No C++ changes are expected unless you added a repository instruction file.

## Definition of Done

- [ ] The Space has four reviewed sources and a tested question.
- [ ] Sharing access was set deliberately and recorded.
- [ ] Five facts are classified with reasons.
- [ ] No secret or sensitive source was added.
- [ ] Any durable rule change is committed under `.github/` or `AGENTS.md`.

## Summary

&emsp;✅&emsp;Use Spaces for shared, synced context<br>
&emsp;✅&emsp;Keep durable rules in version controlled files<br>
&emsp;✅&emsp;Use Memory for preferences, not review
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Space sources added for the workshop:

```markdown
# Copilot C++ Workshop Space

- Repository: nirgeier/Copilot-Cpp-Workshop
- Document: docs/review-checklist.md
- Document: workshop syllabus and alignment notes
- Issue: #1 (customize Copilot)
- Pull request: one small header plus test change
```

Fact classification record:

```markdown
| Fact | Home |
|------|------|
| Use `cmake --preset debug` before every test run | Repository instructions |
| Reviewer must not have edit tools | Agent profile |
| Always include a boundary case | Skill |
| I prefer findings before suggestions | Copilot Memory |
| Workshop syllabus and checklist | Space |
```

- Create a workshop Space containing this repository, `docs/review-checklist.md`, the syllabus notes, one issue, and one pull request.
- Ask which validation gates apply to issue #1 and verify each claim against the original source.
- Share with one teammate as viewer.
- Classify a sample fact as instruction, profile, skill, Space, or Memory; add durable project rules to the correct repository file.
- Store no secret or customer specific source.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Inline Completions and Chat](15-Inline-Completions-and-Chat.md)
