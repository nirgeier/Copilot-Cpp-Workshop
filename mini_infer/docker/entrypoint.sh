#!/usr/bin/env bash
# Container entrypoint with explicit subcommands.
set -euo pipefail

cd "${MINI_INFER_DIR:-/opt/mini_infer}"

case "${1:-demo}" in
  demo)
    exec ./demo.sh
    ;;
  test)
    echo "==> configure and build (debug)"
    cmake --preset debug
    cmake --build --preset debug
    echo "==> test (debug)"
    ctest --preset debug --output-on-failure
    ;;
  cli)
    if [[ $# -gt 1 ]]; then
      args=("${@:2}")
    else
      args=(data/sample.txt)
    fi
    if [[ ! -x ./build/debug/mini_infer_cli ]]; then
      cmake --preset debug
      cmake --build --preset debug
    fi
    exec ./build/debug/mini_infer_cli "${args[@]}"
    ;;
  serve)
    exec node web/server.js
    ;;
  package)
    exec ./scripts/package-solution.sh
    ;;
  shell)
    exec /bin/bash
    ;;
  *)
    echo "usage: entrypoint.sh [demo|test|cli|serve|package|shell]" >&2
    exit 2
    ;;
esac
