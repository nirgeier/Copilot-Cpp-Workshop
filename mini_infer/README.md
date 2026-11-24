# mini_infer

A small, self-contained C++17 capstone project. It normalizes a list of numbers into
`[0, 1]` and finds the index of the largest value. The algorithm is intentionally tiny so
the build, tests, demo, container and download flow are the point.

## Contents

| Path | Purpose |
|------|---------|
| `include/mini_infer/` | Public headers for `normalize` and `argmax` |
| `src/` | Library implementations |
| `cli/main.cpp` | CLI that reads a whitespace separated number file |
| `tests/` | Boost.Test suites with all tests passing |
| `data/sample.txt` | Sample input |
| `demo.sh` | Configure, build, test and run the CLI |
| `scripts/package-solution.sh` | Build `solution.zip` |
| `web/server.js` | Zero-dependency HTTP router for the download endpoint |
| `web/index.html` | Download page with a button |
| `Dockerfile` | Self-contained image for build, tests, demo and download server |

## API

```cpp
namespace mini_infer {
bool normalize(std::vector<double>& values);          // false for empty or constant input
std::size_t argmax(const std::vector<double>& values); // 0 for empty, first max wins on ties
}
```

## Run locally

Requirements: CMake 3.20 or newer, a C++17 compiler, Boost.Test headers 1.70 or newer.

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/mini_infer_cli data/sample.txt
```

Run everything in one step:

```bash
./demo.sh
```

Run with sanitizers as well:

```bash
MINI_INFER_SANITIZERS=1 ./demo.sh
# or manually:
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

Expected CLI output for `data/sample.txt` (min 2, max 8, span 6):

```text
count: 5
normalized: 0 0.333333 0.666667 0.333333 1
argmax index: 4
normalize ok: true
```

## Download the solution zip

The complete project is packed into a single archive, `solution.zip`, with all entries
under `mini_infer/`. Regenerate it at any time:

```bash
./scripts/package-solution.sh
unzip -l solution.zip | head
```

A web page exposes a download button and a router endpoint:

```bash
PORT=8000 node web/server.js
```

Then open <http://localhost:8000/> and click **Download solution.zip**, or call the
endpoint directly:

```bash
curl -OJ http://localhost:8000/download/solution.zip
```

Routes:

| Method and path | Purpose |
|-----------------|---------|
| `GET /` | Download page with button |
| `GET /download/solution.zip` | Zip archive as an attachment |
| `GET /api/downloads` | JSON manifest of available downloads |
| `GET /health` | Health check |

## Run with Docker

Build the image from the `mini_infer` directory (the build context is this folder):

```bash
cd mini_infer
docker build -t mini-infer .
```

The base image is pulled from `mirror.gcr.io` to avoid Docker Hub authentication issues
on machines with a broken keychain.

Run the full demo:

```bash
docker run --rm mini-infer
# equivalent to: docker run --rm mini-infer demo
```

Other subcommands:

```bash
docker run --rm mini-infer test              # configure, build and run all tests
docker run --rm mini-infer cli               # run the CLI on data/sample.txt
docker run --rm mini-infer cli data/sample.txt
docker run --rm mini-infer package           # regenerate solution.zip in the container
docker run --rm -it mini-infer shell         # interactive shell
```

Serve the download page on port 8000:

```bash
docker run --rm -p 8000:8000 mini-infer serve
```

Then open <http://localhost:8000/> and click the download button, or verify with:

```bash
curl -I http://localhost:8000/download/solution.zip
curl -OJ http://localhost:8000/download/solution.zip
```

## Validation gates

A change is not done until build, tests and, where available, sanitizers have been run.
See `AGENTS.md` and `PROJECT_NOTES.md` for the recorded evidence.

Every generated change is a proposal. A human approves it.
