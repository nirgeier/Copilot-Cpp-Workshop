# 2. Lab 3 - Delivery and Review

!!! abstract "About this Lab"
    **Time:** 15:55-16:35 (40 minutes). Fix the seeded argmax defect through a two-agent workflow, review both results, and record what your team should standardize. Issue #3 is your task record.

## 1. Problem Statement

`argmax` starts its search at index 1. A highest score in class 0 is ignored, so `PostprocessingTest.ArgmaxIncludesFirstClass` fails.

## 2. Tasks

- [ ] Delegate the fix to the Copilot coding agent through issue #3, or to a local subagent with a narrow tool scope.
- [ ] In parallel, use a second subagent to add one regression test where class 0 wins by a small margin.
- [ ] Request a review using `.github/agents/cpp-reviewer.agent.md` as the checklist.
- [ ] Check ownership, bounds, integer width, and API stability.
- [ ] Iterate through review comments and verify the session log or agent trace.
- [ ] Compare both approaches on correctness, cost, and review effort.

!!! warning "Keep the scope tight"
    Do not change preprocessing in this lab. Do not weaken the existing test. Treat the empty-input guard as part of the contract.

## 3. Definition of Done

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/edge_benchmark data/valid.json 2000
```

- [ ] The defect is fixed and covered by a regression test.
- [ ] All three CTest entries pass.
- [ ] No test was deleted, skipped, or weakened.
- [ ] A human reviewed and approved the final diff.

## 4. Evidence to Record

- The issue and both agent outputs
- The review comments and the final diff
- The test summary and benchmark output
- One decision: which workflow should the team keep

---

**Next:** [3. Trust, Security and Measurement](03-Trust-Security-Measurement.md)
