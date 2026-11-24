# Project notes for mini_infer

These notes record the accepted plan, the decisions rejected as ungrounded, and the
validation evidence for this repository. Every generated change is a proposal and a human
reviewer approves it.

## 1. Scope

A small offline C++17 project that normalizes a list of numbers into `[0, 1]` and finds the
index of the largest value. Deliverables: library, CLI, Boost.Test suites, scripted demo,
solution zip, download page with a button and a router, and a Docker image.

## 2. Accepted plan

Files: `include/mini_infer/normalize.hpp`, `include/mini_infer/argmax.hpp`,
`src/normalize.cpp`, `src/argmax.cpp`, `cli/main.cpp`, `tests/main.cpp`,
`tests/test_normalize.cpp`, `tests/test_argmax.cpp`, `CMakeLists.txt`, `CMakePresets.json`,
`data/sample.txt`, `demo.sh`, `scripts/package-solution.sh`, `web/server.js`,
`web/index.html`, `Dockerfile`, `docker/entrypoint.sh`.

Commands named as checks: `cmake --preset debug`, `cmake --build --preset debug`,
`ctest --preset debug --output-on-failure`, and the same three for `sanitizers`.

Behavior: `normalize` returns false and leaves data unchanged for empty or constant input.
`argmax` returns zero for empty input and uses a strict `<` comparison so the first
maximum wins. Both use `std::size_t` for indexes.

## 3. Rejected suggestions

- Adding FetchContent, vcpkg or any CMake download step. The project is offline.
- Adding a JSON parser dependency. The CLI reads whitespace separated doubles with
  `std::ifstream` and `operator>>`.
- Adding a model binary or any generated build artifact to the archive.
- Weakening any assertion to make a test pass. All assertions use exact values or a
  `1e-12` tolerance.

## 4. Evidence: debug validation

Command:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
./build/debug/mini_infer_cli data/sample.txt
```

Observed result: configure and build completed with no errors. CTest reported
`100% tests passed out of 2` with `normalize_tests` and `argmax_tests` both Passing.
The CLI printed:

```text
count: 5
normalized: 0 0.333333 0.666667 0.333333 1
argmax index: 4
normalize ok: true
```

CMake emits a CMP0167 policy warning from the installed Boost CMake package. It is a
developer warning only and does not affect the build.

## 5. Evidence: sanitizers

Commands attempted:

```sh
cmake --preset sanitizers
cmake --build --preset sanitizers
ctest --preset sanitizers --output-on-failure
```

Configure and build succeeded. The test step did not finish: `normalize_tests` started and
the test binary kept running with no output. A direct run of the sanitizer test binary also
produced no output after 15 seconds. A minimal probe compiled with the same flags also
hung:

```sh
printf 'int main(){return 0;}\n' > /tmp/asan_probe.cpp
c++ -fsanitize=address,undefined -fno-omit-frame-pointer /tmp/asan_probe.cpp -o /tmp/asan_probe
```

The probe did not exit within 10 seconds. Conclusion: the sanitizer runtime is unavailable
on this macOS host. This is an environment limitation, not a failure in the project code.
The debug results in section 4 are kept as the local validation record. Sanitizers do run
in the Linux container, as recorded in section 7.

## 6. Evidence: archive and download router

```sh
./scripts/package-solution.sh
# Created .../mini_infer/solution.zip
# 31 files, all entries under mini_infer/
```

The router was started with `PORT=8123 node web/server.js` and checked with curl:

| Request | Status |
|---------|--------|
| `GET /` | 200, text/html |
| `GET /health` | 200, application/json |
| `GET /api/downloads` | 200, application/json |
| `GET /download/solution.zip` | 200, application/zip |
| `GET /nope` | 404 |

The zip response carried
`Content-Disposition: attachment; filename="mini-infer-solution.zip"` and the downloaded
archive listed the same 31 files.

## 7. Evidence: Docker

Image build from the `mini_infer` directory:

```sh
docker build -t mini-infer .
```

The build used `mirror.gcr.io/library/node:22-bookworm`, CMake 3.25 and Boost 1.74, and
generated `solution.zip` inside the image.

Container subcommands:

```sh
docker run --rm mini-infer          # default: demo
docker run --rm mini-infer test
docker run --rm mini-infer cli
```

All three configured, built and ran the tests. CTest reported `100% tests passed, 0 tests
failed out of 2` in the debug preset. The CLI printed the same five normalized values and
argmax index 4 as the local run.

Download server:

```sh
docker run --rm -p 8000:8000 mini-infer serve
```

Checked with curl: `/` returned 200 text/html, `/health` and `/api/downloads` returned 200
application/json, `/nope` returned 404, and `/download/solution.zip` returned 200 with
`Content-Disposition: attachment; filename="mini-infer-solution.zip"` and a 32 file archive.

Sanitizers in the Linux container:

```sh
docker run --rm --entrypoint bash -e MINI_INFER_SANITIZERS=1 mini-infer \
  -c 'timeout 150s ./demo.sh'
```

The sanitizer preset configured, built and ran both suites with `100% tests passed, 0 tests
failed out of 2`. This confirms the local sanitizer hang is a host limitation.

## 8. Summary

The repository builds and tests clean in the debug preset locally and in the container.
Sanitizers pass in the container and are recorded as unavailable on the macOS host. The demo
prints normalized values and the argmax index. The solution archive is regenerable and
downloadable from a button on the served page.
