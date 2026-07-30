#!/usr/bin/env bash

set -euo pipefail

umask 0022

export HOME="${HOME:-/tmp/jupyter-home}"
export JUPYTER_CONFIG_DIR="${JUPYTER_CONFIG_DIR:-${HOME}/.jupyter}"
export JUPYTER_DATA_DIR="${JUPYTER_DATA_DIR:-${HOME}/.local/share/jupyter}"
export JUPYTER_RUNTIME_DIR="${JUPYTER_RUNTIME_DIR:-${HOME}/.local/share/jupyter/runtime}"
export MPLCONFIGDIR="${MPLCONFIGDIR:-${HOME}/.config/matplotlib}"
OUTPUTS_DIR="/workspace/outputs"

mkdir -p \
    "${HOME}" \
    "${JUPYTER_CONFIG_DIR}" \
    "${JUPYTER_DATA_DIR}" \
    "${JUPYTER_RUNTIME_DIR}" \
    "${MPLCONFIGDIR}" \
    "${OUTPUTS_DIR}/root/deconv_data_rootfile" \
    "${OUTPUTS_DIR}/pdf" \
    "${OUTPUTS_DIR}/log"

if [ ! -w "${OUTPUTS_DIR}/root/deconv_data_rootfile" ]; then
    echo "Error: ${OUTPUTS_DIR}/root/deconv_data_rootfile no permite escritura." >&2
    exit 1
fi

cd /workspace

exec jupyter lab \
    --ip=0.0.0.0 \
    --port=8888 \
    --no-browser \
    --ServerApp.root_dir=/workspace \
    --IdentityProvider.token="${JUPYTER_TOKEN:-neutrons}" \
    --ServerApp.allow_remote_access=True
