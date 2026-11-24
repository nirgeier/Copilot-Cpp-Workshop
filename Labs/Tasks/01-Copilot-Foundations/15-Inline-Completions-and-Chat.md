# Task - Inline Completions and Chat

!!! abstract "About this Task"
    Compare completion with chat on a C++ function, then run the identical chat question with and without grounded context.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [18. Inline Completions and Chat](../../01-Copilot-Foundations/18-Lab-Inline-Completions-and-Chat.md) |
| Scope | Editor and chat sessions plus one scratch C++ file under `sandbox/`. No library changes. |
| Inputs | One header and source, one scratch C++ file, one chat question, two chat sessions |
| Constraints | No sensitive data in chat. No accepted suggestion without checklist review. |
| Deliverable | A scratch C++ file with one accepted completion, a decision log, and a chat comparison table |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Choose completion for local patterns and chat for grounded questions.
- Attach the smallest sufficient evidence.
- Review every suggestion against the C++ checklist.

## The Task

- Let Copilot complete a small patterned function and a function that needs a bounds decision.
- Record one acceptance and one rejection.
- Then ask the same question in two chats, one bare and one with files attached, and compare the answers.

## Task Steps

### Step 1 - Complete a patterned function in C++

- Open a header and its source.
- Let Copilot complete a small, obvious function and accept it only if it matches the header contract.
- Copy the accepted block into `sandbox/completion_demo.cpp` with a declaration that mirrors the header.
- The scratch file is not part of a CMake target and does not change the library.

**Expected evidence:** the accepted block in the scratch file and the checklist reason.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- Choose a function with a clear local pattern, for example an accessor or a simple conversion.
- Accept only if the signature matches `include/edge_inference/`, const-correctness is preserved, and no API is invented.
- Inline completions are best for local patterned code, not repository wide decisions.

</details>

### Step 2 - Reject a completion needing a decision

- Ask Copilot to complete a function that needs a bounds or ownership decision.
- Reject a plausible but unproven suggestion.

**Expected evidence:** the rejected block and the reason.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- Use Escape to reject.
- A suggestion can compile and still be wrong for C++ reasons: bounds, signedness, integer width, ownership, exception safety, or an invented API.
- Apply `docs/review-checklist.md` to every block.
- Record which checklist item failed.

</details>

### Step 3 - Ask the bare chat question

In a fresh chat with no files attached, ask: "What does `preprocess` do, and which command proves it?"

**Expected evidence:** the answer with claims marked verified or guessed.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- A bare answer is usually generic.
- Mark a claim verified only if you can open the file or run the command.
- Mark a guessed build command as wrong; the real one is in `CMakePresets.json`.
- Slash commands such as explain, fix, tests, docs, commit message, and pull request description cover common actions and can be used here.

</details>

### Step 4 - Ask the grounded chat question

- In a second fresh chat, attach the header, source, and failing test output.
- Ask the identical question.

**Expected evidence:** a comparison table across both chats.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

| Check | Bare chat | Grounded chat |
|-------|-----------|---------------|
| Names the real function | Maybe | Yes |
| Names `src/preprocessing.cpp` | No | Yes |
| Names the exact CTest command | Maybe | Yes |
| Cites a file path | Rarely | Yes |
| Invents an API | Possible | Less likely |

- Use `#file` or `@` path mentions, a selection, or pasted terminal output.
- Reserve `#codebase` for whole repository questions.
- A short prompt with the right file beats a long description.

</details>

### Step 5 - Check responsible use

- Confirm no token, customer data, or unreleased source was pasted.
- Note the public code matching setting state if your plan exposes it.

**Expected evidence:** a short responsible use note.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Code referencing and public code matching filters may apply depending on plan and policy.
- Do not change a policy setting without approval.
- Copilot output is a proposal; a human decides what ships.
- Use checkpoints and history to roll back agent edits when the direction is wrong.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- No library file changes are expected. The scratch file is not part of a CMake target.
- The seeded failures remain.

## Definition of Done

- [ ] The scratch C++ file contains the accepted completion with a checklist reason.
- [ ] One accepted and one rejected completion are logged with checklist reasons.
- [ ] Two chat answers use the identical question.
- [ ] Every repository claim is marked verified or guessed.
- [ ] No sensitive data was pasted into chat.
- [ ] Build and test output is attached.

## Summary

&emsp;✅&emsp;Use completion for local patterns and chat for grounded questions<br>
&emsp;✅&emsp;Attach the smallest sufficient evidence<br>
&emsp;✅&emsp;Review every suggestion against the C++ checklist
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Identical chat question used in both fresh chats:

```text
What does preprocess do, and which command proves it?
```

Comparison record:

```markdown
| Check | Chat A, no context | Chat B, header and instructions |
|-------|--------------------|---------------------------------|
| Names the real function | no | yes |
| Names `ctest --preset debug --output-on-failure` | no | yes |
| Cites `src/preprocessing.cpp` | no | yes |
| Invents an API | yes | no |
| Respects the warning policy | no | yes |
```

- Accept a completion only when it matches the header contract and reject one that makes an unsafe bounds decision, recording both reasons.
- Compare a chat answer with and without the header open, citing file evidence.
- Note the state of the public code matching setting without changing policy.
- Keep sensitive data out of chat and leave the build and test state unchanged.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Official Documentation Map](16-Official-Documentation-Map.md)
