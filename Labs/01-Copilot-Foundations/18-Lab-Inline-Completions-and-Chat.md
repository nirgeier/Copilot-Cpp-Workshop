# 18. Inline Completions and Chat

!!! abstract "About this Lab"
    - Inline completions and chat serve different jobs in the editor.
    - Grounding with files, symbols, and real output changes the answer quality.


## 1. Two Surfaces, Two Jobs

| Surface | Best for | Weak for |
|---------|----------|----------|
| Inline completions | Local, patterned code as you type | Decisions that need repository wide context |
| Chat | Explanation, cross file questions, planning | Typing every line yourself |

- Changing the chat model does not change the completion model.
- They are configured separately, and the available models depend on the plan and client.

- Copilot is available in VS Code, Visual Studio, JetBrains IDEs, Eclipse, Xcode, github.com, GitHub Mobile, and the terminal.
- Capabilities differ by surface and plan.

## 2. Grounding Mechanisms

| Mechanism | Use it for |
|-----------|------------|
| `#file` or `@` path mention | One header or source file |
| Selection | One function or class |
| `#codebase` | Whole repository questions, used sparingly |
| Build and test output | The real error, not an imagined one |
| Images and screenshots | UI questions, not C++ logic |

!!! tip "Smallest sufficient context"
    - A short prompt naming `src/preprocessing.cpp`, its header, and the failing assertion beats a long description of the repository.
    - Extra context adds noise and cost.

## Reference

### Grounding mechanism reference

| Mechanism | Scope | Best for | Limit |
|-----------|-------|----------|-------|
| Selection | One function or class | Local rename or completion | The right symbol must be selected |
| `#file` or `@` path | One file | Header grounded answers | One file per mention |
| `#codebase` | Whole repository | Broad orientation | Costly and noisy, use sparingly |
| Build and test output | One failing command | Real error diagnosis | Paste the whole block |
| Space | Curated sources | Shared workshop context | Sources must be reviewed |
| Image or screenshot | One UI question | Visual issues | Not useful for C++ logic |

- Inline completions suit local, patterned code. Chat suits cross file questions.
- Changing the chat model does not change the completion model.
- Extra context adds noise and cost. Name the smallest sufficient evidence.

```text
What does preprocess do, and which command proves it?
Use include/edge_inference/preprocessing.hpp and tests/test_preprocessing.cpp.
```

!!! note "Review"
    - A completion can compile and still violate ownership, bounds, signedness, or exception safety rules.
    - Apply `docs/review-checklist.md` to every accepted block.

---

## 3. Responsible Use

- Code referencing and public code matching filters may apply, depending on plan and policy.
- Follow local rules for source code context, sensitive data, and approved services.
- Do not paste tokens, customer data, or unreleased source into a chat.
- Copilot output is a proposal. A human decides what ships.

## Example

```text
Bare chat: "What does preprocess do, and which command proves it?"
  -> generic description, guessed command.

Grounded chat: same question plus
  include/edge_inference/preprocessing.hpp
  src/preprocessing.cpp
  tests/test_preprocessing.cpp and the failing CTest block
  -> names src/preprocessing.cpp, the real assertion at line 23, and
     ctest --preset debug --output-on-failure.
```

## 4. Summary

Choose completion for local patterns and chat for grounded questions<br>
Attach the smallest sufficient evidence<br>
Review every suggestion against the C++ checklist

**Back:** [Foundations overview](README.md) and **Next:** [Lab 02 overview](../02-Agent-Mode-and-MCP/README.md)
