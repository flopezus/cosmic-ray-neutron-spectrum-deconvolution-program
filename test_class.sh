#!/usr/bin/env bash

set -euo pipefail

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${REPO_DIR}"

fail() {
    echo "[ERROR] $*" >&2
    exit 1
}

echo "[1/8] Docker y Docker Compose"
command -v docker >/dev/null 2>&1 || fail "Docker no está instalado."
docker --version
docker compose version

export LOCAL_UID
export LOCAL_GID
LOCAL_UID="$(id -u)"
LOCAL_GID="$(id -g)"

echo "[2/8] Sintaxis Bash"
bash -n \
    start_class.sh \
    stop_class.sh \
    test_class.sh \
    docker/entrypoint.sh \
    local_scripts/run_event_em_local.sh \
    local_scripts/run_event_em_mc_local.sh

echo "[3/8] Configuración de Compose"
docker compose config >/dev/null

echo "[4/8] Construcción de la imagen"
docker compose build jupyter

echo "[5/8] ROOT 6.32.06, PyROOT y bibliotecas Python"
docker compose run --rm --no-deps jupyter bash -lc '
    set -euo pipefail
    test "$(root-config --version)" = "6.32.06"
    python3 -c "
import ROOT
import awkward
import ipywidgets
import matplotlib
import numpy
import pandas
import uproot
assert ROOT.gROOT.GetVersion() == \"6.32.06\"
print(\"PyROOT:\", ROOT.gROOT.GetVersion())
"
    cd /workspace/classroom/notebooks
    python3 -c "
from classroom.python.unfolding_helpers import load_shell_config
config = load_shell_config(
    \"configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh\"
)
assert config[\"CAMPAIGN\"] == \"LCO\"
print(\"Import del helper desde notebooks/: OK\")
"
'

echo "[6/8] Macro, configuraciones e inputs"
docker compose run --rm --no-deps jupyter bash -lc '
    set -euo pipefail
    cd /workspace
    test -f macros/deconv_CRNS.C
    test -f configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh
    test -f data/external/CRNS_Data/LCO/LCO_data_60min_complete.root
    test -f data/external/EXPACS_Data/parma_cpp_flopez/LCO_parma_fluxes.root
    test -f data/external/EXPACS_Data/parma_cpp_flopez/ICRP116_binning_resume.csv
    response_count="$(find \
        data/external/Response_Functions_CEFNEN_Spectrometer/LIN_Spectrometer_2025_FTFP/ws_factor \
        -maxdepth 1 -type f -name "*.root" | wc -l)"
    test "${response_count}" -ge 17
    echo "Inputs LCO/FTFP_BERT/ws disponibles (${response_count} respuestas)."
'

echo "[7/8] Carga de deconv_CRNS.C desde local_scripts/"
docker compose run --rm --no-deps jupyter bash -lc '
    set -euo pipefail
    cd /workspace/local_scripts
    root -l -b <<ROOT_EOF
.L ../macros/deconv_CRNS.C
if (!gROOT->GetGlobalFunction("em_loop_steps_update")) {
    gSystem->Exit(2);
}
if (!gROOT->GetGlobalFunction("em_loop_MC_opt_new_update")) {
    gSystem->Exit(3);
}
.q
ROOT_EOF
'

echo "[8/8] Validación rápida de las interfaces (sin ejecutar unfolding)"
if bash local_scripts/run_event_em_local.sh \
    configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh 0 \
    >/dev/null 2>&1; then
    fail "el lanzador EM aceptó un EVENT_ID inválido."
fi

if bash local_scripts/run_event_em_mc_local.sh \
    configs/unfolding_configs/config_EM_MC_stop_LCO_60min_ISO.sh \
    1 100 200000 20 \
    >/dev/null 2>&1; then
    fail "el lanzador MC aceptó una interfaz incompleta."
fi

echo
echo "[OK] Entorno docente verificado. No se ejecutó un Monte Carlo completo."
