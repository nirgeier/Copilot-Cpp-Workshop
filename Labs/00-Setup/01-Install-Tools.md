# 1. Installing Tools

!!! abstract "About this Guide"
    - Install the local toolchain used by every lab.
    - Nothing is downloaded by the CMake configuration: the C++ project uses Boost.Test in header-only mode and needs no model binary or network package at build time.

## 1. Install Git and GitHub CLI

- Git is required for branches, issues, and pull requests.
- GitHub CLI (`gh`) is optional but useful for reading issues as agent context.

!!! tip "Installing Git and gh"

    === ":fontawesome-brands-apple: macOS"
        ```sh
        brew install git gh
        ```

    === ":fontawesome-brands-windows: Windows"
        Install [Git for Windows](https://git-scm.com/download/win) and [GitHub CLI](https://cli.github.com/).

    === ":simple-linux: Linux"
        ```sh
        sudo apt install git gh
        ```

## 2. Install a C++17 Compiler and CMake

- You need a C++17 compiler, CMake 3.20 or newer, and CTest.
- The labs assume Windows 11 with MSVC in the classroom, but the repository builds on macOS and Linux too.

!!! tip "Toolchain by platform"

    === ":fontawesome-brands-apple: macOS"
        ```sh
        xcode-select --install
        brew install cmake boost
        ```

    === ":fontawesome-brands-windows: Windows"
        - Install Visual Studio 2022 with the **Desktop development with C++** workload and CMake.
        - Install Boost headers from an approved internal package or vcpkg mirror.

    === ":simple-linux: Linux"
        ```sh
        sudo apt install build-essential cmake libboost-dev
        ```

## 3. Install Boost.Test Headers

- Tests use `boost/test/unit_test.hpp` and `boost/test/included/unit_test.hpp`.
- Boost 1.70 or newer is required. Headers alone are enough; no library link step is needed.

```bash
# Verify Boost is discoverable
cmake --preset debug
```

If Boost lives in a non-standard location, configure with `-DBOOST_ROOT=/path/to/boost`.

## 4. Install VS Code Extensions

| Extension | Purpose |
|-----------|---------|
| GitHub Copilot | Completions and chat in the editor |
| GitHub Copilot Chat | Chat view, agents, and prompt files |
| C/C++ | IntelliSense, navigation, and debugging |
| CMake Tools | Configure, build, and run CTest from the editor |

!!! warning "Organization policy"
    - Install only extensions and features approved for your environment.
    - Copilot must be enabled by your organization before the workshop.

## Reference

### Toolchain reference

The toolchain has four parts. The versions below are minimums used by the labs.

| Component | Minimum | Verify with | Note |
|-----------|---------|-------------|------|
| Git | Current release | `git --version` | Branch and issue workflow |
| GitHub CLI | Current release | `gh --version` | Optional issue context for agents |
| C++ compiler | C++17 | `cmake --preset debug` | MSVC, GCC, or Clang |
| CMake and CTest | 3.20 | `cmake --version` | Presets drive every gate |
| Boost.Test headers | 1.70 | Configure step | Header only, no link step |
| VS Code extensions | Listed above | Extensions view | Policy approval required |

- Configure with `cmake --preset debug -DBOOST_ROOT=/path/to/boost` when Boost is outside the default search path.
- CMake configuration downloads nothing. Do not add `FetchContent`, vcpkg, or Conan dependencies without an approved offline mirror.
- Boost.Test runs in header-only mode, so no compiled Boost library is needed.

!!! note "Platform differences"
    - Windows uses the Visual Studio 2022 C++ workload and an approved Boost package or vcpkg mirror.
    - macOS and Linux install Boost headers through the system package manager.
    - Never install an extension or preview feature that policy has not approved.

---

## 5. Tools Used

- **Terminal**: all configure, build, and test commands
- **VS Code**: editing and Copilot interaction
- **Git and GitHub CLI**: repository and issue workflow

## Example

```text
$ cmake --version
cmake version 3.25.1

$ g++ --version | head -1
g++ (Debian 12.2.0-14+deb12u1) 12.2.0

$ echo '#include <boost/test/unit_test.hpp>' | g++ -x c++ -std=c++17 -fsyntax-only -
(no output means Boost headers are discoverable)

$ cmake --preset debug
-- Configuring done
-- Generating done
```

---

**Next:** [2. Configure GitHub Copilot](02-Configure-Copilot.md)
