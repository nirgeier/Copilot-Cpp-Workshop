# 5. Agent Skills

!!! abstract "About this Lab"
    - An agent skill packages a procedure with supporting files that Copilot loads when the task matches.
    - The name and description decide where it lives and when it loads.


## 1. What a Skill Is

- An agent skill is a folder of instructions, scripts, and resources that Copilot loads when the task is relevant.
- Skills follow the open Agent Skills specification, so the same folder can be used by more than one AI system.

- The folder must contain a file named `SKILL.md`.
- Frontmatter requires `name` (lowercase, hyphens for spaces) and `description` (what it does and when to use it).
- Optional frontmatter includes `license` and `allowed-tools`.
- The Markdown body holds the procedure, examples, and rules.
- Supporting files in the same folder are discovered when the skill loads.

| Surface | Skills support |
|---------|----------------|
| Copilot app | Yes |
| Copilot CLI | Yes |
| Copilot cloud agent and code review on github.com | Yes |
| Agent mode in VS Code, Visual Studio, and JetBrains IDEs | Yes, version dependent |

- Skill locations depend on the surface.
- Project skills live in `.github/skills`, `.claude/skills`, or `.agents/skills`.
- Personal skills live in `~/.copilot/skills` or `~/.agents/skills`.
- A personal skill is not automatically available to a cloud session, so choose the location for the surface you are using.

### Frontmatter reference

The open Agent Skills specification defines six frontmatter fields, and only `name` and `description` are required.

| Field | Required | Limits | What it does |
|-------|----------|--------|--------------|
| `name` | Yes | 1 to 64 characters, lowercase letters, digits and hyphens, must match the folder name | Unique identifier and slash command |
| `description` | Yes | 1 to 1024 characters | States what the skill does and when to use it, which drives automatic loading |
| `license` | No | License name or bundled license file | Records the terms for sharing the skill |
| `compatibility` | No | 1 to 500 characters | States environment needs such as products, packages or network access |
| `metadata` | No | Map of string keys to string values | Stores client specific properties such as author or version |
| `allowed-tools` | No | Space separated tool names | Pre-approves tools while the skill runs, experimental with varying support |

- `name` cannot start or end with a hyphen or contain consecutive hyphens.
- `description` should name the task and the trigger terms a learner would type.
- A colon followed by a space in `description` must be quoted as a YAML string.
- `metadata` values must be strings, so quote numbers such as `"1.0"`.
- Most skills do not need `compatibility`.
- `allowed-tools` is the specification field for tool preapproval, while some custom agent files use `tools` instead.
- Copilot warns against pre-approving `shell` or `bash` until you have reviewed the skill and every script it references.

```yaml
---
name: cpp-defect-triage
description: Triage one failing CTest case in the edge_inference repository. Use when a build or test fails and the cause is not yet known.
license: MIT
compatibility: Requires CMake, a C++17 compiler and Boost.Test headers available offline.
metadata:
  author: platform-team
  version: "1.0"
allowed-tools: codebase search
---
```

Vendors add more fields beyond the open specification, and another client may ignore any field it does not implement.

| Extension | Seen in | What it controls |
|-----------|---------|------------------|
| `paths` | Claude Code | Auto-loads the skill when files matching the globs are in context |
| `argument-hint` | Claude Code | Hint for arguments in the slash command |
| `disable-model-invocation` | Claude Code | Stops automatic loading so the user must invoke the skill |
| `user-invocable` | Claude Code | Controls whether the user can call the skill directly |
| `context: fork` | Claude Code | Runs the skill in an isolated subagent context |
| `model` | Claude Code | Pins a model for the skill turn |
| `disallowed-tools` | Claude Code | Removes tools while the skill is active |

- Folder location is the other kind of path that matters for skills.
- Project skills live in `.github/skills`, `.claude/skills` or `.agents/skills` in the repository.
- Personal skills live in `~/.copilot/skills` or `~/.agents/skills`.
- A cloud agent does not see your personal skill folder, so shared team skills belong in the repository.

## 2. Choose the Right Primitive

| Primitive | Use it for |
|-----------|------------|
| Instructions | Standing rules that always apply in a scope |
| Prompt file | A repeatable workflow the user invokes |
| Skill | A packaged procedure with scripts and resources |
| Custom agent | A role with its own instructions and tool scope |
| Hook | A deterministic check around an agent action |

- Use a skill when the procedure benefits from supporting files or should be shared across Copilot surfaces.
- Use a prompt file when a human wants to invoke a short template directly.

## 3. Common Failure Modes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Skill never loads | Description is too narrow or vague | Name the task and the repository area |
| Skill loads for everything | Description is too broad | Add constraints and negative cases |
| Copilot ignores the script | Path or invocation is unclear | Reference the file by exact relative path |
| Skill works locally but not in the cloud | Wrong storage location | Use project skills for shared work |

## Example

The complete `SKILL.md` is in section 4. Its key parts are:

```markdown
---
name: cpp-defect-triage
description: Triage a failing CTest case in the edge_inference C++ repository. Use when a build or test fails and the cause is not yet known.
---

1. Reproduce the failure with the commands in `CMakePresets.json`.
2. Capture the failing assertion, file, and line. Do not paraphrase.
3. Read the public header before the implementation.
```

## 4. Summary

Explain what a skill is and where Copilot loads it from<br>
Write a `SKILL.md` with a precise description and grounded procedure<br>
Keep tool permissions narrow and verify loading with evidence

---

**Next:** [6. Custom Agents](06-Lab-Custom-Agents.md)
