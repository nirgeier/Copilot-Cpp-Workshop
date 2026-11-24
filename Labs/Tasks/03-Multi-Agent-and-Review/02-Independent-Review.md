# Task - Run an Independent C++ Review

!!! abstract "About this Task"
    - The agent that wrote a diff must not be the only agent that judges it.
    - You will use the repository reviewer profile on a small change, check its tool scope, and triage its findings against the team checklist.

## 1. Produce a Small Diff

- Use a diff you already own from the tasks track, for example the instructions and prompt files from the context task, or the accepted documentation edit from the guardrails task.
- Keep it under a few files so every line can be discussed.

```sh
git status --short
git diff --stat
git diff
```

## 2. Audit the Reviewer Before You Use It

Open `.github/agents/cpp-reviewer.agent.md` and check the frontmatter:

- Its `description` names the role and the repository.
- Its tool list contains no `edit` tool.
- It points to `docs/review-checklist.md` as the authoritative list.

!!! warning "A reviewer with write access is not independent"
    - If the profile can edit, remove that tool before you run the review.
    - A reviewer must report findings, not change the code it judges.

## 3. Run the Review

- Ask the reviewer to inspect only the current diff.
- Include the acceptance criteria and the validation output with the request.

- [ ] The review reports blocking findings first.
- [ ] Every finding cites a file and line.
- [ ] Non-blocking suggestions are separated from blockers.
- [ ] Missing validation evidence is stated, not assumed.
- [ ] The reviewer did not modify any file.

## 4. Triage the Findings

For each finding, decide one of three outcomes:

| Outcome | When to use it |
|---------|----------------|
| Accept | The claim is supported by the source and the checklist |
| Reject with reason | The claim cites no real API, file, or output |
| Need evidence | The claim is plausible but the validation run is missing |

- Check at least one finding yourself against the actual header or source in `include/edge_inference/` or `src/`.
- Do not accept a finding because it sounds confident.

## 5. Close the Loop

- [ ] Apply only accepted findings, or explain why you did not.
- [ ] Rerun build and tests after any change.
- [ ] Record the reviewer output and your triage in the task notes.
- [ ] A human approves the final diff.

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

## 6. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Review praises the diff without findings | Scope or checklist was not supplied | Restate both in the request |
| Finding cites an API that does not exist | Agent guessed | Reject with the real header as evidence |
| Review changed a file | Write tool still enabled | Remove the tool and rerun |
| All findings look blocking | Checklist weights were not given | Ask for blocking and non-blocking separately |

## 7. Definition of Done

- [ ] The reviewer profile has no edit tool.
- [ ] The review output is attached with file and line references.
- [ ] Every finding has an accept, reject, or need-evidence outcome.
- [ ] At least one finding was verified against repository source.
- [ ] Build and test output is attached after any applied change.
- [ ] A human approved the final diff.

## 8. Summary

&emsp;✅&emsp;Verify the reviewer tool scope before use<br>
&emsp;✅&emsp;Triage findings against `docs/review-checklist.md`<br>
&emsp;✅&emsp;Keep the final approval with a human

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Corrected `.github/agents/cpp-reviewer.agent.md` frontmatter:

```yaml
---
description: Reviews C++ changes in this workshop repository against the team checklist
tools: ["codebase", "search"]
---
```

Review request sent with the current diff:

```text
Review only the current git diff against docs/review-checklist.md.
Report blocking findings first with file and line references. Separate
non-blocking suggestions. State explicitly when validation evidence is
missing. Do not edit any file.
```

Triage record:

```markdown
| Finding | Outcome | Evidence |
|---------|---------|----------|
| Index starts at 1 in argmax | accepted | src/postprocessing.cpp and the failing test |
| Use a third-party math library | rejected | No such dependency in CMakeLists.txt |
| Confirm sanitizer run | need evidence | No sanitizer output attached |
```

1. `cpp-reviewer.agent.md` has no `edit` tool and names `docs/review-checklist.md`.
2. The reviewer reported blocking findings first with file and line references, separated suggestions, and stated missing validation evidence.
3. Each finding was accepted, rejected with a reason, or marked need-evidence. At least one finding was checked against the real header or source.
4. After any applied change, build and CTest were rerun and a human approved the final diff.

A reviewer that changed a file or cited an invented API failed the task.

</details>

---

**Back:** [Tasks (Overview)](../README.md)
