# 1. Models, Cost and Governance

!!! abstract "About this Guide"
    Model choice is an engineering decision. Pick the cheapest model that can do the task reliably, and pin it in a prompt file or agent when the team agrees on a standard.

## 1. The Model Picker

- Frontier reasoning models handle cross-cutting template changes, ABI concerns, and hard debugging.
- Fast lightweight models handle boilerplate, test scaffolding, and documentation.
- Auto selection is convenient, but override it when the task demands deeper reasoning.

| Task in this repository | Suggested choice |
|-------------------------|------------------|
| Explore the include graph | Fast model |
| Rewrite a public template interface | Reasoning model |
| Generate a Boost.Test case | Fast model |
| Diagnose a sanitizer finding | Reasoning model |
| Write lab documentation | Fast model |

## 2. Premium Requests and Multipliers

- Some models consume premium requests at a higher multiplier.
- Plan usage across a workshop day so the team does not exhaust seats.
- Measure on your own tasks: same prompt, same context, evidence-based comparison.

!!! tip "Pinning a model"
    Prompt files and custom agents can declare a preferred model. Use that only when the team has agreed the model is right for the task.

## 3. Bring Your Own Model

- Some setups allow an organization-provided model endpoint.
- This changes data-handling and governance obligations.
- Get approval before enabling it. Do not paste keys into prompts or repository files.

## 4. Organization Policies

- Feature enablement: chat, agents, preview features, and coding agent.
- Model allowlists and preview model access.
- MCP server registry, toolsets, and read-only modes.
- Content exclusion, audit logs, and retention settings.

!!! warning "Governance is a control, not a suggestion"
    A model or tool that is not approved cannot be used in the lab, even if it produces a better answer. Challenge any suggestion that would move source outside the governed environment.

## 5. Summary

&emsp;✅&emsp;Match model capability to task difficulty<br>
&emsp;✅&emsp;Explain premium request cost and multipliers<br>
&emsp;✅&emsp;State which policies constrain model and tool choice

---

**Next:** [2. Agent Mode, Tools and MCP](02-Agent-Mode-and-MCP.md)
