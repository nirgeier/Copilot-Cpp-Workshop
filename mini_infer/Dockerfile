# Self-contained image for the mini_infer capstone project.
# The base image comes from the Google mirror to avoid Docker Hub auth issues.
FROM mirror.gcr.io/library/node:22-bookworm

LABEL org.opencontainers.image.title="mini_infer"
LABEL org.opencontainers.image.description="Self-contained mini_infer C++17 demo, tests and download server"

ARG DEBIAN_FRONTEND=noninteractive

# C++17 toolchain, CMake >= 3.20, Boost.Test headers >= 1.70, zip tooling.
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      libboost-test-dev \
      ca-certificates \
      zip \
      unzip \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/mini_infer
COPY . /opt/mini_infer
RUN chmod +x demo.sh scripts/package-solution.sh docker/entrypoint.sh

# Bake the downloadable archive into the image.
RUN ./scripts/package-solution.sh

ENV MINI_INFER_DIR=/opt/mini_infer \
    PORT=8000

EXPOSE 8000

ENTRYPOINT ["/opt/mini_infer/docker/entrypoint.sh"]
CMD ["demo"]
