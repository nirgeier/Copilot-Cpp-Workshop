# Workshop image: C++17 toolchain, MkDocs site tooling, and GitHub Copilot CLI.
# The base image is pulled from the Google mirror to avoid Docker Hub auth issues.
FROM mirror.gcr.io/library/node:22-bookworm

LABEL org.opencontainers.image.title="Copilot-Cpp-Workshop"
LABEL org.opencontainers.image.description="Hands-on GitHub Copilot labs for a C++17 repository"
LABEL org.opencontainers.image.source="https://github.com/nirgeier/Copilot-Cpp-Workshop"

ARG DEBIAN_FRONTEND=noninteractive

# C++17 compiler, CMake >= 3.20, Boost.Test headers >= 1.70, and site tooling.
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      ninja-build \
      libboost-test-dev \
      python3 \
      python3-dev \
      python3-pip \
      python3-venv \
      git \
      ca-certificates \
      curl \
      jq \
      less \
      procps \
 && rm -rf /var/lib/apt/lists/*

# Pin the MkDocs plugins to the versions used by init_site.sh in this repository.
COPY mkdocs/requirements.txt /opt/requirements.txt
RUN python3 -m venv /opt/mkdocs-venv \
 && /opt/mkdocs-venv/bin/pip install --no-cache-dir --disable-pip-version-check -r /opt/requirements.txt \
 && ln -s /opt/mkdocs-venv/bin/mkdocs /usr/local/bin/mkdocs

# GitHub Copilot CLI. Node 22 is required by the official npm package.
RUN npm config set ignore-scripts false \
 && npm install -g @github/copilot \
 && npm cache clean --force

# A non-root participant with a writable working directory.
RUN useradd --create-home --shell /bin/bash --uid 1001 --user-group workshop \
 && mkdir -p /work \
 && chown workshop:workshop /work \
 && printf '[user]\n\tname = Workshop Participant\n\temail = workshop@example.invalid\n[safe]\n\tdirectory = /work\n' \
      > /home/workshop/.gitconfig \
 && chown workshop:workshop /home/workshop/.gitconfig

COPY docker/workshop-verify /usr/local/bin/workshop-verify
COPY docker/workshop-site /usr/local/bin/workshop-site
RUN chmod 0755 /usr/local/bin/workshop-verify /usr/local/bin/workshop-site

# Baked baseline copy. A host mount at /work overrides this with your checkout.
COPY --chown=workshop:workshop . /work

ENV PATH="/opt/mkdocs-venv/bin:${PATH}" \
    WORKSHOP_DIR=/work \
    PYTHONUNBUFFERED=1 \
    PIP_NO_CACHE_DIR=1

WORKDIR /work
USER workshop

CMD ["/bin/bash"]
