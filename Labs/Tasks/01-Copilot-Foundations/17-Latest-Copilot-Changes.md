# Task - Verify the Latest Copilot Changes

!!! abstract "About this Task"
    Compare the November 2026 Copilot releases with your tenant, then record which items the workshop must teach. Keep evidence in your lab notes. No repository code changes.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [20. Latest Copilot Changes](../../01-Copilot-Foundations/20-Latest-Copilot-Changes.md) |
| Scope | Settings views and workshop notes. No C++ or customization file changes. |
| Inputs | Ten changelog articles, your model picker, your MCP settings, your code review settings |
| Constraints | Quote the article and date. Label public preview items. Do not enable a policy without approval. |
| Deliverable | One coverage matrix, one model list, one review settings record, one action list |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Identify which November 2026 Copilot changes apply to this workshop.
- Distinguish general availability from public preview.
- Turn each gap into a named lab update with an owner.

## The Task

Walk through each release item, check your tenant where access allows, and write a short evidence record. If an item is not available to you, write "not available" rather than inventing a result.

## Task Steps

### Step 1 - Inventory connectors

Open the connector list in the surface you use: Copilot CLI `/mcp` and the Connectors tab, the Copilot app Customize page, VS Code Agents > Customizations, or the github.com customization page.

**Expected evidence:** a table of the eight new services and whether your tenant shows them.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

The eight services are Box, Buildkite, Calendly, ClickUp, Mixpanel, Supabase, Webflow, and Wix. They are in public preview and join more than 25 existing services.

Keep this full record in `notes/connectors-2026-11.md`:

```markdown
# Connector inventory - 2026-11

Source: https://github.blog/changelog/2026-11-18-connect-supabase-box-calendly-and-more-to-copilot
Status: public preview

| Service | Visible in tenant | Needed for workshop | Decision |
|---------|-------------------|---------------------|----------|
| Box | yes/no | no | skip |
| Buildkite | yes/no | no | skip |
| Calendly | yes/no | no | skip |
| ClickUp | yes/no | no | skip |
| Mixpanel | yes/no | no | skip |
| Supabase | yes/no | no | skip |
| Webflow | yes/no | no | skip |
| Wix | yes/no | no | skip |

Admin checks:
- Editor preview features policy enabled for Business or Enterprise.
- MCP allowlist includes the connector or uses a wildcard.
- Service side enablement, for example Box MCP access.
```

For Business or Enterprise, an administrator must enable Editor preview features. If the MCP allowlist names connectors individually, add the ones you need.

</details>

### Step 2 - Check the new models

Open the model picker and record which of the newly announced models are available to your plan.

**Expected evidence:** a model list with plan and status.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary |

Keep this full record in `notes/models-2026-11.md`:

```markdown
# Model inventory - 2026-11

| Model | Status | Plans | Present in my picker | Workshop use |
|-------|--------|-------|----------------------|--------------|
| Gemini 4 Neon | GA | Pro+, Max, Business, Enterprise | yes/no | agentic, multistep tool use |
| GPT-6.2 Astra | GA | Pro+, Max, Business, Enterprise | yes/no | agentic and terminal work |
| GPT-6.2 Sol | GA | Pro+, Max, Business, Enterprise | yes/no | complex coding, in-depth review |
| MAI Code 2 | GA | Pro+, Max, Business, Enterprise | yes/no | deep debugging, multi-file work |
| MAI Code 2 Flash | GA | Free, Student, Pro, Pro+, Max, Business, Enterprise | yes/no | explanations, targeted edits |
| Claude Sonnet 5.5 in Fusion Max | Fusion component | Fusion users | yes/no | Fusion Max |
| GPT-6.1 Terra in Fusion High | Fusion component | Fusion users | yes/no | Fusion High |
| MAI-Code-2 in Fusion Standard | Fusion component | Fusion users | yes/no | Fusion Standard |
```

New models are enabled automatically under default model enablement unless an administrator turned off the global default or explicitly disabled them. Record what you see, not what the article promises.

</details>

### Step 3 - Verify code review additions

Open repository or organization settings under Copilot > Code review and check the four new controls.

**Expected evidence:** a settings record with each control and its state.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary |

Keep this full record in `notes/code-review-2026-11.md`:

```markdown
# Code review settings - 2026-11

Source: https://github.blog/changelog/2026-11-17-copilot-code-review-adaptive-effort-secret-detection-and-more

| Control | Status in release | State in my repo | Note |
|---------|-------------------|------------------|------|
| Adaptive effort | public preview | on/off | picks Lite, Balanced, or Max from PR risk |
| Cross-repository context | public preview | on/off | uses related public repos' default branches |
| Secret detection | public preview | on/off | deterministic 500+ types plus AI/ML detection |
| Repository insights | available | on/off | Insights tab > Repository insights |

Defaults: Balanced remains the default effort. Adaptive never exceeds the
configured maximum level.

Azure Repos code review is generally available with branch policies, custom
instructions, agent skills, audit log events, and Azure subscription billing.
```

Enable nothing without approval. The point of the task is an accurate inventory.

</details>

### Step 4 - Check team customizations

If you have an organization team, open its Customize Copilot tab and note the plugin controls.

**Expected evidence:** a short record of defaults, inheritance, and policy precedence.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary |

Keep this full record in `notes/team-customizations-2026-11.md`:

```markdown
# Team customizations - 2026-11

Status: generally available for organization teams on Business and Enterprise.

- Team maintainers and organization owners can select approved Agent Plugins
  as team defaults.
- Marketplaces come from built in, enterprise, or team added repositories.
- Defaults apply to direct members in VS Code, Copilot app, and Copilot CLI.
- Child teams do not inherit team defaults.
- Members can turn a plugin off where policy permits.
- Enterprise and organization policies take precedence over team choices.

Workshop decision: teach this in Lab 01 alignment and Lab 06 agent roles.
```

If you do not have an organization team, record "not available" and use the article as the source.

</details>

### Step 5 - Write the update plan

Turn the gaps into a short action list with an owner and a target lab.

**Expected evidence:** a table with item, gap, lab, and owner.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary |

```markdown
# Workshop update plan - 2026-11

| Item | Gap | Target lab | Owner |
|------|-----|------------|-------|
| Connectors | Eight new services not listed | Lab 12 | instructor |
| New models | Names absent from model lab | Lab 07 | instructor |
| Fusion | Effort tiers and benchmarks missing | Lab 07 | instructor |
| Copilot app | Azure DevOps, browser use, GHES | Lab 01 | instructor |
| Code review | Secret detection, cross-repo, Azure Repos | Lab 10 | instructor |
| JetBrains | Cloud sandbox, remote access, voice, diffs | Lab 13 | instructor |
| Agent 365 | External audit streaming | Lab 09 | admin |
| Team plugins | Team defaults and marketplaces | Lab 01, Lab 06 | org owner |
```

Mark each item public preview or GA using the changelog article. Rebuild the site with `mkdocs build --config-file mkdocs.yml` after any doc change.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

No C++ changes are expected. The two seeded failures remain.

## Definition of Done

- [ ] All ten changelog items were reviewed.
- [ ] Connector, model, and code review inventories are recorded with dates.
- [ ] Public preview items are labeled as such.
- [ ] Team customization availability was checked or marked "not available".
- [ ] One update plan row exists per gap, with a target lab and owner.
- [ ] No policy was changed without approval and no credential was committed.

## Summary

Verify November 2026 Copilot changes against your tenant<br>
Record models, connectors, and review controls with evidence<br>
Turn each workshop gap into an owned update

## Solution

Coverage matrix template for `notes/coverage-2026-11.md`:

```markdown
| Release item | Status | Visible in tenant | Workshop gap | Lab to update | Owner |
|--------------|--------|-------------------|--------------|---------------|-------|
| Connector expansion | public preview | yes/no | Connectors lab | 12 MCP and Connectors | <name> |
| New models | GA | yes/no | Model choice lab | 7 Choosing the Right Model | <name> |
| Adaptive code review effort | public preview | yes/no | Code review lab | 10 Copilot Code Review | <name> |
| Secret detection in review | public preview | yes/no | Governance lab | 03 Trust and Measurement | <name> |
```

The complete records are in the step solutions above. The expected outcome is a coverage matrix that names all ten releases, states which are public preview, and assigns each workshop gap to a lab and an owner. No C++ file changes.

**Back:** [Tasks (Overview)](../README.md)
