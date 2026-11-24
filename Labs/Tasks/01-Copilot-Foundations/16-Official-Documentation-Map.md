# Task - Verify a Lab Against Official Docs

!!! abstract "About this Task"
    Use the documentation map to verify one claim in a lab, then record the access date and decide whether a correction is needed.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [19. Official Documentation Map](../../01-Copilot-Foundations/19-Official-Documentation-Map.md) |
| Scope | Documentation only. No C++ or customization file changes. |
| Inputs | One claim from any lab in this section, the linked official article |
| Constraints | Quote the documented text. Do not invent metrics or availability. |
| Deliverable | A verification note with claim, source, access date, and verdict |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Find the official article behind a lab claim.
- Check feature availability against the feature matrix when it matters.
- Record a correction without rewriting a whole lab.

## The Task

- Pick one claim from a lab, open its documentation map link, and verify it.
- If the claim moved, propose the smallest correction to the lab file.

## Task Steps

### Step 1 - Pick a checkable claim

- Choose a claim with a number, a location, or a support statement.
- Avoid vague claims.

**Expected evidence:** the claim written verbatim with its lab link.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

Good candidates: "Auto selection gives a 10 percent discount on model costs in paid plans", "Repository hooks live in `.github/hooks/*.json`", "Code review excludes tools without `annotations.readOnlyHint: true`", or "Data for a day is available within two full UTC days." Each is specific and easy to verify.

</details>

### Step 2 - Open the source article

Find the claim in the documentation map and open the linked article.

**Expected evidence:** the article URL and the relevant quoted sentence.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- For the discount claim, open the auto model selection article.
- For hooks, open the hooks concept article or the hooks reference.
- For code review tools, open the code review concept article.
- For metrics lag, open the Copilot usage metrics article.
- Quote one sentence rather than paraphrasing it.

</details>

### Step 3 - Check availability and plan limits

If the claim is about a feature, confirm the client, version, and plan.

**Expected evidence:** a support note naming client and version.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- Use the feature matrix for client and version support, and the plans article for entitlement.
- For example, plan mode is not available in Visual Studio at the time of writing, and MCP server policy applies to Business and Enterprise users but not individual plans.
- Record the state you observed instead of assuming it is universal.

</details>

### Step 4 - Record the verdict

Write a short note with claim, source, access date, and verdict.

**Expected evidence:** a four line note.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

```text
Claim: Auto selection gives a 10 percent discount on model costs in paid plans.
Source: https://docs.github.com/en/copilot/concepts/models/auto-model-selection
Access date: YYYY-MM-DD
Verdict: Confirmed for Copilot Chat and cloud agent. Quote the scope, not just the number.
```

- Use the real date you opened the article.
- Do not copy a date from this lab.

</details>

### Step 5 - Propose the smallest correction

- If the claim moved, change only the sentence that is wrong.
- Add the new source link to the map if needed.

**Expected evidence:** a one sentence correction proposal, or "no change needed".

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Example correction: change "premium requests" to "AI credits" where the current documentation uses credits, and keep the older term only where a plan still uses it.
- Do not rewrite the whole lab.
- Keep prose in ASCII hyphens and rebuild the site with `mkdocs build --config-file mkdocs.yml`.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No repository code changes are expected.

## Definition of Done

- [ ] One specific claim was chosen and quoted verbatim.
- [ ] The official article and access date are recorded.
- [ ] Client, version, or plan limits were checked where relevant.
- [ ] A verdict is written with the documented scope.
- [ ] Any correction is one sentence and traces to the new source.

## Summary

Trace a lab claim to an official article<br>
Check client, version, and plan support<br>
Record a verdict and make the smallest correction
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

Verification record template:

```markdown
| Lab | Claim checked | Official article | Access date | Verdict |
|-----|---------------|------------------|-------------|---------|
| 12 | 50 MCP server limit | docs.github.com/en/copilot/concepts/customizations/mcp | YYYY-MM-DD | current |
| 16 | preToolUse can deny | docs.github.com/en/copilot/reference/hooks-reference | YYYY-MM-DD | current |
| 5 | `metadata` is a string map | docs.github.com/en/copilot/concepts/customizations/agent-skills | YYYY-MM-DD | needs update |
```

Use the official article when a lab and a product UI disagree. Record the link and access date instead of copying a large excerpt into the repository.

- Use the official docs as the authority when a lab and a product UI disagree.
- Start with the feature and customization sections for the surface you use, then the model, agent, and tool references, then the review and administration pages.
- Record the links you relied on in your lab notes rather than copying large excerpts into this repository.

</details>


**Back:** [Tasks (Overview)](../README.md)
