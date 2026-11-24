#!/usr/bin/env bash
# Build the MkDocs site in a clean checkout (GitHub clone or Vercel).
# The generated mkdocs.yml points at .mkdocs-build/overrides, which is
# gitignored, so recreate it from the tracked mkdocs/overrides first.
set -euo pipefail

rm -rf .mkdocs-build/overrides
mkdir -p .mkdocs-build
cp -R mkdocs/overrides .mkdocs-build/overrides

usage=.mkdocs-build/overrides/partials/usage.md
sed -i.bak \
  -e 's|__KILLERCODA_URL__|https://killercoda.com/codewizard/scenario/CopilotCppWorkshop|g' \
  -e 's|__GHCR_IMAGE__|ghcr.io/nirgeier/copilot-cpp-workshop|g' \
  -e 's|__REPO_URL__|https://github.com/nirgeier/Copilot-Cpp-Workshop|g' \
  -e 's|__REPO_OWNER__|nirgeier|g' \
  -e 's|__REPO_NAME__|Copilot-Cpp-Workshop|g' \
  -e 's|__SITE_URL__|https://nirgeier.github.io/Copilot-Cpp-Workshop/|g' \
  -e 's|__SETUP_LAB_DIR__|00-Setup|g' \
  "$usage"
rm -f "$usage.bak"

python3 -m venv .venv
.venv/bin/pip install --disable-pip-version-check --no-cache-dir -r mkdocs/requirements.txt
.venv/bin/mkdocs build --config-file mkdocs.yml --site-dir mkdocs-site
