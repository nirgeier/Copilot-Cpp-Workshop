# AI-Assisted Development with GitHub Copilot - C++ Labs

&emsp;🧠&emsp;A full-day, hands-on workshop for C++ development teams. **GitHub Copilot is the subject**. C++ is the working codebase: every demo and lab runs against the small CMake project in this repository.  
&emsp;⚙️&emsp;The day runs from 09:00 to 17:00 with an alignment session, advanced lectures, and three hands-on labs.  
&emsp;📘&emsp;C++ knowledge is assumed. No time is spent teaching C++ syntax.

---

## 🚀 Lab Series

| Lab | Title | Description |
|-----|-------|-------------|
| 000 | [Setup](./00-Setup/README.md) | Install tools, configure Copilot, and verify the starter repository |
| 001 | [Copilot Foundations](./01-Copilot-Foundations/README.md) | Alignment, context engineering, custom agents, Lab 1 |
| 002 | [Agent Mode and MCP](./02-Agent-Mode-and-MCP/README.md) | Models, agent mode, MCP, Lab 2 |
| 003 | [Multi-Agent and Review](./03-Multi-Agent-and-Review/README.md) | Subagents, coding agent, AI code review, Lab 3 |

## 🎯 Learning Objectives

&emsp;✅&emsp;Use Copilot surfaces deliberately: completion, chat, Edit, Agent, and Plan<br>
&emsp;✅&emsp;Engineer context with instructions, `AGENTS.md`, and prompt files<br>
&emsp;✅&emsp;Build custom agents and Agent Skills for a C++ team workflow<br>
&emsp;✅&emsp;Select models and drive agent mode with validation gates<br>
&emsp;✅&emsp;Extend Copilot with MCP under least-privilege access<br>
&emsp;✅&emsp;Orchestrate multi-agent delivery and review generated C++ diffs<br>
&emsp;✅&emsp;Measure, govern, and keep a human in the loop

## 🧩 The Starter Repository

The code next to this site is the prepared workshop repository:

| Path | Purpose |
|------|---------|
| `include/edge_inference/`, `src/` | Small C++17 inference library with a deterministic reference backend |
| `cli/` | Command line tool that runs one input through the inference path |
| `benchmark/` | Latency benchmark with p50 and p95 reporting |
| `tests/` | Boost.Test suites with two seeded failures for Lab 2 and Lab 3 |
| `data/` | Valid, boundary, and invalid input samples |
| `.github/` | Copilot instructions, path rules, prompts, a reviewer agent, and a skill |

!!! warning "Seeded failures are intentional"
    A clean checkout builds successfully but `preprocessing_tests` and `postprocessing_tests` fail. Those failures are the starting points for Lab 2 and Lab 3. `model_tests` passes from the start.

## 📁 How to Use These Labs

1. Start with **Lab 000** and verify your local environment.
2. Work through the labs in order. Each lab folder has an overview page and numbered steps.
3. Clone this repository and keep your work on a lab branch.
4. Follow the **definition of done** in each lab. Build and test output is evidence.

---

**Happy coding with Copilot!** 🧠✨
