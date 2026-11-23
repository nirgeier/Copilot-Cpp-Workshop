# 2. Configuring GitHub Copilot

!!! abstract "About this Guide"
    Connect Copilot to VS Code, confirm your entitlement, and review the organization controls that apply to the labs. Everything in this guide is subject to local policy.

## 1. Sign In to Copilot

1. Open VS Code.
2. Select the Copilot icon in the activity bar and choose **Sign in**.
3. Complete authentication with your approved GitHub account.
4. Confirm the Copilot status item shows your account and an active seat.

!!! tip "Seats and entitlements"
    Business and Enterprise seats differ in available features and policy controls. Your administrator decides which models, preview features, and MCP servers are enabled.

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

The repository already carries a customization layer that Lab 1 will extend:

| File | Purpose |
|------|---------|
| `AGENTS.md` | Build and test commands, C++ rules, validation gates |
| `.github/copilot-instructions.md` | Repository-wide Copilot guidance |
| `.github/instructions/*.instructions.md` | Path-specific rules for C++ and CMake files |
| `.github/prompts/*.prompt.md` | Reusable plan, review, and test prompts |
| `.github/agents/cpp-reviewer.agent.md` | Reviewer persona with a narrow tool set |
| `.github/skills/add-boost-test-suite/SKILL.md` | Team procedure for adding Boost.Test cases |

!!! warning "Do not change these yet"
    Read them now. Lab 1 asks you to curate them. Changing them before the lab removes the before-and-after comparison.

## 4. Optional: Copilot CLI and MCP

- Install Copilot CLI only if it is on the approved software list.
- MCP servers used in Lab 2 must come from an organization allowlist.
- Use read-only scopes where possible. Do not paste tokens into prompts or files.

## 5. Tools Used

- **VS Code**: Copilot chat and agents
- **GitHub account**: entitlement and policy checks
- **Browser**: organization feature settings, if you have access

---

**Next:** [3. Verify the Environment](03-Verify-Environment.md)
