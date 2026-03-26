#!/bin/bash

set -euo pipefail

#------------------------------------------------------
# Uso:
#   bash run_events_em_mc_stop.slurm configs/config_LCO_15m_BEAM.sh
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

# Verifica variables obligatorias
required_vars=(
    CAMPAIGN STEPS TIME_GRID NDET MAX_STEPS BIN_SEED CUT
    PHYLST SCF NEUFTY TOTAL_EVENTS MAX_PARALLEL EXCLUDED_EVENTS
)

for var in "${required_vars[@]}"; do
    if [ -z "${!var}" ]; then
        echo "Error: la variable '$var' no está definida en $CONFIG_FILE"
        exit 1
    fi
done

# EXCLUDED_EVENTS puede quedar vacío si no quieres excluir ninguno
if [ -z "${EXCLUDED_EVENTS+x}" ]; then
    EXCLUDED_EVENTS=""
fi

# Directorio de logs
LOGDIR="${REPO_DIR}/outputs/log/logs_em_mc_stop_${CAMPAIGN}_${TIME_GRID}_min_${PHYLST}_${SCF}_${NEUFTY}"

mkdir -p "$LOGDIR"

# Copia la configuración usada al directorio de salida
cp "$CONFIG_FILE" "$LOGDIR/$(basename "$CONFIG_FILE")"

ARRAY_SPEC="1-${TOTAL_EVENTS}%${MAX_PARALLEL}"

echo "SCRIPT_DIR           : $SCRIPT_DIR"
echo "REPO_DIR             : $REPO_DIR"
echo "Configuración usada  : $CONFIG_FILE"
echo "Directorio de logs   : $LOGDIR"
echo "Array specification  : $ARRAY_SPEC"
echo "Eventos excluidos    : ${EXCLUDED_EVENTS:-ninguno}"

sbatch \
  --chdir="${REPO_DIR}/local_scripts"\
  -J "EM_MC_stop_${CAMPAIGN}_${TIME_GRID}_min_${NEUFTY}" \
  -o "${LOGDIR}/em_mc_stop_%A_%a.out" \
  -e "${LOGDIR}/em_mc_stop_%A_%a.err" \
  --array="${ARRAY_SPEC}" \
  --export=ALL,CONFIG_FILE="${CONFIG_FILE}",LOGDIR="${LOGDIR}",REPO_DIR="${REPO_DIR}" \
  "${SCRIPT_DIR}/run_events_em_mc_stop_jobs.sh"




