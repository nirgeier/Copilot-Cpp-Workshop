# Task - Choose the Right Model

!!! abstract "About this Task"
    - Run the same two C++ prompts through Auto and a pinned model.
    - Compare the answers and costs, then write one team rule.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [7. Choosing the Right Model](../../01-Copilot-Foundations/07-Lab-Choosing-the-Right-Model.md) |
| Scope | Chat sessions and notes. No repository code changes. |
| Inputs | Two fixed prompts, the model picker, the AI usage page |
| Constraints | Do not paste keys. Respect the allowlist. Do not claim a number that is not documented. |
| Deliverable | A comparison table and one sentence of team guidance |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Explain Auto selection, tiers, Fusion, and manual pinning.
- Match task difficulty to model capability with evidence.
- State policy and cost constraints on model choice.

## The Task

- Use the same prompt and the same attached files in two fresh chats: one with Auto and one with a pinned model.
- Check every repository claim.
- Record credits if your plan exposes them.
- Finish with a rule your team can apply.

## Task Steps

### Step 1 - Prepare the comparison

- Write the two prompts down verbatim and decide which files to attach to each.
- Both runs must use identical inputs.

**Expected evidence:** a note with the two prompts and the attached paths.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

Prompt A: "Map the CMake targets, the public headers, and the exact build and test commands in this repository."

Prompt B: "Explain the failing `postprocessing_tests` assertion and list three plausible causes."

- Attach `CMakePresets.json` for A.
- Attach `src/postprocessing.cpp`, its header, and the failing assertion for B.
- Do not add more context to one run than the other.

</details>

### Step 2 - Run Auto and pinned sessions

- Run both prompts with Auto, then repeat with a pinned model.
- Note the model name shown in the picker.

**Expected evidence:** four responses with the model recorded.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- For a simple mapping task, Auto Efficiency or a fast model is usually sufficient.
- For the causal diagnosis, Auto Intelligence or a reasoning model is more appropriate.
- If your surface shows Copilot Fusion instead of Auto, select an effort level and record it.

Two complete customization files make the pin repeatable. Create `.github/prompts/model-choice.prompt.md`:

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

Create `.github/agents/cpp-reasoning.agent.md`:

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

Replace `<approved-model-id>` with an ID from your allowlisted picker. Changing the chat model does not change the inline completion model, so record which surface you used.

</details>

### Step 3 - Check claims against the repository

- Mark each claim as verified, wrong, or unverifiable.
- Verify with a file or a command, not with intuition.

**Expected evidence:** a table with a row per claim.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

| Claim type | How to verify |
|------------|---------------|
| File path exists | Open the path or use search |
| Build command | Check `CMakePresets.json` |
| Cause of failure | Rerun `ctest --preset debug --output-on-failure` |
| API name | Find it in a header in `include/edge_inference/` |

- Mark any invented API or guessed command as wrong.
- Do not accept an answer just because it sounds confident.

Record the four runs with a complete `scripts/record-model-comparison.py`:

```python
#!/usr/bin/env python3
"""Render a model comparison table from a JSON file into Markdown."""
import argparse
import json
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path, help="JSON file with a 'runs' list")
    parser.add_argument("output", type=Path, help="Markdown file to write")
    args = parser.parse_args()

    data = json.loads(args.input.read_text(encoding="utf-8"))
    lines = [
        "| Task | Surface | Model shown | Verified | Wrong | Credits |\n",
        "|------|---------|-------------|----------|-------|---------|\n",
    ]
    for run in data.get("runs", []):
        cells = [
            str(run.get("task", "")),
            str(run.get("surface", "")),
            str(run.get("model", "")),
            str(run.get("verified", 0)),
            str(run.get("wrong", 0)),
            str(run.get("credits", "n/a")),
        ]
        cells = [c.replace("|", "\\|").replace("\n", " ") for c in cells]
        lines.append("| " + " | ".join(cells) + " |\n")

    args.output.write_text("".join(lines), encoding="utf-8")
    print(f"wrote {args.output} with {len(data.get('runs', []))} runs")


if __name__ == "__main__":
    main()
```

Example `model-comparison.json` input:

```json
{
  "runs": [
    {
      "task": "Map CMake targets and headers",
      "surface": "VS Code chat",
      "model": "Auto Balance",
      "verified": 6,
      "wrong": 0,
      "credits": "n/a"
    },
    {
      "task": "Diagnose postprocessing_tests",
      "surface": "VS Code chat",
      "model": "pinned reasoning model",
      "verified": 4,
      "wrong": 1,
      "credits": "n/a"
    }
  ]
}
```

Run it with `python3 scripts/record-model-comparison.py model-comparison.json model-comparison.md`.

</details>

### Step 4 - Read cost and policy signals

- Open the AI usage view available on your plan.
- Note credits by model and any budget or allowlist constraint.

**Expected evidence:** a short note with what the view does and does not show.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- Individual users see included credits, additional usage, a model chart, and a per model breakdown.
- Business and Enterprise users see usage this cycle in Copilot settings.
- IDEs show plan allowance and reset dates.
- These views show credits by model, not credits per prompt or session.
- GitHub documents a 10 percent discount for Auto in Copilot Chat and cloud agent on paid plans.
- Quote the documentation, not a local estimate.

</details>

### Step 5 - Write the team rule

State when the team uses Auto and when it pins a model.

**Expected evidence:** one sentence plus the reason.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- "Use Auto Balance for everyday chat; pin a reasoning model for sanitizer and ABI investigations, and pin a fast model for test scaffolding and documentation." The reason is that routing should reserve high cost reasoning for tasks where it changes the answer.
- Add: "Never use a model outside the organization allowlist."

Package the rule as a complete skill at `.github/skills/model-selection/SKILL.md`:

```markdown
---
name: model-selection
description: Choose a GitHub Copilot model for a C++ task in this repository. Use when deciding between Auto and a pinned model, or when weighing cost and policy constraints.
---

# Model selection

## Procedure

1. Name the task in one sentence.
2. Classify it as retrieval or summarization, patterned code, cross-cutting C++ reasoning, or hard debugging.
3. Check policy: is the model allowlisted and available on this plan?
4. Start with Auto. Use `Efficiency` for retrieval and boilerplate, `Balance` for everyday work, and `Intelligence` for complex reasoning.
5. Pin a model in a prompt file or an agent profile only when the team agrees and the task repeats.
6. Record the displayed model, the surface, and the credits consumed if visible.
7. Verify every repository claim against a file before accepting the answer.

## Decision table

| Task in this repository | Starting choice |
|-------------------------|-----------------|
| Map CMake targets and public headers | Fast model or Auto Efficiency |
| Generate a Boost.Test case | Fast model |
| Rewrite a public template interface | Reasoning model or Auto Intelligence |
| Diagnose a sanitizer finding | Reasoning model |

## Rules

- Never use a model outside the organization allowlist.
- Do not paste a provider key into a prompt, a lab file, or the repository.
- Changing the chat model does not change the inline completion model.
- Keep prose in ASCII hyphens.
```


</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No C++ file changes are expected in this task.

## Definition of Done

- [ ] Four responses were recorded with the displayed model.
- [ ] Prompts and context were identical across compared runs.
- [ ] Every repository claim was marked verified, wrong, or unverifiable.
- [ ] Cost and policy limits are stated from documentation.
- [ ] No key or credential was pasted into chat or the repository.
- [ ] One team rule is written with a reason.

## Summary

&emsp;✅&emsp;Compare Auto and pinned models on identical inputs<br>
&emsp;✅&emsp;Verify answers against real files and commands<br>
&emsp;✅&emsp;Write a team rule grounded in capability and cost

## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

The complete deliverables are the four files shown in the step solutions:
`.github/prompts/model-choice.prompt.md`, `.github/agents/cpp-reasoning.agent.md`,
`scripts/record-model-comparison.py`, and the skill below.

```markdown
---
name: model-selection
description: Choose a GitHub Copilot model for a C++ task in this repository. Use when deciding between Auto and a pinned model, or when weighing cost and policy constraints.
---

# Model selection

## Procedure

1. Name the task in one sentence.
2. Classify it as retrieval or summarization, patterned code, cross-cutting C++ reasoning, or hard debugging.
3. Check policy: is the model allowlisted and available on this plan?
4. Start with Auto. Use `Efficiency` for retrieval and boilerplate, `Balance` for everyday work, and `Intelligence` for complex reasoning.
5. Pin a model in a prompt file or an agent profile only when the team agrees and the task repeats.
6. Record the displayed model, the surface, and the credits consumed if visible.
7. Verify every repository claim against a file before accepting the answer.

## Decision table

| Task in this repository | Starting choice |
|-------------------------|-----------------|
| Map CMake targets and public headers | Fast model or Auto Efficiency |
| Generate a Boost.Test case | Fast model |
| Rewrite a public template interface | Reasoning model or Auto Intelligence |
| Diagnose a sanitizer finding | Reasoning model |

## Rules

- Never use a model outside the organization allowlist.
- Do not paste a provider key into a prompt, a lab file, or the repository.
- Changing the chat model does not change the inline completion model.
- Keep prose in ASCII hyphens.
```

The expected outcome is unchanged: two identical prompts run with Auto and a pinned model, every repository claim checked against a file, the comparison table written by the script, and no key or credential in the repository.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Debug with Real Evidence](05-Debugging-with-Copilot.md)
