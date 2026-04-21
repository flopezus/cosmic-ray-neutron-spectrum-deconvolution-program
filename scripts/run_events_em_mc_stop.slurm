#!/bin/bash

set -euo pipefail

#------------------------------------------------------
# Uso:
#   bash run_events_em_mc_stop.slurm configs/config_EM_MC_stop_LCO_15min_BEAM.sh
#------------------------------------------------------

# Verifica que se entregue un archivo de configuración
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

if [ $# -lt 1 ]; then
    echo "Uso: $0 archivo_config.sh"
    echo "Ejemplo:"
    echo "  $0 ${REPO_DIR}/configs/unfolding_configs/config_EN_MC_stop_LCO_15min_BEAM.sh"
    exit 1
fi

CONFIG_FILE="$(readlink -f "$1")"

# Verifica que exista
if [ ! -f "$CONFIG_FILE" ]; then
    echo "Error: no existe el archivo de configuración: $CONFIG_FILE"
    exit 1
fi

# Carga la configuración externa
source "$CONFIG_FILE"

#------------------------------------------------------
# Variables obligatorias
#------------------------------------------------------
required_vars=(
    CAMPAIGN
    STEPS
    TIME_GRID
    NDET
    MAX_STEPS
    BIN_SEED
    CUT
    PHYLST
    SCF
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

# Variables opcionales
EXCLUDED_EVENTS="${EXCLUDED_EVENTS:-}"
SELECTED_EVENTS="${SELECTED_EVENTS:-}"

#------------------------------------------------------
# Validación simple de listas
#------------------------------------------------------
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

#------------------------------------------------------
# Construcción de la lista base de eventos
#------------------------------------------------------
BASE_EVENTS=()

if [ -n "$SELECTED_EVENTS" ]; then
    read -r -a BASE_EVENTS <<< "$SELECTED_EVENTS"
    MODE_DESC="lista explícita"
else
    mapfile -t BASE_EVENTS < <(seq 1 "$TOTAL_EVENTS")
    MODE_DESC="rango completo 1-${TOTAL_EVENTS}"
fi

#------------------------------------------------------
# Tabla de exclusión
#------------------------------------------------------
declare -A EXCLUDED_MAP=()
for ev in $EXCLUDED_EVENTS; do
    EXCLUDED_MAP["$ev"]=1
done

#------------------------------------------------------
# Lista final: única, filtrada, ordenada
#------------------------------------------------------
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

#------------------------------------------------------
# Convierte lista de enteros a formato Slurm array
# Ejemplo: 1 2 3 7 9 10 -> 1-3,7,9-10
#------------------------------------------------------
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

#------------------------------------------------------
# Directorio de logs
#------------------------------------------------------
LOGDIR="${REPO_DIR}/outputs/log/logs_em_mc_stop_${CAMPAIGN}_${TIME_GRID}_min_${PHYLST}_${SCF}_${NEUFTY}"
mkdir -p "$LOGDIR"

# Copia la configuración usada al directorio de salida
cp "$CONFIG_FILE" "$LOGDIR/$(basename "$CONFIG_FILE")"

#------------------------------------------------------
# Resumen
#------------------------------------------------------
echo "SCRIPT_DIR           : $SCRIPT_DIR"
echo "REPO_DIR             : $REPO_DIR"
echo "Configuración usada  : $CONFIG_FILE"
echo "Directorio de logs   : $LOGDIR"
echo "Modo de selección    : $MODE_DESC"
echo "TOTAL_EVENTS         : $TOTAL_EVENTS"
echo "MAX_PARALLEL         : $MAX_PARALLEL"
echo "Eventos excluidos    : ${EXCLUDED_EVENTS:-ninguno}"
echo "Eventos seleccionados: ${SELECTED_EVENTS:-todos 1-${TOTAL_EVENTS}}"
echo "N eventos finales    : ${#FINAL_EVENTS[@]}"
echo "Array specification  : $ARRAY_SPEC"

sbatch \
  --chdir="${REPO_DIR}/local_scripts" \
  -J "EM_MC_stop_${CAMPAIGN}_${TIME_GRID}_min_${NEUFTY}" \
  -o "/dev/null" \
  -e "${LOGDIR}/em_mc_stop_%A_%a.err" \
  --array="${ARRAY_SPEC}" \
  --export=ALL,CONFIG_FILE="${CONFIG_FILE}",LOGDIR="${LOGDIR}",REPO_DIR="${REPO_DIR}" \
  "${SCRIPT_DIR}/run_events_em_mc_stop_jobs.sh"


