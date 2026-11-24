# Task - Review Copilot Usage Internally

!!! abstract "About this Task"
    - Open the administrator views available to you and turn adoption signals into one enablement action.
    - No productivity claims without evidence.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [9. Reviewing Copilot Usage Internally](../../01-Copilot-Foundations/09-Lab-Reviewing-Copilot-Usage-Internally.md) |
| Scope | GitHub settings and dashboards only. Nothing is committed to the repository. |
| Inputs | Individual usage page, organization activity report, Copilot metrics dashboards, audit log |
| Constraints | Do not copy personal usage data or credentials into the repository. Do not equate activity with productivity. |
| Deliverable | A one page brief with four views and one action |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Distinguish billing, activity, metrics, and audit views.
- Read adoption cohorts and coverage limits before drawing a conclusion.
- Convert a signal into one concrete enablement step.

## The Task

- Open every view your access allows.
- Record what each answers, its limits, and one action supported by the data.
- If you lack admin access, use the documented examples and state the access limitation explicitly.

## Task Steps

### Step 1 - Separate the four views

Write down which question each view answers and who owns it.

**Expected evidence:** a four row table.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

| View | Question | Owner |
|------|----------|-------|
| Individual AI usage | What did I consume and on which models | Developer |
| Organization activity report | Who last used Copilot and how seats are assigned | Org owner |
| Usage metrics dashboards | How teams adopt Copilot and how it relates to PR flow | Admin or decision maker |
| Audit log | Who changed a policy or content exclusion | Admin |

Mixing these leads to wrong conclusions, for example treating credits by model as a per task cost report.

</details>

### Step 2 - Open the views you can access

- For Business or Enterprise, go to profile picture, Copilot settings, Usage this cycle.
- For Individual, go to billing settings, AI usage.
- Open the organization activity view and the metrics dashboards if you have access.

**Expected evidence:** a note listing each view opened and the access level.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

- The individual view shows included credits, additional usage, a model chart, and a per model breakdown.
- The organization overview shows assigned seats and estimated monthly cost, and the activity report downloads as CSV.
- The REST API can retrieve seat information and per user details.
- IDEs show allowance and reset dates in the Copilot status control.
- If a view is blocked, write "no access" rather than inventing data.

</details>

### Step 3 - Record the coverage limits

List at least four limits that affect interpretation.

**Expected evidence:** four bullets with a source article.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

- The AI usage page does not trace credits to specific prompts or sessions.
- Detailed IDE breakdowns need supported clients with telemetry enabled.
- Data for a day is available within two full UTC days after that day closes.
- Organization totals can overlap because a user can belong to several organizations. Do not add them into an enterprise total.
- Usage metrics measure activity, not license assignments.
- Dashboard comparisons show associations, not proof of causation.

</details>

### Step 4 - Trace a configuration change

- In the organization or repository settings, find the last content exclusion change.
- Follow its timestamp into the audit log and record the actor and the resulting excluded paths.

**Expected evidence:** one audit log entry with actor, time, and excluded paths.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- At the bottom of the settings page you will see who last changed content exclusions and when.
- Clicking the time opens the audit log filtered on `copilot.content_exclusion_changed`.
- Expand the entry to see `excluded_paths` after the change.
- If your organization has no change to show, write that explicitly.
- Do not paste the paths into the repository if they reference sensitive locations.

</details>

### Step 5 - Write the enablement brief

- Use four sections: adoption, depth, cost, next step.
- The next step must be one training session or one policy change tied to a signal.

**Expected evidence:** a one page brief in your workshop notes.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Example: "Adoption: seats assigned and active users are rising.
- Depth: usage is concentrated in completions, with little agent mode use.
- Cost: credits are dominated by one model.
- Next step: run a context engineering and mode selection clinic, then review adoption cohorts after two weeks." Add the sentence: "These are associations, not proof that Copilot changed throughput."

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- No repository code changes are expected.
- The seeded failures remain.

## Definition of Done

- [ ] All four views are named correctly and not confused with each other.
- [ ] At least one real view was opened, with access level recorded.
- [ ] Four coverage or lag limits are listed.
- [ ] One policy or content exclusion change was traced where access allows.
- [ ] The brief contains one action tied to a signal.
- [ ] No personal usage data or credentials were copied into the repository.

## Summary

Separate billing, activity, metrics, and audit views<br>
State coverage limits before interpreting a trend<br>
Produce one evidence based enablement action
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

The completed `notes/enablement-brief.md`:

```markdown
# Copilot enablement brief

## Adoption
- Seats assigned: <from organization activity>
- Active users and trend: <from usage metrics>
- Coverage note: client telemetry must be enabled for IDE detail

## Depth
- Surfaces actually used: completions, chat, agent, code review
- Adoption cohort with the lowest acceptance rate: <name>

## Cost
- Credits by model: <from individual AI usage or metrics API>
- Budget constraint: <plan or organization limit>

## Next step
- Action: one context engineering session for the low-acceptance cohort
- Signal: acceptance rate and review rework from the dashboard
```

- Name the four views: individual usage, organization activity, usage metrics dashboards, and configuration change review.
- Open at least one dashboard or report you have access to and record coverage and lag limits.
- Trace one content exclusion or policy change in the audit log where access allows, and tie the final action page to the signal that motivated it.
- Do not copy personal usage data or credentials into the repository.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Copilot Code Review](07-Copilot-Code-Review.md)
