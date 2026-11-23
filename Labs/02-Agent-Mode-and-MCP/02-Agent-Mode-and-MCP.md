# 2. Agent Mode, Tools and MCP

!!! abstract "About this Guide"
    Agent mode plans, edits files, runs terminal commands, and corrects itself from errors. Your job is to define a definition of done that an agent can actually obey.

## 1. Plan First

- Use the Plan agent to agree on an approach before any code changes.
- The plan should name files, acceptance criteria, and validation gates.
- Reject assumptions that are not supported by the repository.

!!! tip "Executable definition of done"
    For this repository:
    ```sh
    cmake --build --preset debug
    ctest --preset debug --output-on-failure
    cmake --preset sanitizers && cmake --build --preset sanitizers
    ctest --preset sanitizers --output-on-failure
    ```

## 2. Tool Approval and Checkpoints

| Control | Why it matters |
|---------|----------------|
| Tool approval | Prevents unreviewed terminal commands or edits |
| Auto-approval rules | Reduce friction for known safe commands only |
| Request limits | Bound cost and run time |
| Todo lists | Make multi-step work visible |
| Keep or undo | Lets you reject an edit after inspection |

## 3. Feed Real Failures Back

- Paste the compiler diagnostic, not a paraphrase.
- Paste the Boost.Test failure, including file and line.
- Ask the agent to fix the failing check, not to silence it.

!!! warning "Never weaken a test"
    Changing `EXPECT`/`BOOST_CHECK` assertions or deleting a test to get a green run is a failed lab, not a passed one.

## 4. Model Context Protocol (MCP)

- MCP exposes tools, resources, and prompts to Copilot.
- Configure servers in VS Code, Copilot CLI, and the coding agent.
- The GitHub MCP server can read issues and pull requests as grounded context.

| MCP concern | Rule for the labs |
|-------------|-------------------|
| Registries | Use only approved servers |
| Allowlists | Follow the organization list |
| Credentials | Least privilege, never in prompts or files |
| Toolsets | Give each agent only what it needs |
| Outputs | Treat tool output as untrusted data |

## 5. C++ Specifics

- Agent edits in `CMakeLists.txt` must keep the project offline and C++17.
- Generated code must respect the header and implementation split.
- Watch for invented STL calls and non-standard extensions.
- Run sanitizers when the toolchain supports them.

## 6. Summary

&emsp;✅&emsp;Approve a plan before edits<br>
&emsp;✅&emsp;Use real build and test output as feedback<br>
&emsp;✅&emsp;Configure MCP under least privilege

---

**Next:** [3. Lab 2 - Plan, Build and Validate](03-Lab-2-Plan-Build-Validate.md)
