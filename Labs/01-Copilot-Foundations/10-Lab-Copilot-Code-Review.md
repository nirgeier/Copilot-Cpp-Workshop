# 10. Copilot Code Review

!!! abstract "About this Lab"
    - Copilot can act as a reviewer, and its comments still need human review.
    - Effort levels, instructions, and skills shape what the review finds.



!!! note "Latest changes"
    The November 2026 releases added new models, connectors, review controls, and monitoring. See [20. Latest Copilot Changes](20-Latest-Copilot-Changes.md) for the current status.

## 1. Where Review Happens

- Copilot code review is available on github.com, GitHub Mobile, GitHub CLI, VS Code, Visual Studio, Xcode, JetBrains IDEs, and Azure DevOps.
- If Copilot comes from an organization, the organization must enable the code review policy.

- For organizations on Business or Enterprise, members without a Copilot license can be granted review access when two policies are enabled: AI credits paid usage, and the sub policy allowing unlicensed members to use code review on github.com.
- That sub policy is off by default and is most restrictive.

## 2. Effort Levels

| Level | Intended use |
|-------|--------------|
| Lite | Cost efficient, glaring bugs, security issues, style |
| Balanced | Deeper logic, security sensitive code, cross service changes |
| Max | Multiple high reasoning models for the most critical changes |
| Adaptive | Copilot chooses, bounded by the configured maximum |

- Balanced is the default unless a different default is set.
- Higher effort consumes more credits.
- GitHub publishes approximate per review costs in the code review documentation.
- Quote the documented figure, not an estimate from this lab.

## 3. Tune the Review

- Copilot code review reads repository instructions.
- Use them to make comments relevant to this C++ project.

| File | Scope |
|------|-------|
| `.github/copilot-instructions.md` | Repository wide review criteria |
| `AGENTS.md` | Repository context and intentional patterns |
| `.github/instructions/*.instructions.md` | Path specific rules for C++ or CMake |
| `docs/review-checklist.md` | The human checklist that stays authoritative |

- Copilot code review also reads `CLAUDE.md`, `GEMINI.md`, and `REVIEW.md` if present.
- Agent skills and repository MCP servers can extend a review.
- Code review only uses MCP tools that declare `annotations.readOnlyHint: true`.


## Reference

### Review input reference

| Input | Source | Effect | Constraint |
|-------|--------|--------|------------|
| Repository instructions | `.github/copilot-instructions.md` | Repo wide review criteria | Version controlled |
| Agent facing rules | `AGENTS.md` | Intentional patterns | Shared with other agents |
| Path instructions | `.github/instructions/*.instructions.md` | C++ or CMake rules | `applyTo` scoped |
| Human checklist | `docs/review-checklist.md` | Authoritative C++ rules | Kept by humans |
| Skills | `.github/skills/` | Packaged review procedure | Loaded when description matches |
| MCP tools | Repository MCP settings | Extra context for a review | `annotations.readOnlyHint: true` only |

Each input has its own tab with a code example.

=== "Repository instructions"

    ```markdown
    # Repository instructions
    - Apply `docs/review-checklist.md` to every C++ diff.
    - Never approve a diff solely because tests pass.
    ```

=== "Agent facing rules"

    ```markdown
    # AGENTS.md
    - Keep headers and implementation split.
    - Validate sizes before indexing.
    - Copilot output is a proposal. A human approves it.
    ```

=== "Path instructions"

    ```markdown
    ---
    applyTo: "tests/**"
    ---

    - Use Boost.Test in header-only mode.
    - Never weaken an assertion to get a green run.
    ```

=== "Human checklist"

    ```markdown
    - [ ] Every claimed API exists in the included headers.
    - [ ] Indexing is bounds checked before use.
    - [ ] Build and CTest output is attached.
    - [ ] A human reviewer approved the final diff.
    ```

=== "Skills"

    ```markdown
    ---
    name: cpp-api-check
    description: Verify that proposed C++ calls exist in the headers. Use when reviewing a diff.
    ---

    List every new call, find it in a header, mark found or invented.
    ```

=== "MCP tools"

    ```json
    {
      "servers": {
        "github": {
          "type": "http",
          "url": "https://api.githubcopilot.com/mcp/"
        }
      }
    }
    ```


- Severity is reported as High, Medium, or Low. Treat every comment as a proposal.
- Effort levels are Lite, Balanced, Max, and Adaptive. Balanced is the default unless changed.
- Higher effort and agent sessions consume more credits. Quote GitHub's published costs, not lab estimates.

!!! note "Agent authored pull requests"
    - A required approval from the author does not count. Another human must approve.
    - Workflows under `.github/workflows/` do not run automatically on a Copilot branch. Inspect before approving.

---

## Example

A classified review comment table:

```text
| Copilot comment | Severity | Classification | Evidence |
|-----------------|----------|----------------|----------|
| Add a bounds check before indexing in src/preprocessing.cpp:13 | Medium | Grounded | The loop writes output.data[index] without a size check |
| Rename the public preprocess function | Low | Wrong | Breaks include/edge_inference/preprocessing.hpp |
| Add a constant input case | Low | Plausible | Useful, but not required by the checklist |

Accepted: the bounds check, after human inspection.
Rejected: the rename and the unproven suggestion.
```

A matching repository instruction:

```markdown
For C++ changes, apply `docs/review-checklist.md` before suggesting approval.
Pay particular attention to ownership, bounds, signedness, and weakened tests.
```

## 4. Summary

Request and classify Copilot code review comments<br>
Choose an effort level from risk, not habit<br>
Keep human review and workflow approval explicit

**Next:** [11. Prompt Files and Custom Instructions](11-Lab-Prompt-Files-and-Custom-Instructions.md)
