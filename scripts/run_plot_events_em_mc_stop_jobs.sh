#!/bin/bash
#------------------ SLURM parameters ------------------#
#SBATCH -p main
#SBATCH -n 1
#SBATCH -c 1
#SBATCH --mem-per-cpu=2800
#SBATCH --time=15-00:00:00
#SBATCH --mail-user=franco.lopez.usquiano@gmail.com
#SBATCH --mail-type=FAIL,END
#------------------------------------------------------#

set -euo pipefail

ml purge
ml root/6.32.06-zen4-i

if [ -z "${CONFIG_FILE:-}" ]; then
    echo "Error: CONFIG_FILE no fue exportado al job." >&2
    exit 1
fi

if [ ! -f "$CONFIG_FILE" ]; then
    echo "Error: no existe CONFIG_FILE: $CONFIG_FILE" >&2
    exit 1
fi

if [ -z "${REPO_DIR:-}" ]; then
    echo "Error: REPO_DIR no fue exportado al job." >&2
    exit 1
fi

if [ ! -d "$REPO_DIR" ]; then
    echo "Error: no existe REPO_DIR: $REPO_DIR" >&2
    exit 1
fi

source "$CONFIG_FILE"

required_vars=(
    CAMPAIGN
    TIME_GRID
    NDET
    PHYLST
    NEUFTY
)

for var in "${required_vars[@]}"; do
    if [ -z "${!var+x}" ] || [ -z "${!var}" ]; then
        echo "Error: la variable '$var' no está definida o está vacía en $CONFIG_FILE" >&2
        exit 1
    fi
done

EXCLUDED_EVENTS="${EXCLUDED_EVENTS:-}"
EVENT_ID="${SLURM_ARRAY_TASK_ID:?SLURM_ARRAY_TASK_ID no está definido.}"

for excluded in $EXCLUDED_EVENTS; do
    if [ "$EVENT_ID" -eq "$excluded" ]; then
        echo "[$(date '+%F %T')] Evento ${EVENT_ID} está excluido. Saliendo sin ejecutar ROOT."
        exit 0
    fi
done

DECONV_PATH="${REPO_DIR}/macros/deconv_EM_MC.C"
if [ ! -f "$DECONV_PATH" ]; then
    echo "Error: no existe el macro ROOT: $DECONV_PATH" >&2
    exit 1
fi

OUTDIR="${REPO_DIR}/outputs/pdf/deconv_data_pdf/EM_MC_fitting/bin_fit_per_event/${CAMPAIGN}/${NEUFTY}"
mkdir -p "$OUTDIR"

echo "[$(date '+%F %T')] JobID=${SLURM_JOB_ID:-no_slurm_job_id}, ArrayTaskID=${SLURM_ARRAY_TASK_ID}"
echo "Evento                : ${EVENT_ID}"
echo "Campaña               : ${CAMPAIGN}"
echo "Archivo config        : ${CONFIG_FILE}"
echo "REPO_DIR              : ${REPO_DIR}"
echo "Directorio de logs    : ${LOGDIR:-no definido}"
echo "Directorio de salida  : ${OUTDIR}"
echo "Macro ROOT            : ${DECONV_PATH}"
echo "Función ROOT          : MakeHistograms_loop_bin_energy_single_pass_new"
echo "Parámetros:"
echo "  time_grid     = ${TIME_GRID}"
echo "  ndet          = ${NDET}"
echo "  phylst        = ${PHYLST}"
echo "  neufieldtype  = ${NEUFTY}"

srun root -l -b <<EOF_ROOT
gROOT->ProcessLine(".L ${DECONV_PATH}");
gROOT->ProcessLine("MakeHistograms_loop_bin_energy_single_pass_new(\"${CAMPAIGN}\",${EVENT_ID},${TIME_GRID},${NDET},\"${PHYLST}\",\"${NEUFTY}\")");
.q
EOF_ROOT

echo "[$(date '+%F %T')] Evento ${EVENT_ID} finalizado correctamente."
