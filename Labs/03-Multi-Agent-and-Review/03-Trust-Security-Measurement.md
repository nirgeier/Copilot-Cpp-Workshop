# 3. Trust, Security, Governance and Measurement

!!! abstract "About this Guide"
    - The final session turns workshop practice into team policy.
    - Copilot output stays a proposal until a human accepts it with evidence.

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
    - Copilot code review, code scanning autofix, and secret scanning help, but none replaces human review.
    - See `docs/review-checklist.md` in the repository for the full C++ checklist.

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

## Reference

### Safeguard reference

| Risk | Safeguard | Owner |
|------|-----------|-------|
| Fabricated API | Header first, compile with `-Wall -Wextra -Wpedantic` | Implementer |
| Missing edge case | Boundary test in a Boost.Test suite | Test author |
| Silent behavior change | Contract review in `docs/review-checklist.md` | Reviewer |
| Prompt injection | Treat issue and tool output as untrusted data | Orchestrator |
| Tool poisoning | Approved registries and narrow toolsets | Administrator |
| Secret exposure | Secret scanning and no tokens in prompts | Everyone |

| Control | Where it is set |
|---------|-----------------|
| Feature enablement | Organization settings |
| Model allowlist | Organization settings |
| Content exclusion | Repository or organization settings |
| Required reviewers | Repository branch protection |

!!! note "Human decisions"
    - Architecture, safety, performance targets, and release readiness stay with people.
    - A passing build and test run is evidence, not approval.

---

## 5. What Remains Human

- Architecture, safety, performance targets, and release readiness are human decisions.
- Copilot can propose a measured optimization after Lab 3, but an engineer decides whether the trade-off is acceptable.

## Example

```json
{
  "action": "copilot.content_exclusion_changed",
  "actor": "org-admin",
  "timestamp": "2026-11-24T09:15:00Z",
  "repository": "nirgeier/Copilot-Cpp-Workshop",
  "excluded_paths": ["config/secrets/**", "data/customer/**"]
}
```

Read this entry from the organization audit log. Confirm the actor and that
the excluded paths match a documented decision. Do not paste sensitive paths
into a lab file or a chat prompt.

## 6. Course Close

- Rerun all commands from Lab 00 on your final branch.
- Confirm all three CTest entries pass.
- Archive your notes, plans, diffs, and agent traces with the workshop record.

---

**Back:** [Home](../README.md)
