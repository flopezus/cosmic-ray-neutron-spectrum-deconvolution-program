#!/usr/bin/env bash

set -euo pipefail

export HOME="${HOME:-/tmp/jupyter-home}"
export JUPYTER_CONFIG_DIR="${JUPYTER_CONFIG_DIR:-${HOME}/.jupyter}"
export JUPYTER_DATA_DIR="${JUPYTER_DATA_DIR:-${HOME}/.local/share/jupyter}"
export JUPYTER_RUNTIME_DIR="${JUPYTER_RUNTIME_DIR:-${HOME}/.local/share/jupyter/runtime}"
export MPLCONFIGDIR="${MPLCONFIGDIR:-${HOME}/.config/matplotlib}"

mkdir -p \
    "${HOME}" \
    "${JUPYTER_CONFIG_DIR}" \
    "${JUPYTER_DATA_DIR}" \
    "${JUPYTER_RUNTIME_DIR}" \
    "${MPLCONFIGDIR}"

cd /workspace

exec jupyter lab \
    --ip=0.0.0.0 \
    --port=8888 \
    --no-browser \
    --ServerApp.root_dir=/workspace \
    --IdentityProvider.token="${JUPYTER_TOKEN:-neutrons}" \
    --ServerApp.allow_remote_access=True
