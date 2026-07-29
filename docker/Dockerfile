FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG ROOT_VERSION=6.32.06
ARG ROOT_ARCHIVE=root_v6.32.06.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz
ARG ROOT_URL=https://root.cern/download/${ROOT_ARCHIVE}

# Bibliotecas de ejecución de la distribución binaria de ROOT y herramientas
# necesarias para cargar o compilar macros C++ dentro del contenedor.
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        bash \
        binutils \
        build-essential \
        ca-certificates \
        cmake \
        curl \
        dpkg-dev \
        g++ \
        gcc \
        git \
        libcfitsio-dev \
        libfftw3-dev \
        libgif-dev \
        libglew-dev \
        libglu1-mesa-dev \
        libgraphviz-dev \
        libgsl-dev \
        libkrb5-dev \
        libldap2-dev \
        libpcre3-dev \
        libssl-dev \
        libtbb-dev \
        libx11-dev \
        libxext-dev \
        libxft-dev \
        libxml2-dev \
        libxpm-dev \
        python3 \
        python3-dev \
        python3-pip \
        tini \
    && rm -rf /var/lib/apt/lists/*

# ROOT 6.32.06 para Ubuntu 22.04/x86_64, publicado por el proyecto ROOT.
RUN mkdir -p /opt/root \
    && curl --fail --location --retry 4 --retry-delay 2 \
        "${ROOT_URL}" -o /tmp/root.tar.gz \
    && tar -xzf /tmp/root.tar.gz --strip-components=1 -C /opt/root \
    && rm /tmp/root.tar.gz

ENV ROOTSYS=/opt/root
ENV PATH=/opt/root/bin:${PATH}
ENV LD_LIBRARY_PATH=/opt/root/lib
ENV PYTHONPATH=/workspace:/opt/root/lib
ENV CPLUS_INCLUDE_PATH=/opt/root/include
ENV LIBRARY_PATH=/opt/root/lib

COPY docker/requirements.txt /tmp/requirements.txt
RUN python3 -m pip install --no-cache-dir pip==24.2 \
    && python3 -m pip install --no-cache-dir -r /tmp/requirements.txt \
    && rm /tmp/requirements.txt

COPY docker/entrypoint.sh /opt/classroom/entrypoint.sh
RUN chmod 0755 /opt/classroom/entrypoint.sh \
    && test "$(root-config --version)" = "${ROOT_VERSION}" \
    && python3 -c "import ROOT; assert ROOT.gROOT.GetVersion() == '${ROOT_VERSION}'"

ARG CLASSROOM_USER=classroom
ARG CLASSROOM_UID=1000
ARG CLASSROOM_GID=1000
RUN groupadd --gid "${CLASSROOM_GID}" "${CLASSROOM_USER}" \
    && useradd \
        --uid "${CLASSROOM_UID}" \
        --gid "${CLASSROOM_GID}" \
        --create-home \
        --shell /bin/bash \
        "${CLASSROOM_USER}"

ENV HOME=/home/${CLASSROOM_USER}

WORKDIR /workspace
EXPOSE 8888

USER ${CLASSROOM_USER}

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/opt/classroom/entrypoint.sh"]
