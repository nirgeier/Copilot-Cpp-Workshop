# C++ review checklist for AI generated changes

Use this for every Copilot diff in this repository. Copilot output is a
proposal, not an authority.

## Correctness

- [ ] Every claimed API exists in the included headers. No invented STL calls.
- [ ] Array and vector indexing is bounds checked before use.
- [ ] Integer widths and signedness are safe for the input sizes in `data/`.
- [ ] The three data samples behave as documented, including the invalid one.

## Ownership and lifetime

- [ ] No raw `new` or `delete` in new code. RAII and standard containers only.
- [ ] References and pointers do not outlive their owners.
- [ ] Exception paths do not leak resources or leave objects half updated.

## Interfaces and build

- [ ] Public headers in `include/edge_inference/` stay stable unless the issue
      asks for a change.
- [ ] `const`-correctness is preserved and `noexcept` is not added casually.
- [ ] `CMakeLists.txt` and presets still configure without network access.
- [ ] No new third party dependency without an approved offline package.

## Validation evidence

- [ ] Build output is attached.
- [ ] `ctest --preset debug --output-on-failure` output is attached.
- [ ] Sanitizer run output is attached where the toolchain supports it.
- [ ] No test was deleted, skipped, or weakened to make the run green.
- [ ] A human reviewer approved the final diff.

## Governance

- [ ] No secrets, client data, or model binaries were added.
- [ ] Tool scope was least privilege, and approval checkpoints were respected.
- [ ] Text uses ASCII hyphens, never em dashes.
