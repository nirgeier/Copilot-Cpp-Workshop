# 11. Prompt Files and Custom Instructions

!!! abstract "About this Lab"
    - Standing instructions and reusable prompt files solve different problems.
    - The repository layers them so rules apply broadly and workflows are invoked deliberately.


## 1. Two Different Mechanisms

| Mechanism | Applies when | Location here |
|-----------|--------------|---------------|
| Custom instructions | Automatically, inside their scope | `.github/copilot-instructions.md`, `.github/instructions/*.instructions.md`, `AGENTS.md` |
| Prompt file | Only when invoked for one interaction | `.github/prompts/*.prompt.md` |

- Custom instructions shape every interaction in their scope.
- Prompt files are standalone Markdown templates for a focused task.
- They can declare input variables and additional context.

- Repository prompt files use the `.prompt.md` extension and usually live in `.github/prompts/`. Some IDEs allow other locations.
- In a supported IDE you run a prompt file from chat by referencing or selecting it.
- Frontmatter can declare `description`, `agent`, and optional model and tools.

!!! tip "When to use which"
    - A rule that must always hold, such as "validate sizes before indexing", belongs in instructions.
    - A workflow a human starts, such as "turn issue #1 into a plan", belongs in a prompt file.

## Reference

### Prompt file frontmatter reference

| Field | Required | Values | Effect |
|-------|----------|--------|--------|
| `description` | Yes | Short task description | Selects the prompt file |
| `agent` | No | Agent name | Runs the prompt in a specialist role |
| `model` | No | Model identifier | Preferred model for this workflow |
| `tools` | No | Tool names | Tools available to the prompt |

- A prompt file runs only when invoked. An instruction applies automatically in its scope.
- Put standing rules in `.github/copilot-instructions.md` or a path scoped `.instructions.md`.
- Keep one task per prompt file, name the evidence to read, and require an output contract.

```yaml
---
description: Triage one failing CTest case in this repository and propose a scoped fix
agent: cpp-planner
---
```

!!! note "Variable syntax"
    - Input variables such as `${input:test_name}` and frontmatter keys differ between IDEs and the CLI.
    - Check the documentation for your surface before relying on them.

---

## 2. Prompts, Instructions, Skills, Agents, and Hooks

- Lab 11 compares two mechanisms. The repository uses a small toolkit of related primitives.
- They differ by trigger, scope, and the control they give the model.
- Choose the smallest primitive that solves the problem.

| Primitive | File | Loaded when | Best for |
|-----------|------|-------------|----------|
| Instruction | `.github/copilot-instructions.md`, `AGENTS.md` | Always in scope | Standing rules that always apply |
| Path instruction | `.github/instructions/*.instructions.md` | A matching file is in context | Rules for a file type or folder using `applyTo` |
| Prompt file | `.github/prompts/*.prompt.md` | The user invokes it | A repeatable, user-started workflow |
| Custom agent | `.github/agents/*.agent.md` | The role is selected | A role with a specific tool scope |
| Skill | `.github/skills/<name>/SKILL.md` | Its description matches the task | A packaged procedure with supporting files |
| Hook | `.github/hooks/*.json` | A configured event fires | A deterministic check around an action |

### What each one actually does

- **Instruction**: a rule the model sees in every interaction in scope. It requests behavior but does not enforce it. Keep durable, tool-neutral facts in `AGENTS.md` and repository rules in `.github/copilot-instructions.md`.
- **Path instruction**: an instruction with an `applyTo` glob. Use it when a rule only matters for certain files, for example `**/*.cpp`. A broad glob turns it into a global rule.
- **Prompt file**: a Markdown template for one task. A human starts it with `/` in chat. Its `description` selects it, and its body names the evidence to read and the output to produce. It runs once per invocation.
- **Custom agent**: a role profile. Its `tools` frontmatter restricts what the role may touch. Keep the tool set narrow so a reviewer cannot edit the code it reviews.
- **Skill**: a folder with `SKILL.md`, optional scripts, and resources. Copilot loads it when the task matches its `description`. Use it for a procedure you want reused without memorizing a command.
- **Hook**: code that runs on an event such as a tool call. It enforces a rule by blocking an action. It is a guardrail, not a replacement for tests.

!!! tip "Choosing a primitive"
    - An always-on rule belongs in instructions.
    - A workflow a human starts belongs in a prompt file.
    - A role with limited rights belongs in a custom agent.
    - A packaged procedure belongs in a skill.
    - A rule that must be blocked belongs in a hook.

!!! note "They compose"
    - A prompt file can declare an `agent`, so invoking a prompt can select a role.
    - Instructions stay in context while a prompt file, a skill, or an agent runs.
    - A hook can check the result of any of them.

!!! note "Agent versus subagent"
    - A custom agent defines a role and its tool scope.
    - A subagent is an instance you delegate work to with a handoff contract (Lab 14).

---

## 3. Common Failure Modes

| Failure | Cause | Fix |
|---------|-------|-----|
| Rule ignored | Buried in a long file or contradicts another layer | Shorten and place near the task |
| Rule applied everywhere | Path glob too broad | Narrow `applyTo` |
| Prompt file never invoked | No clear description | Write an action oriented description |
| Generic answer | No evidence sources named | Attach exact files and commands |

## Example

```markdown
---
description: Triage one failing CTest case in this repository and propose a scoped fix
---

# Triage one CTest failure

Task: ${input:test_name}

1. Quote the exact assertion from `ctest --preset debug --output-on-failure`.
2. Read the public header before the implementation.
3. List at most three causes with file and line. Do not edit.
```

## 4. Summary

Distinguish automatic instructions from invoked prompt files<br>
Name each customization primitive and when it loads<br>
Keep path rules narrow and facts in `AGENTS.md`<br>
Write a prompt file with evidence sources and an output contract

**Next:** [12. MCP and Connectors](12-Lab-MCP-and-Connectors.md)
