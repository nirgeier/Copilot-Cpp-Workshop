# Copilot-Cpp-Workshop

[![Deploy GitHub Pages](https://github.com/nirgeier/Copilot-Cpp-Workshop/actions/workflows/deploy-mkdocs.yml/badge.svg)](https://github.com/nirgeier/Copilot-Cpp-Workshop/actions/workflows/deploy-mkdocs.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub stars](https://img.shields.io/github/stars/nirgeier/Copilot-Cpp-Workshop?style=social)](https://github.com/nirgeier/Copilot-Cpp-Workshop/stargazers)

Hands-on labs for **AI-Assisted Development with GitHub Copilot**, taught against a small C++17 codebase. GitHub Copilot is the course subject; C++ is the working codebase.

📘 **[Read the labs on the documentation site](https://nirgeier.github.io/Copilot-Cpp-Workshop/)**

---

## 🚀 What This Repository Contains

| Path | Purpose |
|------|---------|
| `Labs/` | The MkDocs lab site: setup, foundations, agent mode, multi-agent delivery |
| `mkdocs/` | Modular MkDocs configuration fragments and shared theme overrides |
| `mkdocs.yml` | Generated site configuration (concatenation of `mkdocs/01-*.yml` to `06-*.yml`) |
| `include/edge_inference/`, `src/` | Small C++17 inference library with a deterministic reference backend |
| `cli/` | Command line tool that runs one input through the inference path |
| `benchmark/` | Latency benchmark with p50 and p95 reporting |
| `tests/` | Boost.Test suites with two seeded failures for Lab 2 and Lab 3 |
| `data/` | Valid, boundary, and invalid input samples |
| `models/` | Notes on the model artifact and the optional ONNX Runtime path |
| `.github/` | Copilot instructions, path rules, prompts, reviewer agent, and a skill |
| `docs/review-checklist.md` | C++ review checklist used by the reviewer agent |

## 📂 Lab Structure

```
Labs/
├── README.md                       Home
├── 00-Setup/                       Tools, Copilot configuration, baseline verification, container
├── 01-Copilot-Foundations/         Alignment, context, agents, Lab 1
├── 02-Agent-Mode-and-MCP/          Models, agent mode, MCP, Lab 2
└── 03-Multi-Agent-and-Review/      Orchestration, Lab 3, governance
```

## 🛠️ Quick Start (C++ Project)

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/edge_inference_cli data/valid.json
./build/debug/edge_benchmark data/valid.json 500
```

A clean checkout builds successfully, but `preprocessing_tests` and `postprocessing_tests` fail on purpose. They are the starting points for Lab 2 and Lab 3. `model_tests` passes from the start. See `Labs/00-Setup/03-Verify-Environment.md`.

## 🐳 Run in a Container

The Dockerfile packages the C++17 toolchain, Boost.Test headers, the pinned MkDocs environment, and GitHub Copilot CLI. No local tool installation is needed.

```bash
# Pull the published image, or build it locally with: docker build -t copilot-cpp-workshop -f Dockerfile .
docker pull ghcr.io/nirgeier/copilot-cpp-workshop:latest
docker run --rm -it -v "$PWD":/work -p 8000:8000 ghcr.io/nirgeier/copilot-cpp-workshop:latest
```

If the package is private, log in first with `echo "$(gh auth token)" | docker login ghcr.io -u nirgeier --password-stdin`.

Inside the container, run `workshop-verify` for the validation gates, `workshop-site build` or `workshop-site serve` for the docs, and `copilot` for the terminal labs. See `Labs/00-Setup/04-Container-Setup.md` for details and troubleshooting.

## 📖 Build the Lab Site

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r mkdocs/requirements.txt
cat mkdocs/01-*.yml mkdocs/02-*.yml mkdocs/03-*.yml mkdocs/04-*.yml mkdocs/05-*.yml mkdocs/06-*.yml > mkdocs.yml
mkdocs serve
```

Or run `./init_site.sh --no-serve` for the automated setup used by the other lab repositories.

## 🔧 Conventions

- Tests use Boost.Test in header-only mode. Boost headers 1.70 or newer are required.
- No model binary is committed. See `models/README.md`.
- No network downloads at CMake configure time.
- All prose uses ASCII hyphens, never em dashes.
- Copilot output is a proposal. A human reviewer approves every change.
