# 1. Multi-Agent Orchestration

!!! abstract "About this Guide"
    Multi-agent work means giving each agent a narrow context and a clear contract. The orchestrator decides what to delegate, when to stop, and what a human must approve.

## 1. Patterns

| Pattern | Use it for |
|---------|-----------|
| Orchestrator and workers | Split a large task into scoped subtasks |
| Parallel exploration | Research several hypotheses at once |
| Specialist review | Apply the C++ reviewer independently of the implementer |
| Isolated context | Keep a long debugging session from polluting a new task |

## 2. Subagents

- A subagent gets its own context window and a narrow instruction.
- Custom agents from `.github/agents/` can be used as subagents.
- Define the expected output before you delegate: a diff, a test, or a finding.

!!! tip "Good delegation"
    "Fix `argmax` in `src/postprocessing.cpp`, add one regression test in `tests/test_postprocessing.cpp`, and run `ctest --preset debug --output-on-failure -R postprocessing_tests`." This is better than "fix the C++ bug".

## 3. Local, Background and Cloud Agents

- **Local**: interactive, in your IDE, easiest to inspect.
- **Background**: runs while you work on something else.
- **Cloud**: the Copilot coding agent works in an Actions based environment and returns a pull request.

| Question | Consideration |
|----------|---------------|
| Where does it run? | Local, background, or cloud |
| What are its permissions? | Tool scope, token scopes, network access |
| How do you inspect it? | Session log, pull request, agent trace |
| Who approves? | A human, always |

## 4. Copilot CLI

- Use Copilot CLI for interactive and programmatic work.
- Slash commands, tool permissions, custom agents, and skills apply there too.
- Keep the same acceptance criteria you would use in the IDE.

## 5. The Copilot Coding Agent

- Assign an issue to the coding agent from the IDE, CLI, or github.com.
- Prepare its environment: compiler, CMake, Boost headers, and any approved caches.
- Iterate through pull request review comments. Read the session log before merging.

## 6. Spec-Driven Development

- Specification, plan, and tasks form the contract between humans and agents.
- In this repository, the issue body is the specification and the plan prompt produces the task list.

## 7. Summary

&emsp;✅&emsp;Choose a pattern that fits the task<br>
&emsp;✅&emsp;Scope a subagent's context and expected output<br>
&emsp;✅&emsp;Prepare the cloud agent environment for C++ builds

---

**Next:** [2. Lab 3 - Delivery and Review](02-Lab-3-Delivery-and-Review.md)
