# 2. Configuring GitHub Copilot

!!! abstract "About this Guide"
    - Connect Copilot to VS Code, confirm your entitlement, and review the organization controls that apply to the labs.
    - Everything in this guide is subject to local policy.

## 1. Sign In to Copilot

1. Open VS Code.
2. Select the Copilot icon in the activity bar and choose **Sign in**.
3. Complete authentication with your approved GitHub account.
4. Confirm the Copilot status item shows your account and an active seat.

!!! tip "Seats and entitlements"
    - Business and Enterprise seats differ in available features and policy controls.
    - Your administrator decides which models, preview features, and MCP servers are enabled.

## 2. Confirm Copilot Surfaces

| Surface | Where | Used in the labs |
|---------|-------|------------------|
| Inline completions | Editor | Accepting, partially accepting, and steering C++ suggestions |
| Next edit suggestions | Editor | Small follow-up edits in headers and sources |
| Chat view | Side bar | Context, slash commands, checkpoints |
| Ask, Edit, Agent, Plan | Chat modes | Exploration, edits, multi-step work, planning |
| Copilot CLI | Terminal | Programmatic and scripted use, if approved |
| Copilot coding agent | github.com | Issue to pull request delegation in Lab 3 |

## 3. Review Repository Guidance

GitHub Copilot supports several ways to steer its behavior. The table lists every option, where it lives, and whether this workshop uses it. Check the [customization cheat sheet](https://docs.github.com/en/copilot/reference/customization-cheat-sheet) for current details.

| Option | Where it lives | Purpose | In this repo |
|--------|----------------|---------|--------------|
| Custom instructions, repository wide | `AGENTS.md` | Build and test commands, C++ rules, validation gates | Yes |
| Custom instructions, repository wide | `.github/copilot-instructions.md` | Repository-wide Copilot guidance | Yes |
| Custom instructions, path specific | `.github/instructions/*.instructions.md` | Rules scoped to C++ and CMake files | Yes |
| Custom instructions, personal or organization | GitHub account or organization settings | Preferences that follow a user or apply across repositories | No |
| Prompt files | `.github/prompts/*.prompt.md` | Reusable plan, review, and test prompts | Yes |
| Custom agents | `.github/agents/*.agent.md` | Specialist personas with a narrow tool set | Yes |
| Agent skills | `.github/skills/<skill-name>/SKILL.md` | Team procedures that Copilot loads when relevant | Yes |
| Hooks | `.github/hooks/*.json` | Shell commands that run at defined agent lifecycle events | No |
| MCP servers | `mcp.json` or repository MCP settings | Connections to external tools and data sources | Lab 2 |
| Subagents | Runtime process, no file | Isolated delegated work started by an agent | Lab 3 |
| Copilot connectors | GitHub account or organization settings | Project context from connected external services | No |
| Copilot memory | Personal and repository settings on GitHub | Facts and preferences that persist across sessions | No |

!!! warning "Do not change these yet"
    - Read them now.
    - Lab 1 asks you to curate them.
    - Changing them before the lab removes the before-and-after comparison.

## 4. Optional: Copilot CLI and MCP

- Install Copilot CLI only if it is on the approved software list.
- MCP servers used in Lab 2 must come from an organization allowlist.
- Use read-only scopes where possible. Do not paste tokens into prompts or files.

## Reference

### Customization file reference

Copilot reads customization files from fixed locations. The extension and scope decide when a file is loaded.

| File | Extension | Scope | Loaded |
|------|-----------|-------|--------|
| Repository instructions | `copilot-instructions.md` | Whole repository | Always |
| Path instructions | `*.instructions.md` | `applyTo` globs | When a matching file is in context |
| Agent facing rules | `AGENTS.md` | Every coding agent | Always |
| Prompt file | `*.prompt.md` | One invoked interaction | On demand |
| Custom agent | `*.agent.md` | One specialist role | When selected |
| Skill | `SKILL.md` | One packaged procedure | When the description matches |

- Repository files live under `.github/` and are reviewable in a pull request.
- Personal and organization instructions combine with these files and are not versioned here.
- `applyTo` is the field that narrows a path instruction. Keep the glob narrow.

```yaml
---
applyTo: "**/*.cpp, **/*.hpp"
---
```

!!! note "Surface differences"
    - Not every Copilot surface reads every file type. Check the customization cheat sheet linked above before relying on one.
    - Hooks and MCP servers need a separate policy review; they are not instruction files.

---

## 5. Tools Used

- **VS Code**: Copilot chat and agents
- **GitHub account**: entitlement and policy checks
- **Browser**: organization feature settings, if you have access

## Example

```markdown
# Repository instructions

- Configure, build, and test with the presets in `CMakePresets.json`.
- Boost.Test is header only. Do not add a test framework.
- Do not add network downloads to CMake.
- Copilot output is a proposal. A human reviews every diff.
- Keep prose in ASCII hyphens.
```

---

**Next:** [3. Verify the Environment](03-Verify-Environment.md)
