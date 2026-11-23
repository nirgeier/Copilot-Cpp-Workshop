# 3. Trust, Security, Governance and Measurement

!!! abstract "About this Guide"
    The final session turns workshop practice into team policy. Copilot output stays a proposal until a human accepts it with evidence.

## 1. Common AI Coding Failure Modes

| Failure mode | C++ example in this repository |
|--------------|--------------------------------|
| Fabricated API | Calling a Boost.Test matcher that does not exist |
| Stale library usage | Using an ONNX Runtime call removed in later versions |
| Missing edge cases | Forgetting the constant-input case in normalization |
| Silent behavior change | Normalizing inputs without updating the model contract |
| Undefined behavior | Off-by-one indexing or unsafe casts |

## 2. Agent Specific Risks

- Prompt injection through issue text, comments, or tool output
- Tool poisoning through untrusted MCP servers
- Over-broad permissions and auto-approval rules
- Secrets exposure in prompts, logs, or committed files

!!! warning "Layered safeguards"
    Copilot code review, code scanning autofix, and secret scanning help, but none replaces human review. See `docs/review-checklist.md` in the repository for the full C++ checklist.

## 3. Enterprise Controls

- Feature enablement for chat, agents, previews, MCP, and the coding agent.
- Model allowlists, content exclusion, and audit logs.
- Data handling commitments for Business and Enterprise plans.
- Required reviewers and branch protection on the repository.

## 4. Measuring Impact

- Copilot usage and adoption signals
- Premium request analytics and budgets
- Time saved on boilerplate versus time spent reviewing
- Defect escape rate in AI generated changes

| Measure | What it tells you |
|---------|-------------------|
| Acceptance rate | How often suggestions are kept |
| Review rework | How much generated code must be corrected |
| Build and test failures | Whether validation gates catch issues |
| Premium requests | Whether model choice is economical |

## 5. What Remains Human

Architecture, safety, performance targets, and release readiness are human decisions. Copilot can propose a measured optimization after Lab 3, but an engineer decides whether the trade-off is acceptable.

## 6. Course Close

- Rerun all commands from Lab 00 on your final branch.
- Confirm all three CTest entries pass.
- Archive your notes, plans, diffs, and agent traces with the workshop record.

---

**Back:** [Home](../README.md)
