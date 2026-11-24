#!/usr/bin/env bash
# Full demo for mini_infer: configure, build, test, then run the CLI.
set -euo pipefail

cd "$(dirname "$0")"

echo "==> configure (debug)"
cmake --preset debug

echo "==> build (debug)"
cmake --build --preset debug

echo "==> test (debug)"
ctest --preset debug --output-on-failure

echo "==> CLI demo on data/sample.txt"
./build/debug/mini_infer_cli data/sample.txt

if [[ "${MINI_INFER_SANITIZERS:-0}" == "1" ]]; then
  echo "==> configure, build and test (sanitizers)"
  cmake --preset sanitizers
  cmake --build --preset sanitizers
  ctest --preset sanitizers --output-on-failure
fi
