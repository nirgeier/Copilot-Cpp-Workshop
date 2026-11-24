# Task - Hooks and Guardrails

!!! abstract "About this Task"
    - Add a repository hook that denies a dangerous tool call and logs tool use.
    - Keep it fast, local, and free of secrets.

## Task Definition

| Field | Details |
|-------|---------|
| Lab | [16. Hooks and Guardrails](../../01-Copilot-Foundations/16-Lab-Hooks-and-Guardrails.md) |
| Scope | `.github/hooks/` and one local script under `scripts/` if needed |
| Inputs | A CLI or cloud agent session, the hook reference, one allowed and one denied command |
| Constraints | Hooks run code. Validate input, escape shell arguments, no secrets in logs, no network calls without approval. |
| Deliverable | A reviewed hook file, a log sample, and a denial demonstration |
| Validation | `cmake --build --preset debug` and `ctest --preset debug --output-on-failure` |

## Lab Goals

- Choose a hook when a rule must be enforced rather than requested.
- Use `preToolUse` for allow and deny decisions and `postToolUse` for audit trails.
- Keep hooks below the timeout and quiet about sensitive data.

## The Task

- Create `.github/hooks/project-hooks.json` with a `preToolUse` guard and a `postToolUse` logger.
- Demonstrate one allowed command and one denied command.

## Task Steps

### Step 1 - Choose the events

Decide which events the task needs and name them.

**Expected evidence:** a short list with a reason per event.

<details class="note" markdown="1">
<summary>Suggested solution - Step 1</summary>

- `preToolUse` is required because it can approve or deny a tool execution.
- `postToolUse` records results for an audit trail.
- `sessionStart` and `sessionEnd` are optional for session logging.
- `errorOccurred` is useful for debugging hook failures.
- Cloud agent supports only a subset of CLI events, so check the hooks reference for the surface in use.

</details>

### Step 2 - Write the hook file

Create the JSON with `version: 1`, a `hooks` object, and command entries with a bash script path and timeout.

**Expected evidence:** valid JSON that parses.

<details class="note" markdown="1">
<summary>Suggested solution - Step 2</summary>

```json
{
  "version": 1,
  "hooks": {
    "preToolUse": [
      {
        "type": "command",
        "bash": "./scripts/guard.sh",
        "cwd": ".",
        "timeoutSec": 10
      }
    ],
    "postToolUse": [
      {
        "type": "command",
        "bash": "cat >> logs/tool-results.jsonl"
      }
    ]
  }
}
```

- Required fields are `version`, `hooks`, and `type: "command"`.
- `bash` gives the script path on Unix.
- `cwd`, `env`, and `timeoutSec` are optional; the default timeout is 30 seconds.
- Use the PowerShell key instead on Windows.

</details>

### Step 3 - Implement the guard

Write a small script that denies a destructive pattern and allows everything else.

**Expected evidence:** the script exists and is under five seconds.

<details class="note" markdown="1">
<summary>Suggested solution - Step 3</summary>

Create `scripts/guard.sh` with this complete content. It parses the native camelCase `preToolUse` payload and never evaluates tool input as shell code:

```bash
#!/usr/bin/env bash
# preToolUse receives one JSON object on stdin. Examples:
#   { "sessionId": "...", "toolName": "bash", "toolArgs": { "command": "..." } }
# Write a deny decision to stdout to block the call. Empty stdout means
# default permission behavior. Command hook errors are fail closed.
set -euo pipefail

python3 - <<'PY'
import json
import re
import sys

try:
    payload = json.load(sys.stdin)
except (ValueError, OSError):
    print(json.dumps({
        "permissionDecision": "deny",
        "permissionDecisionReason": "Hook received invalid JSON",
    }))
    sys.exit(0)

tool_name = str(payload.get("toolName", payload.get("tool_name", ""))).lower()
args = payload.get("toolArgs", payload.get("tool_input", {}))
if isinstance(args, dict):
    command = str(args.get("command", args.get("cmd", "")))
else:
    command = str(args)

blocked = [
    r"\brm\s+-rf\b",
    r"\bcurl\b[^\n|]*\|\s*(bash|sh)\b",
    r"\bgit\s+push\s+--force\b",
]

for pattern in blocked:
    if re.search(pattern, command, re.IGNORECASE):
        print(json.dumps({
            "permissionDecision": "deny",
            "permissionDecisionReason": "Blocked by project hook: " + pattern,
        }))
        sys.exit(0)

# No output: let the normal permission flow decide.
PY
```

The hook denies three patterns and emits no output otherwise. Command hooks are fail closed on errors, and timeouts fail open, so keep `timeoutSec` short and the script fast.

</details>

### Step 4 - Demonstrate allow and deny

- Run a CLI session with the hook enabled.
- Trigger one allowed command and one denied command.

**Expected evidence:** a log entry for each and the denial message.

<details class="note" markdown="1">
<summary>Suggested solution - Step 4</summary>

- Allowed: ask Copilot to read `CMakePresets.json`.
- The `postToolUse` hook appends a result line.

- Denied: ask Copilot to run the command your guard blocks.
- The agent should report that the hook denied the tool call.
- Show the log line and the agent message.
- If the agent ignored the hook, check the configuration location for your surface.

</details>

### Step 5 - Review the hook like code

Check that no secret is logged, no external service is called, and the hook is under the timeout.

**Expected evidence:** a short review note with file and line.

<details class="note" markdown="1">
<summary>Suggested solution - Step 5</summary>

- Review with `docs/review-checklist.md` as a model: input validation, escaping, permissions on scripts and logs, timeouts, and network behavior.
- A hook that runs synchronously and blocks the agent must stay under five seconds where possible.
- Record one improvement for the next iteration.

</details>

## Validation

```sh
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

- No C++ changes are expected.
- The seeded failures remain.

## Definition of Done

- [ ] A repository hook file exists with `version: 1` and valid command entries.
- [ ] One allow case and one deny case were demonstrated with evidence.
- [ ] Hook logs contain no secrets or sensitive source.
- [ ] The hook stays under its timeout and makes no unapproved network call.
- [ ] The hook diff was reviewed like code.

## Summary

&emsp;✅&emsp;Use hooks for enforced rules, not requested rules<br>
&emsp;✅&emsp;Deny dangerous tool calls in `preToolUse`<br>
&emsp;✅&emsp;Keep hooks fast, local, and reviewed
## Solution

<details class="note" markdown="1">
<summary>Reference solution</summary>

`.github/hooks/project-hooks.json`:

```json
{
  "version": 1,
  "hooks": {
    "preToolUse": [
      { "type": "command", "bash": "./scripts/guard.sh", "timeoutSec": 10 }
    ],
    "postToolUse": [
      { "type": "command", "bash": "cat >> logs/tool-results.jsonl" }
    ]
  }
}
```

`scripts/guard.sh`, keeping tool input as data rather than shell code:

```bash
#!/usr/bin/env bash
set -euo pipefail

python3 - <<'PY'
import json
import re
import sys

payload = json.load(sys.stdin)
args = payload.get("toolArgs", {})
command = str(args.get("command", "")) if isinstance(args, dict) else str(args)
blocked = [r"\brm\s+-rf\b", r"\bgit\s+push\s+--force\b"]
if any(re.search(pattern, command) for pattern in blocked):
    print(json.dumps({
        "permissionDecision": "deny",
        "permissionDecisionReason": "Destructive command blocked by project hook",
    }))
PY
```

- A repository hook file with `preToolUse` and `postToolUse` entries, each under five seconds, appending non-sensitive entries to a log.
- Demonstrate one allowed command producing a log line and one denied command stopping the agent.
- Review the hook like code, keep it offline, and confirm the seeded test state is unchanged.

</details>


**Back:** [Tasks (Overview)](../README.md) | **Next:** [Task - Spaces and Copilot Memory](14-Spaces-and-Memory.md)
