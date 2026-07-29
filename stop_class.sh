#!/usr/bin/env bash

set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${REPO_DIR}"

export LOCAL_UID
export LOCAL_GID
LOCAL_UID="$(id -u)"
LOCAL_GID="$(id -g)"

docker compose down
