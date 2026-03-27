#!/bin/bash
#------------------ SLURM parameters ------------------#
#SBATCH -p main                  # Partición (ajusta según NLHPC: slims/general/main, etc.)
#SBATCH -n 1                      # 1 tarea por job
#SBATCH -c 1                      # 1 CPU por tarea
#SBATCH --mem-per-cpu=1000        # 1 GB por CPU (ajusta según uso real)
#SBATCH --time=15-00:00:00         # Tiempo máximo (15 dias) (D-HH:MM:SS)
#SBATCH --mail-user=franco.lopez.usquiano@gmail.com
#SBATCH --mail-type=ALL
#------------------------------------------------------#

set -euo pipefail

# Limpia y carga módulos
ml purge
ml root/6.32.06-zen4-i   # o root/6.32.06-zen4-k según prefieras

if [ -z "${CONFIG_FILE:-}" ]; then
    echo "Error: CONFIG_FILE no fue exportado al job."
    exit 1
fi

if [ ! -f "$CONFIG_FILE" ]; then
    echo "Error: no existe CONFIG_FILE: $CONFIG_FILE"
    exit 1
fi

if [ -z "${REPO_DIR:-}" ]; then
    echo "Error: REPO_DIR no fue exportado al job."
    exit 1
fi

source "$CONFIG_FILE"

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
)

for var in "${required_vars[@]}"; do
    if [ -z "${!var+x}" ] || [ -z "${!var}" ]; then
        echo "Error: la variable '$var' no está definida o está vacía en $CONFIG_FILE"
        exit 1
    fi
done

#------------------------------------------------------
# 1) Lista de eventos válidos: 1–NMAX excluyendo algunos
#------------------------------------------------------
# Evento = ID del array

if [ -z "${EXCLUDED_EVENTS+x}" ]; then
    EXCLUDED_EVENTS=""
fi

EVENT_ID="${SLURM_ARRAY_TASK_ID}"

for excluded in $EXCLUDED_EVENTS; do
    if [ "$EVENT_ID" -eq "$excluded" ]; then
        echo "[$(date)] Evento ${EVENT_ID} está excluido. Saliendo sin ejecutar ROOT."
        exit 0
    fi
done

echo "[$(date)] JobID=${SLURM_JOB_ID}, ArrayTaskID=${SLURM_ARRAY_TASK_ID}"
echo "Evento (i) a procesar : ${EVENT_ID}"
echo "Campaña               : ${CAMPAIGN}"
echo "Archivo config        : ${CONFIG_FILE}"
echo "REPO_DIR              : ${REPO_DIR}"
echo "Directorio de logs    : ${LOGDIR:-no definido}"
echo "Parámetros:"
echo "  steps         = ${STEPS}"
echo "  time_grid     = ${TIME_GRID}"
echo "  ndet          = ${NDET}"
echo "  max_steps     = ${MAX_STEPS}"
echo "  bin_seed      = ${BIN_SEED}"
echo "  cut           = ${CUT}"
echo "  phylst        = ${PHYLST}"
echo "  scale factor  = ${SCF}"
echo "  neufieldtype  = ${NEUFTY}"


#------------------------------------------------------
# 2) Ejecutar ROOT llamando a em_loop_steps_update()
#------------------------------------------------------
# Ajusta la ruta a deconv_CRNS.C si es distinta en el NLHPC
#DECONV_PATH="/home/cchen06/deconv/cosmic-ray-neutron-spectrum-deconvolution-program/macros/deconv_CRNS.C"

DECONV_PATH="${REPO_DIR}/macros/deconv_CRNS.C"

if [ ! -f "$DECONV_PATH" ]; then
    echo "Error: no existe el macro ROOT: $DECONV_PATH"
    exit 1
fi

srun root -l -b <<EOF
gROOT->ProcessLine(".L ${DECONV_PATH}");
gROOT->ProcessLine("em_loop_steps_update(\\"${CAMPAIGN}\\",${EVENT_ID},${STEPS},${TIME_GRID},${NDET},${MAX_STEPS},\\"${CUT}\\",\\"${PHYLST}\\",\\"${SCF}\\",\\"${NEUFTY}\\")");
.q
EOF

