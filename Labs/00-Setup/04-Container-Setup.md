# 4. Using the Workshop Container

!!! abstract "About this Guide"
    The container image packages the C++ toolchain, Boost.Test headers, the pinned MkDocs environment, and GitHub Copilot CLI. Participants do not need to install them locally.

## 1. What Is in the Image

| Component | Version or source | Used for |
|-----------|-------------------|----------|
| Base image | `mirror.gcr.io/library/node:22-bookworm` | Node 22 for Copilot CLI |
| Compiler | GNU C++ from `build-essential` | C++17 build |
| CMake and CTest | Debian bookworm package, 3.25 or newer | Presets and tests |
| Boost headers | `libboost-test-dev`, 1.74 or newer | Header-only Boost.Test |
| Python and MkDocs | Python 3 venv with `mkdocs/requirements.txt` | Site build and serve |
| GitHub Copilot CLI | `@github/copilot` from npm | Terminal labs |
| Git and GitHub tooling | `git`, `jq`, `curl` | Repository and API tasks |
| Helper commands | `workshop-verify`, `workshop-site` | Repeatable validation |

!!! note "Nothing secret is baked in"
    The image contains no Copilot token, no credentials, and no model binary. Each participant signs in to Copilot CLI at runtime.

## 2. Get the Image

The published image lives in the GitHub Container Registry under this repository:

```sh
docker pull ghcr.io/nirgeier/copilot-cpp-workshop:latest
```

If the package is private in your environment, authenticate first with a token that has `read:packages`:

```sh
echo "$(gh auth token)" | docker login ghcr.io -u nirgeier --password-stdin
```

An administrator can change package visibility and repository access in the package settings at `https://github.com/nirgeier?tab=packages`. There is no working REST endpoint for user package visibility, so this step is done in the web UI.

To build the image locally instead, from the repository root:

```sh
docker build -t copilot-cpp-workshop -f Dockerfile .
```

The base image comes from a registry mirror. If your environment has direct Docker Hub access, you may change the `FROM` line to the official `node:22-bookworm` image.

Build time depends on your network and machine. The image downloads apt packages, pinned Python wheels, and the Copilot CLI npm package once, then everything runs offline.

## 3. Run With Your Own Checkout

Mount your repository at `/work`. Changes you make inside the container are written to your host checkout.

```sh
docker run --rm -it \
  -v "$PWD":/work \
  -p 8000:8000 \
  copilot-cpp-workshop
```

!!! warning "Work on a branch"
    Create a lab branch before starting, for example `git switch -c labs/your-name`. Copilot may edit files in the mounted directory.

## 4. Run With the Baked Baseline

If you do not mount a checkout, the image starts with a baseline copy of the repository at `/work`:

```sh
docker run --rm -it -p 8000:8000 copilot-cpp-workshop
```

Any changes in this mode are discarded when the container exits unless you commit them to a volume. Use the mount form for real lab work.

## 5. Run the Validation Gates

Inside the container:

```sh
workshop-verify
```

This configures `debug`, builds, and runs CTest. It prints the expected baseline at the end. To add the sanitizer preset with a time cap:

```sh
WORKSHOP_SANITIZERS=1 workshop-verify
```

You can also run the commands directly:

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug --output-on-failure
```

!!! warning "Two failures are expected"
    `preprocessing_tests` and `postprocessing_tests` fail on a clean checkout. `model_tests` passes. Tasks assign those defects specifically; do not fix them in unrelated tasks.

## 6. Sign In to Copilot CLI

```sh
copilot
```

- Confirm that you trust `/work` for this session only.
- If prompted, run `/login` and follow the device code flow.
- Use `@CMakePresets.json` to attach a file, plan mode for a plan, and `/review` for a diff review.

!!! warning "Protect your credentials"
    Never copy a token into a lab file, a prompt, or a committed diff. Do not bake a personal token into the image.

## 7. Build or Serve the Site

```sh
workshop-site build
workshop-site serve
```

The serve command binds to `0.0.0.0:8000` inside the container. With `-p 8000:8000`, open `http://localhost:8000/Copilot-Cpp-Workshop/` in your browser. The path suffix comes from the site URL configured in this repository.

To rebuild the generated `mkdocs.yml` from its fragments, run `./init_site.sh --no-serve` on a host checkout, then rebuild the image. The container uses the configuration present in the repository.

## Reference

### Container invocation reference

| Option | Required | Effect |
|--------|----------|--------|
| `--rm` | Recommended | Remove the container when it exits |
| `-it` | Interactive | Keep a terminal session open |
| `-v "$PWD":/work` | For lab work | Mount the host checkout for persistent edits |
| `-p 8000:8000` | Site use | Map the MkDocs server port |
| `--user "$(id -u):$(id -g)"` | UID mismatch only | Avoid permission errors on mounted files |

| Command or variable | Purpose |
|---------------------|---------|
| `workshop-verify` | Configure, build, and run CTest |
| `WORKSHOP_SANITIZERS=1` | Add a time capped sanitizer run |
| `workshop-site build` | Build the MkDocs site |
| `workshop-site serve` | Serve on `0.0.0.0:8000` |
| `copilot` | Start Copilot CLI and sign in |

- Without a mount, the image starts from a baked baseline and the changes are lost on exit.
- The image contains no token, credential, or model binary. Sign in at runtime.

!!! note "Registry and policy"
    - The image uses a registry mirror in `FROM`. Replace it only if your environment allows direct Docker Hub access.
    - Package visibility is controlled in the GitHub container package settings, not by a REST endpoint.

---

## 8. Troubleshooting

| Symptom | Cause | Fix |
|---------|-------|-----|
| Permission denied on mounted files | Host UID differs from container UID 1001 | Add `--user "$(id -u):$(id -g)"` to `docker run` |
| `detected dubious ownership` from git | Mounted repo owner differs | The image trusts `/work`; other paths need `git config --global --add safe.directory <path>` |
| Port 8000 already in use | Another server is running | Map a different port, for example `-p 8010:8000` |
| Image pull fails with Docker Hub auth error | Registry authentication issue | Use the mirror in the `FROM` line, as the Dockerfile does |
| Sanitizer test run appears to hang | Slow or unsupported sanitizer runtime | Use `WORKSHOP_SANITIZERS=1`, which caps the run at 120 seconds |
| Copilot CLI says Node is too old | System Node below 22 | Use this image; it is based on Node 22 |

## Example

```text
$ docker run --rm ghcr.io/nirgeier/copilot-cpp-workshop:latest workshop-verify
==> configure (debug)
==> build (debug)
[100%] Built target edge_unit_tests
==> test (debug) - two seeded failures are expected
1/3 Test #1: preprocessing_tests ..........***Failed
2/3 Test #2: postprocessing_tests .........***Failed
3/3 Test #3: model_tests ...................   Passed
33% tests passed, 2 tests failed out of 3

Expected baseline: model_tests passes; preprocessing_tests and
postprocessing_tests fail. Those two failures are workshop starting points.
```

## 9. Definition of Done

- [ ] The image builds from the repository root.
- [ ] `workshop-verify` shows one passing and two seeded failing test entries.
- [ ] `workshop-site build` completes with exit code 0.
- [ ] Copilot CLI starts and you can sign in with your own account.
- [ ] No token, credential, or personal path is present in a committed file.

## 10. Summary

&emsp;✅&emsp;Build and run a reproducible workshop container<br>
&emsp;✅&emsp;Use a mounted checkout for persistent lab work<br>
&emsp;✅&emsp;Run C++ gates, site tooling, and Copilot CLI without local installs

**Back:** [Lab 00 overview](README.md)
