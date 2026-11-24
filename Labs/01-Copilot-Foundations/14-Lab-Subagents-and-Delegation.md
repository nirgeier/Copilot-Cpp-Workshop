# 14. Subagents and Delegation

!!! abstract "About this Lab"
    - A subagent handles delegated work in an isolated context.
    - A handoff contract defines the input, output, and tool scope of each worker.


## 1. The Delegation Model

- A subagent is an agent doing delegated work in a separate context window.
- It operates independently, does not pause for user feedback, and returns its result to the main session.

- Subagents use the same tools and model as the main session.
- They cannot create other subagents.
- Separate context keeps intermediate detail out of the main conversation.
- Independent tasks can run in parallel.
- Delegation is a behavior, not a requirement to author a custom profile.

- Use a subagent for research, analysis of many files, or an independent perspective.
- Do not use one when the main session needs every intermediate step to make a decision.

| Situation | Better choice |
|-----------|---------------|
| Ask what `preprocess` does | Ask in the main chat |
| Review a diff from an independent angle | Delegate to a review subagent |
| Scan all headers for a pattern | Delegate |
| Argue against your proposed fix | Delegate to a second opinion agent |

## 2. Built-in Agents in Copilot CLI

- Copilot CLI provides `explore`, `task`, `general-purpose`, `code-review`, `research`, `rubber-duck`, and `security-review`.
- These are provided by the CLI, not authored as profiles.
- Their tools and model defaults differ.

- The `rubber-duck` agent is a practical second opinion.
- It is useful after you believe a fix is correct, precisely because it has no stake in your conclusion.

## Reference

### Delegation control reference

| Surface | Enable | Invocation |
|---------|--------|------------|
| VS Code | `runSubagent` in the tools control | Direct name, prompt pattern, or `#runSubagent` |
| JetBrains | Subagent setting; a custom agent must exist | Direct name or prompt pattern |
| Copilot CLI | Built-in agents, no profile needed | Name the agent in the prompt |

| Built-in agent | Use it for |
|----------------|------------|
| `explore` | Read-only codebase exploration |
| `task` | A delegated implementation task |
| `code-review` | An independent review |
| `rubber-duck` | A second opinion against your conclusion |
| `security-review` | Policy and secret review |

- A subagent uses the main session tools and model, cannot spawn subagents, and returns a result without pausing for feedback.
- Include the task reference, acceptance criteria, evidence, validation command, and output format in the handoff.

```text
Use a subagent to argue against this diff using docs/review-checklist.md.
Cite file and line. State when evidence is missing. Do not edit files.
```

!!! note "Trust boundary"
    - Delegated output is untrusted. Check file and line references before merging.
    - Keep write permissions narrow for review roles.

---

## Example

```text
Task: challenge the proposed fix for preprocessing_tests.
Evidence: docs/review-checklist.md, src/preprocessing.cpp, its header,
          tests/test_preprocessing.cpp.
Validation: cmake --build --preset debug and ctest --preset debug --output-on-failure.
Output: at most three blocking findings, each with file and line. Do not edit.
```

## 3. Summary

Describe a subagent and when delegation helps<br>
Enable and invoke a subagent with a handoff contract<br>
Use a second opinion without treating it as approval

**Next:** [15. Copilot CLI](15-Lab-Copilot-CLI.md)
