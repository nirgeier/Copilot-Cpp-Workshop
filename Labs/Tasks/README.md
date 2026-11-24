# Hands-on Tasks

- This section is the practice track for the course.
- Each task is a small exercise against the C++ starter repository in this workshop.
- Read the matching theory section first, then return here and do the work.

- Tasks are grouped by course section.
- Every task has steps, a definition of done, and validation commands.
- Keep your evidence on a lab branch and bring a diff to the review step.

| Course section | Tasks |
|----------------|-------|
| Setup | Build and verify the starter repository |
| Copilot Foundations | One task per lab, listed below |
| Agent Mode and MCP | Configure guardrails, connect an approved MCP server |
| Multi-Agent and Review | Delegate to a subagent, run an independent C++ review |
| Project | Build a complete C++ repository with the full customization layer |

## Copilot Foundations Tasks

- Every lab in the Copilot Foundations section has a matching task.
- Each task has a full definition, lab goals, clear steps, and a suggested solution for every step.

| Task | Lab | Focus |
|------|-----|-------|
| [Create an Agent Skill](01-Copilot-Foundations/02-Agent-Skills.md) | [Lab 5](../01-Copilot-Foundations/05-Lab-Agent-Skills.md) | `SKILL.md`, selective loading, tool scope |
| [Create a Custom Agent](01-Copilot-Foundations/03-Custom-Agents.md) | [Lab 6](../01-Copilot-Foundations/06-Lab-Custom-Agents.md) | Role profiles and tool scopes |
| [Ground Context with Instructions and Prompts](01-Copilot-Foundations/01-Ground-Context.md) | [Labs 2 and 11](../01-Copilot-Foundations/02-Context-Engineering.md) | Instruction layers and prompt files |
| [Choose the Right Model](01-Copilot-Foundations/04-Choosing-the-Right-Model.md) | [Lab 7](../01-Copilot-Foundations/07-Lab-Choosing-the-Right-Model.md) | Auto, pinned models, cost, policy |
| [Debug with Real Evidence](01-Copilot-Foundations/05-Debugging-with-Copilot.md) | [Lab 8](../01-Copilot-Foundations/08-Lab-Debugging-with-Copilot.md) | One seeded defect, hypotheses, sanitizers |
| [Review Copilot Usage Internally](01-Copilot-Foundations/06-Reviewing-Copilot-Usage.md) | [Lab 9](../01-Copilot-Foundations/09-Lab-Reviewing-Copilot-Usage-Internally.md) | Metrics, activity, credits, audit log |
| [Copilot Code Review](01-Copilot-Foundations/07-Copilot-Code-Review.md) | [Lab 10](../01-Copilot-Foundations/10-Lab-Copilot-Code-Review.md) | Comments, effort levels, agent PRs |
| [Prompt Files and Custom Instructions](01-Copilot-Foundations/08-Prompt-Files-and-Instructions.md) | [Lab 11](../01-Copilot-Foundations/11-Lab-Prompt-Files-and-Custom-Instructions.md) | Scoped rules and invoked workflows |
| [MCP and Connectors](01-Copilot-Foundations/09-MCP-and-Connectors.md) | [Lab 12](../01-Copilot-Foundations/12-Lab-MCP-and-Connectors.md) | Least privilege, tool classification |
| [Agent Mode and Plan Mode](01-Copilot-Foundations/10-Agent-Mode-and-Plan-Mode.md) | [Lab 13](../01-Copilot-Foundations/13-Lab-Agent-Mode-and-Plan-Mode.md) | Plan, approve, steer, validate |
| [Subagents and Delegation](01-Copilot-Foundations/11-Subagents-and-Delegation.md) | [Lab 14](../01-Copilot-Foundations/14-Lab-Subagents-and-Delegation.md) | Handoff contracts, second opinion |
| [Copilot CLI](01-Copilot-Foundations/12-Copilot-CLI.md) | [Lab 15](../01-Copilot-Foundations/15-Lab-Copilot-CLI.md) | Trust, `@` context, `/review` |
| [Hooks and Guardrails](01-Copilot-Foundations/13-Hooks-and-Guardrails.md) | [Lab 16](../01-Copilot-Foundations/16-Lab-Hooks-and-Guardrails.md) | `preToolUse` deny, audit logging |
| [Spaces and Copilot Memory](01-Copilot-Foundations/14-Spaces-and-Memory.md) | [Lab 17](../01-Copilot-Foundations/17-Lab-Spaces-and-Copilot-Memory.md) | Shared context, fact classification |
| [Inline Completions and Chat](01-Copilot-Foundations/15-Inline-Completions-and-Chat.md) | [Lab 18](../01-Copilot-Foundations/18-Lab-Inline-Completions-and-Chat.md) | Surface comparison, grounding |
| [Verify against Official Docs](01-Copilot-Foundations/16-Official-Documentation-Map.md) | [Lab 19](../01-Copilot-Foundations/19-Official-Documentation-Map.md) | Claim verification and corrections |
| [Verify the Latest Copilot Changes](01-Copilot-Foundations/17-Latest-Copilot-Changes.md) | [Lab 20](../01-Copilot-Foundations/20-Latest-Copilot-Changes.md) | Connectors, new models, review updates, monitoring |

## Project Task

- The project task is the capstone. It creates a new repository instead of editing the starter checkout.
- It uses the full customization layer to write C++ code with AI, then builds, tests, and proves each guardrail.

| Project | Focus |
|---------|-------|
| [Build a Workshop Repository](Project/01-Workshop-Repository.md) | Git repo, CMake presets, C++ library, CLI, Boost.Test, instructions, prompts, agents, skill, hooks, MCP classification |

!!! note "Seeded failures"
    - A clean checkout builds, but `preprocessing_tests` and `postprocessing_tests` fail on purpose.
    - Tasks that do not name those defects must leave them failing.
    - `model_tests` passes from the start.

## How to use this track

1. Create a branch for your task work, for example `git switch -c tasks/your-name`.
2. Open the task from the left navigation under **Tasks** and read the definition of done first.
3. Do the steps in order. Record command output rather than paraphrasing it.
4. Run the validation commands at the end of the task, even when the task changes no C++ code.
5. Keep the diff small. A human reviews every task before it is accepted.

## Definition of done for the whole track

- [ ] Every task has a branch or a committed diff that a reviewer can inspect.
- [ ] Build and test output is attached where the task asks for it.
- [ ] No seeded defect was fixed outside its assigned task.
- [ ] No secrets, model binaries, or personal paths were added.
- [ ] All prose uses ASCII hyphens.

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

- A completed track has one branch or committed diff per task, build and test evidence where the task asks for it, the seeded failures left intact outside their assigned tasks, and a human reviewer for every diff.
- Use the theory sections in the Labs tab when a task step is unclear.

</details>

---

**Next:** [Task - Build and Verify the Starter Repository](00-Setup/01-Build-and-Verify.md)
