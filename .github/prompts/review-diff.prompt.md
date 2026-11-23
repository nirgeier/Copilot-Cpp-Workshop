---
description: Review the current diff against the C++ checklist and validation evidence
agent: cpp-reviewer
---

# Review the current diff

1. Read `docs/review-checklist.md` and the repository instructions.
2. Inspect only the current diff and the files it touches.
3. Check correctness, ownership and lifetimes, bounds, integer width,
   exception safety, and interface stability.
4. Check that every API used actually exists in the included headers.
5. Check that no test was deleted, skipped, or weakened.
6. Ask for the build and CTest output. If only a test count is reported, treat
   the validation as incomplete.
7. Report findings as blocking or non-blocking, each with a file and line.

Do not accept a change because the tests pass. Pass tests are necessary, not
sufficient.
