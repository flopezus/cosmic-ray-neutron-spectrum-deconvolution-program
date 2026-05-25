#!/bin/bash

set -euo pipefail

#------------------------------------------------------
# Uso:
#   bash scripts/run_plot_events_em_mc_stop.slurm configs/unfolding_configs/config_EM_MC_stop_SanPedrodeAtacama_15min_MIX.sh
#
# Lanza un Slurm array para generar, por evento, los PDFs/SVGs de:
#   MakeHistograms_loop_bin_energy_single_pass_new()
# en macros/deconv_EM_MC.C
#------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
JOB_SCRIPT="${SCRIPT_DIR}/run_plot_events_em_mc_stop_jobs.sh"

if [ $# -lt 1 ]; then
    echo "Uso: $0 archivo_config.sh"
    echo "Ejemplo:"
    echo "  $0 ${REPO_DIR}/configs/unfolding_configs/config_EM_MC_stop_SanPedrodeAtacama_15min_MIX.sh"
    exit 1
fi

CONFIG_FILE="$(readlink -f "$1")"

if [ ! -f "$CONFIG_FILE" ]; then
    echo "Error: no existe el archivo de configuración: $CONFIG_FILE"
    exit 1
fi

if [ ! -f "$JOB_SCRIPT" ]; then
    echo "Error: no existe el worker: $JOB_SCRIPT"
    exit 1
fi

source "$CONFIG_FILE"

required_vars=(
    CAMPAIGN
    TIME_GRID
    NDET
    PHYLST
    NEUFTY
    TOTAL_EVENTS
    MAX_PARALLEL
)

for var in "${required_vars[@]}"; do
    if [ -z "${!var+x}" ] || [ -z "${!var}" ]; then
        echo "Error: la variable '$var' no está definida o está vacía en $CONFIG_FILE"
        exit 1
    fi
done

EXCLUDED_EVENTS="${EXCLUDED_EVENTS:-}"
SELECTED_EVENTS="${SELECTED_EVENTS:-}"

CLUSTER_MAX_PARALLEL="${CLUSTER_MAX_PARALLEL:-80}"
if (( MAX_PARALLEL > CLUSTER_MAX_PARALLEL )); then
    echo "Aviso: MAX_PARALLEL=${MAX_PARALLEL} en config excede el máximo permitido para este clúster (${CLUSTER_MAX_PARALLEL})."
    echo "Se ajustará MAX_PARALLEL a ${CLUSTER_MAX_PARALLEL}."
    MAX_PARALLEL="${CLUSTER_MAX_PARALLEL}"
fi

validate_event_list() {
    local list_name="$1"
    local list_value="$2"
    local ev

    for ev in $list_value; do
        if ! [[ "$ev" =~ ^[0-9]+$ ]]; then
            echo "Error: '$ev' en ${list_name} no es un entero positivo."
            exit 1
        fi
        if [ "$ev" -lt 1 ] || [ "$ev" -gt "$TOTAL_EVENTS" ]; then
            echo "Error: evento '$ev' en ${list_name} está fuera del rango 1-${TOTAL_EVENTS}."
            exit 1
        fi
    done
}

validate_event_list "EXCLUDED_EVENTS" "$EXCLUDED_EVENTS"
validate_event_list "SELECTED_EVENTS" "$SELECTED_EVENTS"

BASE_EVENTS=()

if [ -n "$SELECTED_EVENTS" ]; then
    read -r -a BASE_EVENTS <<< "$SELECTED_EVENTS"
    MODE_DESC="lista explícita"
else
    mapfile -t BASE_EVENTS < <(seq 1 "$TOTAL_EVENTS")
    MODE_DESC="rango completo 1-${TOTAL_EVENTS}"
fi

declare -A EXCLUDED_MAP=()
for ev in $EXCLUDED_EVENTS; do
    EXCLUDED_MAP["$ev"]=1
done

declare -A SEEN_MAP=()
FINAL_EVENTS=()

for ev in "${BASE_EVENTS[@]}"; do
    if [ -n "${EXCLUDED_MAP[$ev]:-}" ]; then
        continue
    fi

    if [ -z "${SEEN_MAP[$ev]:-}" ]; then
        FINAL_EVENTS+=("$ev")
        SEEN_MAP["$ev"]=1
    fi
done

if [ "${#FINAL_EVENTS[@]}" -eq 0 ]; then
    echo "Error: no quedaron eventos para ejecutar después de aplicar SELECTED_EVENTS y EXCLUDED_EVENTS."
    exit 1
fi

mapfile -t FINAL_EVENTS < <(printf "%s\n" "${FINAL_EVENTS[@]}" | sort -n)

build_array_spec() {
    local arr=("$@")
    local n="${#arr[@]}"

    if [ "$n" -eq 0 ]; then
        return 1
    fi

    local start="${arr[0]}"
    local prev="${arr[0]}"
    local curr
    local spec=""

    for ((i=1; i<n; i++)); do
        curr="${arr[i]}"

        if [ "$curr" -eq $((prev + 1)) ]; then
            prev="$curr"
            continue
        fi

        if [ -n "$spec" ]; then
            spec+=","
        fi

        if [ "$start" -eq "$prev" ]; then
            spec+="${start}"
        else
            spec+="${start}-${prev}"
        fi

        start="$curr"
        prev="$curr"
    done

    if [ -n "$spec" ]; then
        spec+=","
    fi

    if [ "$start" -eq "$prev" ]; then
        spec+="${start}"
    else
        spec+="${start}-${prev}"
    fi

    echo "$spec"
}

ARRAY_BASE_SPEC="$(build_array_spec "${FINAL_EVENTS[@]}")"
ARRAY_SPEC="${ARRAY_BASE_SPEC}%${MAX_PARALLEL}"

LOGDIR="${REPO_DIR}/outputs/log/logs_plot_em_mc_stop_${CAMPAIGN}_${TIME_GRID}_min_${PHYLST}_${NEUFTY}"
mkdir -p "$LOGDIR"
cp "$CONFIG_FILE" "$LOGDIR/$(basename "$CONFIG_FILE")"

echo "SCRIPT_DIR           : $SCRIPT_DIR"
echo "REPO_DIR             : $REPO_DIR"
echo "JOB_SCRIPT           : $JOB_SCRIPT"
echo "Configuración usada  : $CONFIG_FILE"
echo "Directorio de logs   : $LOGDIR"
echo "Función ROOT         : MakeHistograms_loop_bin_energy_single_pass_new"
echo "Modo de selección    : $MODE_DESC"
echo "TOTAL_EVENTS         : $TOTAL_EVENTS"
echo "MAX_PARALLEL         : $MAX_PARALLEL"
echo "Eventos excluidos    : ${EXCLUDED_EVENTS:-ninguno}"
echo "Eventos seleccionados: ${SELECTED_EVENTS:-todos 1-${TOTAL_EVENTS}}"
echo "N eventos finales    : ${#FINAL_EVENTS[@]}"
echo "Array specification  : $ARRAY_SPEC"

sbatch \
  --chdir="${REPO_DIR}/local_scripts" \
  -J "PLOT_EM_MC_${CAMPAIGN}_${TIME_GRID}_min_${NEUFTY}" \
  -o "${LOGDIR}/plot_em_mc_%A_%a.out" \
  -e "${LOGDIR}/plot_em_mc_%A_%a.err" \
  --array="${ARRAY_SPEC}" \
  --export=ALL,CONFIG_FILE="${CONFIG_FILE}",LOGDIR="${LOGDIR}",REPO_DIR="${REPO_DIR}" \
  "${JOB_SCRIPT}"
