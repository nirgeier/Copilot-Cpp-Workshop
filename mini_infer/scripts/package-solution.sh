#!/usr/bin/env bash
# Build solution.zip, a single archive with the complete mini_infer solution.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/solution.zip"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

STAGE="$TMP/mini_infer"
mkdir -p "$STAGE"

FILES=(
  CMakeLists.txt
  CMakePresets.json
  AGENTS.md
  README.md
  PROJECT_NOTES.md
  demo.sh
  Dockerfile
  .gitignore
  .dockerignore
)
for file in "${FILES[@]}"; do
  if [[ -f "$ROOT/$file" ]]; then
    cp "$ROOT/$file" "$STAGE/"
  fi
done

for dir in data include src cli tests web docker scripts; do
  if [[ -d "$ROOT/$dir" ]]; then
    cp -R "$ROOT/$dir" "$STAGE/"
  fi
done

rm -f "$OUT"
(cd "$TMP" && zip -q -r "$OUT" mini_infer)

echo "Created $OUT"
unzip -l "$OUT" | tail -n 2
