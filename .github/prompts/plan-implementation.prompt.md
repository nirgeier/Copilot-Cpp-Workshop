---
description: Turn a workshop issue into a small, repository-grounded implementation plan
agent: Plan
---

# Plan an implementation

Use this prompt with a task or issue reference.

1. Read `AGENTS.md`, `.github/copilot-instructions.md`, and the files named in
   the task. Do not rely on memory of a similar repository.
2. State the current behavior using file and line references.
3. List the files to change and what changes in each one. Keep the public
   interface stable unless the task explicitly requires otherwise.
4. Name the validation gates: build, the relevant CTest entries, and the
   sanitizer preset.
5. List assumptions that are not supported by repository evidence and stop for
   human input instead of guessing.
6. End with a one paragraph definition of done.

Do not edit files. Do not add dependencies. Do not propose changes to the
seeded defects outside the scope of the task.
