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
    Copilot sees the files you open, the symbols you mention, the build commands in `CMakePresets.json`, and the compiler output you paste into chat. The same prompt can produce different answers with different context.

## 3. The C++ Workspace Copilot Sees

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
    The generated `compile_commands.json` gives tooling the exact include paths and warning flags. Without it, Copilot and the C/C++ extension may guess.

## 4. Supplying Context

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

## 5. Responsible Use

- Code referencing and public-code matching filters apply.
- Follow local rules for source-code context, sensitive data, and approved services.
- Copilot output is a proposal. A human decides what ships.

## 6. Summary

&emsp;✅&emsp;Identify the right Copilot surface for a task<br>
&emsp;✅&emsp;Explain what context Copilot sees in this repository<br>
&emsp;✅&emsp;Use checkpoints and history to keep changes reviewable

---

**Next:** [2. Context Engineering](02-Context-Engineering.md)
