#!/usr/bin/env bash

set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${REPO_DIR}"

export LOCAL_UID
export LOCAL_GID
export JUPYTER_PORT="${JUPYTER_PORT:-8888}"
export JUPYTER_TOKEN="${JUPYTER_TOKEN:-neutrons}"
LOCAL_UID="$(id -u)"
LOCAL_GID="$(id -g)"

mkdir -p \
    outputs/root/deconv_data_rootfile \
    outputs/pdf \
    outputs/log

docker compose up -d --build

echo
echo "JupyterLab está iniciado."
echo "URL: http://localhost:${JUPYTER_PORT}/lab?token=${JUPYTER_TOKEN}"
echo
echo "Ver logs:"
echo "  docker compose logs -f jupyter"
echo
echo "Detener el entorno:"
echo "  ./stop_class.sh"
