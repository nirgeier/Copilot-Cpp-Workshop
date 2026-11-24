# 7. Choosing the Right Model

!!! abstract "About this Lab"
    - Model choice is an engineering decision with a cost and a governance consequence.
    - Auto selection and pinned models behave differently on the same C++ task.



!!! note "Latest changes"
    The November 2026 releases added new models, connectors, review controls, and monitoring. See [20. Latest Copilot Changes](20-Latest-Copilot-Changes.md) for the current status.

## 1. The Model Picker

Copilot exposes several ways to select a model:

- **Auto** (or **Copilot Fusion** where available) routes each task to a model.
- **Task optimization** evaluates task complexity and system health, then routes work along conversation boundaries.
- **Tiers** bias the routing: `Efficiency` favors cost, `Balance` weighs cost, quality, and latency, and `Intelligence` favors quality.
- **Manual selection** pins a model for a chat session, a prompt file, or an agent profile.
- **Bring your own key** adds a provider model, subject to policy approval.

!!! note "Documented discount"
    - GitHub documents a 10 percent discount on model costs for paid plans when using Auto in Copilot Chat or Copilot cloud agent.
    - Check current pricing before quoting a number to your team.
    - Charges still depend on the model Auto selects.

Auto never chooses models outside your plan, models blocked by administrator policy, data-resident or FedRAMP restricted models, evaluation models that you have disabled, or locally installed models added to your picker.

## 2. Match Task to Capability

| Task in this repository | Starting choice | Why |
|-------------------------|-----------------|-----|
| Map the include graph | Fast model or Auto Efficiency | Retrieval and summarization, low ambiguity |
| Generate a Boost.Test case | Fast model | Local, patterned change with a clear spec |
| Rewrite a public template interface | Reasoning model or Auto Intelligence | ABI and ownership consequences |
| Diagnose a sanitizer finding | Reasoning model | Multi-step causal reasoning |
| Draft lab documentation | Fast model | Low risk, human reviewed |

!!! tip "Change the chat model, not the completion model"
    - In the IDE, changing the Copilot Chat model does not change the model used for inline suggestions.
    - Those are configured separately.
    - Record which surface you measured.

## 3. Where a Model Can Be Pinned

| Location | Effect |
|----------|--------|
| Model picker in chat | Current session or client default |
| `.prompt.md` frontmatter | One repeatable workflow |
| `.agent.md` frontmatter | One specialist role |
| Organization policy | Allowlist and default models for the org |

- Pin a model only when the team agrees it is right for the task.
- A pinned model can become stale as models change.

## Reference

### Model selection reference

| Mechanism | Where it is set | Limit |
|-----------|-----------------|-------|
| Auto | Model picker | Routes within plan, policy, and residency limits |
| Tier bias | Model picker | `Efficiency`, `Balance`, `Intelligence` |
| Manual pin | Picker, prompt file, agent profile | One session, one workflow, or one role |
| Bring your own key | Organization configuration | Needs policy approval |

- Auto does not choose blocked models, evaluation models you disabled, or data resident restricted models.
- GitHub documents a 10 percent cost discount for Auto on paid plans. Check current pricing before quoting it.
- Changing the chat model does not change the completion model.

A complete prompt file at `.github/prompts/model-choice.prompt.md`:

```markdown
---
description: Pick a Copilot model for a C++ task in this repository and explain the cost and policy trade-off
model: <approved-model-id>
---

# Choose a model for this task

Task: ${input:task_description}

1. Classify the task as retrieval, patterned code, cross-cutting C++ reasoning, or hard debugging.
2. Name the model you would start with: Auto with a tier, or a pinned model.
3. Cite the repository files that support the classification.
4. State the policy constraint: plan, allowlist, and data residency.
5. State the cost signal to record after the run.
6. Output: task class, model, files, policy, cost signal, confidence.

## Rules

- Do not invent a model name that is not in the picker.
- Do not paste a provider key into a prompt, a lab file, or the repository.
- Keep prose in ASCII hyphens.
```

A complete agent profile at `.github/agents/cpp-reasoning.agent.md`:

```markdown
---
description: Reasons about cross-cutting C++ changes and hard failures in the edge_inference repository
model: <approved-model-id>
tools: ["codebase", "search"]
---

# C++ reasoning specialist

You handle tasks that need multi-step causality: template and ABI changes,
ownership bugs, and sanitizer findings. You do not edit during analysis.

## Procedure

1. Restate the problem and cite the failing test or the sanitizer finding.
2. Read the public header before the implementation.
3. List at most three hypotheses with file and line for each.
4. Name the command that would disprove each hypothesis.
5. Propose the smallest change and the validation commands from `CMakePresets.json`.

## Output

- Blocking findings first, with file and line.
- Validation commands from `CMakePresets.json`.
- State clearly when evidence is missing.

## Rules

- Replace `<approved-model-id>` with a model ID from your allowlisted picker.
- Do not add dependencies or network downloads.
- Keep prose in ASCII hyphens.
```

Replace `<approved-model-id>` with a model ID from your allowlisted picker.

!!! note "Governance"
    - Use a model only if it is allowlisted for your organization.
    - Do not paste a provider key into a prompt, a lab file, or the repository.

## Review input reference

Each input that shapes model choice has its own tab with a concrete example.

=== "Task prompt"

    ```text
    Task: Explain the failing postprocessing_tests assertion and list three
    plausible causes.
    Attach: tests/test_postprocessing.cpp, src/postprocessing.cpp, its header,
            the failing CTest block.
    Do not edit. Output: causes with file and line, plus a disproof command.
    ```

=== "Model picker and tier"

    ```text
    Picker: Auto
    Tier: Intelligence
    Reason: multi-step causal reasoning across a header, a source, and a test.
    Record: displayed model, surface, and credits consumed if visible.
    ```

=== "Prompt file pin"

    ```markdown
    ---
    description: Triage a failing CTest case with a pinned model
    model: <approved-model-id>
    ---

    Quote the exact assertion. Cite file and line. Do not edit.
    ```

=== "Agent profile pin"

    ```markdown
    ---
    description: Reasons about C++ failures in edge_inference
    model: <approved-model-id>
    tools: ["codebase", "search"]
    ---

    Blocking findings first, with file and line. No edit tools.
    ```

=== "Organization policy"

    ```json
    {
      "default": "auto:balance",
      "allowed": ["auto", "fast-approved-model-id"],
      "denied": ["preview-evaluation-model"]
    }
    ```

=== "Usage and cost"

    ```text
    Individual: billing > AI usage > credits by model.
    Business: Copilot settings > Usage this cycle.
    Record: model, credits, and the fact that per-prompt cost is not shown.
    ```

=== "Repository context"

    ```text
    CMakePresets.json: debug, release, sanitizers, base (hidden)
    include/edge_inference/*.hpp: public contract
    src/*.cpp: implementation
    tests/: Boost.Test suites and the two seeded failures
    ```


---

## 4. Cost Signals

- AI credit consumption is shown per model on the individual AI usage page.
- Organizations and enterprises see shared credit consumption and budgets.
- IDEs show plan allowance and reset dates in the Copilot status control.
- Higher effort code reviews and agent sessions consume more credits than a chat question.

- Use the signals to compare your own tasks.
- Do not treat one workshop measurement as a team wide productivity metric.

## Example

```markdown
---
description: Pick a Copilot model for a C++ task in this repository and explain the cost and policy trade-off
model: <approved-model-id>
---

Task: ${input:task_description}

Classify the task, name the starting model, cite the supporting files,
state the policy constraint, and name the cost signal to record.
```

## 5. Summary

&emsp;✅&emsp;Explain Auto, tiers, Fusion, and manual pinning<br>
&emsp;✅&emsp;Match model capability to task difficulty with evidence<br>
&emsp;✅&emsp;State the policy and budget constraints on model choice

---

**Next:** [8. Debugging with Copilot](08-Lab-Debugging-with-Copilot.md)
