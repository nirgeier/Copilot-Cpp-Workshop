# Task - Copilot Code Review

!!! abstract "About this Task"
    Request a Copilot review on a small C++ diff, classify every comment, and inspect an agent authored pull request before approving workflows.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [10. Copilot Code Review](../../01-Copilot-Foundations/10-Lab-Copilot-Code-Review.md) |
| Scope | A small diff from the debugging task, plus one line in repository instructions |
| Inputs | A pull request, `docs/review-checklist.md`, the effort level control |
| Constraints | Do not apply a suggestion without reading the diff. Do not approve workflows blindly. |
| Deliverable | A classified comment table and an agent PR inspection note |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Request and classify Copilot review comments by severity and correctness.
- Choose a review effort level from risk.
- Keep human approval and workflow approval explicit.

## The Task

- Use the diff from task 05, or create a small header and test change if you skipped it.
- Add one review hint to repository instructions, request a review, classify each comment, then inspect how an agent authored pull request is handled.

## Task Steps

### Step 1 - Add one review hint

Add one line to `.github/copilot-instructions.md` pointing the reviewer at the human checklist.

**Expected evidence:** the added line in the diff.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- Add: "For C++ changes, apply `docs/review-checklist.md` before suggesting approval.
- Pay particular attention to ownership, bounds, signedness, and weakened tests." Keep it short and checkable.
- Copilot code review reads repository wide instructions, path instructions, and `AGENTS.md`, so the hint reaches the reviewer without a special setting.

</details>

### Step 2 - Request the review

- On a pull request, find Copilot under Reviewers and click Request.
- Record the effort level you selected and why.

**Expected evidence:** the review overview and the effort level in your notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- For a small local fix, Balanced is a reasonable default.
- Choose Lite for a low risk documentation or test only change, and Max for a public interface change with ABI consequences.
- Adaptive is available where supported and is bounded by the configured maximum.
- Higher effort consumes more credits, so quote the documented cost rather than a local estimate.

</details>

### Step 3 - Classify every comment

- For each comment, mark grounded, plausible but unproven, or wrong.
- Include severity and a file and line reference.

**Expected evidence:** a table with one row per comment.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

| Comment | Severity | Classification | Why |
|---------|----------|----------------|-----|
| Missing bounds check in `src/preprocessing.cpp:NN` | Medium | Grounded | Line reads the buffer without a size check |
| Suggested rename of a public symbol | Low | Wrong | Breaks the public interface in `include/edge_inference/` |
| Suggested new test for constant input | Low | Plausible | Useful, but not proven needed by the checklist |

- Reject any comment that asks you to delete or weaken an assertion.
- Replies you add to Copilot's comments are visible to humans but are not visible to Copilot.

</details>

### Step 4 - Review an agent authored pull request

- If an agent opens a pull request in your environment, inspect it.
- Check workflow changes before clicking Approve and run workflows.

**Expected evidence:** a short inspection note.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- By default, GitHub Actions workflows do not run automatically on an agent pushed branch.
- Look first at any change under `.github/workflows/`.
- Only then click Approve and run workflows.
- Your approval of a Copilot pull request does not count toward a required approval, so another reviewer must approve.
- Use `@copilot` in a comment to request changes, and use the feedback buttons with a reason when the output is poor.

</details>

### Step 5 - Apply only accepted suggestions

- Apply the grounded comments that pass human review.
- Rerun validation.

**Expected evidence:** the final diff with only human accepted changes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Accept a single suggestion or a group in one commit, then rebuild and run CTest.
- Never apply a comment solely because Copilot labeled it High.
- Keep a human decision record for each accepted change.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- Expected state depends on whether you applied the debugging fix.
- Record the CTest summary line.

## Definition of Done

- [ ] A review was requested with the effort level recorded.
- [ ] Every comment was classified with severity and file and line.
- [ ] No weakening suggestion was applied.
- [ ] Workflow files were inspected before any workflow approval.
- [ ] Each applied change has a human decision record.
- [ ] Validation output is attached.

## Summary

&emsp;✅&emsp;Classify review comments instead of accepting them<br>
&emsp;✅&emsp;Choose effort from risk and document the reason<br>
&emsp;✅&emsp;Keep human approval and workflow approval explicit
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Add this line to `.github/copilot-instructions.md`:

```markdown
Apply docs/review-checklist.md to every C++ diff. Report ownership, bounds,
signedness, integer width, exception safety, and API stability findings first.
```

Classification record for the requested review:

```markdown
| Comment | Class | Reason |
|---------|-------|--------|
| Missing bounds check at index N | grounded | Cited src/preprocessing.cpp line and the header contract |
| Consider a different container | plausible but unproven | No repository evidence or benchmark |
| Remove the failing assertion | wrong | Violates the no-weakening rule in the review checklist |
```

- Add a line to repository instructions pointing the reviewer at `docs/review-checklist.md`.
- Request a review on a small header plus test diff and state the effort level you used.
- Classify each comment as grounded, plausible but unproven, or wrong; reject any comment that asks to weaken a test.
- Inspect an agent authored pull request for workflow changes before approving it, and have a human read every diff before applying a suggestion.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Prompt Files and Custom Instructions](08-Prompt-Files-and-Instructions.md)
