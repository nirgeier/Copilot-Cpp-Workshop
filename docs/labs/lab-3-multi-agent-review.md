# Lab 3 - Multi-agent delivery and AI code review

Aligned with Module 9 of the syllabus. 40 minutes.

## Starting point

`postprocessing_tests` fails in `ArgmaxIncludesFirstClass`. The `argmax`
implementation starts its search at index 1, so a highest score in class 0 is
ignored.

## Tasks

1. Delegate the fix to the Copilot coding agent through the Lab 3 issue, or use
   a local subagent with a narrow tool scope. Keep the task to one function.
2. In parallel, use a local subagent to add one focused test that documents the
   failure mode, for example a case where class 0 wins by a small margin.
3. Request a review using `.github/agents/cpp-reviewer.agent.md` as the
   checklist. Check ownership, bounds, integer width, and API stability.
4. Iterate through review comments. Verify the session log or agent trace.
5. Compare the two approaches on correctness, cost, and review effort. Record
   what the team should standardize.

## Definition of done

- The defect is fixed and covered by a regression test.
- No test was weakened or deleted to obtain a green run.
- The benchmark still runs on all three data samples.
- A human reviews and approves the final diff.

```bash
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/edge_benchmark data/valid.json 2000
```

## Evidence to record

The issue, both agent outputs, the review comments, the final test output, and
a short decision on which workflow to keep.
