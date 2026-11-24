# 1. Basic Alignment Session

!!! abstract "About this Guide"
    This 60-minute session brings everyone to the same baseline: what Copilot is, where it runs, what the C++ workspace looks like to it, and which behavior is allowed by policy.

## 1. What GitHub Copilot Is Today

- Copilot started as code completion and is now an agentic engineering platform.
- It assists across the lifecycle: understanding, planning, implementation, testing, debugging, and optimization.
- Plans and entitlements matter. Business and Enterprise differ in policy controls and premium requests.

| Capability | Example in this repository |
|------------|----------------------------|
| Completion | Finishing a CMake target or a test case |
| Chat | Explaining `preprocess` or `argmax` |
| Edit | Renaming a symbol across header and source |
| Agent | Closing a seeded defect with build and test validation |
| Plan | Producing an implementation plan before edits |

## 2. Where Copilot Runs

- VS Code and Visual Studio
- JetBrains CLion and Eclipse
- github.com and GitHub Mobile
- The terminal with Copilot CLI

!!! tip "Workspace context"
    - Copilot sees the files you open, the symbols you mention, the build commands in `CMakePresets.json`, and the compiler output you paste into chat.
    - The same prompt can produce different answers with different context.

## 3. The Chat UI: Modes and Permissions

The Copilot Chat view has two separate selectors at the bottom of the chat input. Your administrator may hide some options.

### Mode picker

| Mode | Picker text | What it does |
|------|-------------|--------------|
| Interactive | Step-by-step collaboration | Copilot works while you steer it and review each step. This is the lab default. |
| Plan | Plan first, execute when ready | Researches the task and drafts a plan before any edits. **Start Implementation** hands that plan to Interactive. |
| Autopilot | Works autonomously within permissions | Keeps working across turns until it decides the task is done, without another prompt. It does not change your permission level. |

### Permissions picker

| Level | What it means |
|-------|---------------|
| Manual permissions (default) | You review actions that were not pre-approved. It does not mean every command prompts. |
| Assisted permissions | A model decides which actions need your review. That reviewer can make mistakes. |
| Allow all | Skips ordinary tool confirmations, including destructive ones. It does not override organization policy or sandbox limits. |

- Autopilot is a mode, not a fourth permission level.
- Sandboxing for terminal is a separate toggle in the same picker.
- The chat input shows the current mode and permission level as chips.
- New sessions can start with a chosen level through `chat.defaultConfiguration` and `approvals`.

!!! warning "Workshop baseline"
    - Use Interactive with Manual permissions for the labs.
    - Plan belongs to Lab 2. Autopilot and Allow all need an explicit decision and a human check.

## 4. The C++ Workspace Copilot Sees

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- `CMakeLists.txt` defines the library, CLI, benchmark, and test target.
- `include/edge_inference/*.hpp` declares the public interfaces.
- `src/*.cpp` implements them.
- `tests/` holds Boost.Test suites registered with CTest.

!!! warning "compile_commands.json"
    - The generated `compile_commands.json` gives tooling the exact include paths and warning flags.
    - Without it, Copilot and the C/C++ extension may guess.

## 5. Supplying Context

| Mechanism | Use it for |
|-----------|-----------|
| `#file` and `#folder` mentions | Grounding an answer in a specific header or directory |
| `#codebase` | Whole-repository questions, used sparingly |
| Symbol selection | Asking about one function or class |
| Compiler output | Fixing the real error, not an imagined one |
| Test output and terminal logs | Evidence-driven debugging |
| Images and screenshots | UI questions, not C++ logic |

- Slash commands cover common actions: explain, fix, tests, docs, commit message, pull request description.
- Chat sessions keep history and checkpoints. Roll back an agent's edits when the direction is wrong.

## 6. Sessions Across Surfaces

A session groups the workspace, conversation, tool calls, and context for one task. A chat is a conversation inside a session.

| Surface | Find a previous session | Continue or recover |
|---------|--------------------------|---------------------|
| VS Code Chat | Sessions list at the top of the Chat view, grouped by time | Select a session, including Archived ones, then send a follow up |
| VS Code Agents window | Session list in the left sidebar, across workspaces | Select a session marked Done, then restore it before replying |
| Copilot CLI | Sidebar for recent local sessions, Sessions tab for full history | `copilot --continue`, `copilot --resume`, or `/resume` in session |
| github.com coding agent | Agent session list for the repository | Open the session log and the pull request it produced |

- In VS Code, every agent response is a checkpoint. **Restore Checkpoint** rolls back workspace files and the conversation to that point.
- Checkpoints do not undo terminal commands, network calls, or changes to external services. Use Git and the external system for those.
- Use `/fork` in a chat to explore an alternative while keeping the original conversation.
- Session history sync is experimental and policy controlled. Turning sync off does not stop model requests.

!!! note "What a session is not"
    - A session is not a branch. Separate chats in one workspace can edit the same files.
    - Copilot Memory and Spaces hold context across sessions. See lab 17.

## Reference

### Chat control reference

The chat input has two independent selectors. Administrator policy can hide options.

| Control | Value | Effect |
|---------|-------|--------|
| Mode | Interactive | Step by step with steering; lab default |
| Mode | Plan | Research and draft a plan before edits |
| Mode | Autopilot | Keep working across turns within current permissions |
| Permissions | Manual | Review actions that were not pre-approved |
| Permissions | Assisted | A model decides which actions need review |
| Permissions | Allow all | Skip ordinary confirmations, not policy or sandbox limits |

- Autopilot is a mode, not a fourth permission level.
- `chat.defaultConfiguration` and `approvals` can set the starting mode and level for new sessions.
- Terminal sandboxing is a separate toggle in the same picker.

!!! note "Workshop baseline"
    - Use Interactive with Manual permissions unless a lab says otherwise.
    - `#file`, `#folder`, `#codebase`, symbol selection, and pasted build output are the grounding controls in this repository.

---

## 7. Responsible Use

- Code referencing and public-code matching filters apply.
- Follow local rules for source-code context, sensitive data, and approved services.
- Copilot output is a proposal. A human decides what ships.

## Example

```text
Prompt: What does preprocess do, and which command proves it?
Attach: include/edge_inference/preprocessing.hpp
        src/preprocessing.cpp
        tests/test_preprocessing.cpp
        the failing CTest block

A grounded answer: "preprocess copies at most kInputSize (8) values into a
fixed width Tensor. tests/test_preprocessing.cpp asserts a [0, 1] range.
Prove it with cmake --preset debug, cmake --build --preset debug, then
ctest --preset debug --output-on-failure."

Without the attachments, the answer names no real file and guesses a command.
```

## 8. Summary

&emsp;✅&emsp;Identify the right Copilot surface for a task<br>
&emsp;✅&emsp;Explain what context Copilot sees in this repository<br>
&emsp;✅&emsp;Use checkpoints and history to keep changes reviewable

---

**Next:** [2. Context Engineering](02-Context-Engineering.md)
