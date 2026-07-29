#!/usr/bin/env bash
# Ejecuta un único evento con la misma función C++/ROOT usada en producción,
# sustituyendo solamente la capa SLURM.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

usage() {
    echo "Uso: $0 CONFIG_FILE EVENT_ID" >&2
}

fail() {
    echo "Error: $*" >&2
    exit 1
}

if [ "$#" -ne 2 ]; then
    usage
    exit 2
fi

CONFIG_INPUT="$1"
EVENT_ID="$2"

if [[ "${CONFIG_INPUT}" = /* ]]; then
    CONFIG_FILE="${CONFIG_INPUT}"
else
    CONFIG_FILE="${REPO_DIR}/${CONFIG_INPUT}"
fi

[ -f "${CONFIG_FILE}" ] || fail "no existe la configuración: ${CONFIG_FILE}"
CONFIG_FILE="$(readlink -f "${CONFIG_FILE}")"

[[ "${EVENT_ID}" =~ ^[1-9][0-9]*$ ]] ||
    fail "EVENT_ID debe ser un entero positivo."

# shellcheck disable=SC1090
source "${CONFIG_FILE}"

required_vars=(
    CAMPAIGN STEPS TIME_GRID NDET MAX_STEPS BIN_SEED
    CUT PHYLST SCF NEUFTY
)

for var in "${required_vars[@]}"; do
    if [ -z "${!var+x}" ] || [ -z "${!var}" ]; then
        fail "'${var}' no está definida o está vacía en ${CONFIG_FILE}"
    fi
done

for var in STEPS TIME_GRID NDET MAX_STEPS BIN_SEED; do
    [[ "${!var}" =~ ^[0-9]+$ ]] ||
        fail "'${var}' debe ser un entero no negativo."
done

for var in CAMPAIGN CUT PHYLST SCF NEUFTY; do
    [[ "${!var}" =~ ^[A-Za-z0-9_.-]+$ ]] ||
        fail "'${var}' contiene caracteres no admitidos."
done

if [ -n "${TOTAL_EVENTS:-}" ]; then
    [[ "${TOTAL_EVENTS}" =~ ^[1-9][0-9]*$ ]] ||
        fail "TOTAL_EVENTS debe ser un entero positivo."
    [ "${EVENT_ID}" -le "${TOTAL_EVENTS}" ] ||
        fail "EVENT_ID=${EVENT_ID} supera TOTAL_EVENTS=${TOTAL_EVENTS}."
fi

for excluded in ${EXCLUDED_EVENTS:-}; do
    [[ "${excluded}" =~ ^[1-9][0-9]*$ ]] ||
        fail "'${excluded}' en EXCLUDED_EVENTS no es un entero positivo."
    [ "${EVENT_ID}" -ne "${excluded}" ] ||
        fail "el evento ${EVENT_ID} está excluido por la configuración."
done

case "${PHYLST}" in
    QGSP_BERT)
        CAMPAIGN_TAG="${CAMPAIGN}_QGSP_BERT_${NEUFTY}"
        ;;
    FTFP_BERT)
        CAMPAIGN_TAG="${CAMPAIGN}_FTFP_BERT_${NEUFTY}"
        ;;
    *)
        fail "PHYLST debe ser QGSP_BERT o FTFP_BERT."
        ;;
esac

if [ "${STEPS}" -eq 0 ]; then
    OUTPUT_BASE="EM_stop"
else
    OUTPUT_BASE="EM"
fi

OUTPUT_DIR="${REPO_DIR}/outputs/root/deconv_data_rootfile/${OUTPUT_BASE}/${CAMPAIGN}/${CAMPAIGN_TAG}"
LOG_DIR="${REPO_DIR}/outputs/log/local_em"
OUTPUT_FILE="${OUTPUT_DIR}/EM_unfolding_loop_campaign_${CAMPAIGN}_event_${EVENT_ID}_steps_${STEPS}_timegrid_${TIME_GRID}_ndet_${NDET}.root"
LOG_FILE="${LOG_DIR}/EM_${CAMPAIGN}_event_${EVENT_ID}_${TIME_GRID}min.log"
DECONV_PATH="${REPO_DIR}/macros/deconv_CRNS.C"

mkdir -p "${OUTPUT_DIR}" "${LOG_DIR}" "${REPO_DIR}/outputs/pdf"
[ -f "${DECONV_PATH}" ] || fail "no existe la macro ${DECONV_PATH}"
command -v root >/dev/null 2>&1 || fail "ROOT no está disponible en PATH."

echo "Campaña       : ${CAMPAIGN}"
echo "Evento        : ${EVENT_ID}"
echo "Configuración : ${CONFIG_FILE}"
echo "Parámetros    : steps=${STEPS}, time_grid=${TIME_GRID}, ndet=${NDET}, max_steps=${MAX_STEPS}"
echo "Salida        : ${OUTPUT_FILE}"
echo "Log           : ${LOG_FILE}"

# deconv_CRNS.C construye sus rutas desde ../data y ../outputs.
cd "${SCRIPT_DIR}"

root -l -b 2>&1 <<ROOT_EOF | tee "${LOG_FILE}"
.L ${DECONV_PATH}
if (!gROOT->GetGlobalFunction("em_loop_steps_update")) {
    std::cerr << "No se pudo cargar em_loop_steps_update" << std::endl;
    gSystem->Exit(1);
}
em_loop_steps_update(
    "${CAMPAIGN}",
    ${EVENT_ID},
    ${STEPS},
    ${TIME_GRID},
    ${NDET},
    ${MAX_STEPS},
    "${CUT}",
    "${PHYLST}",
    "${SCF}",
    "${NEUFTY}"
);
.q
ROOT_EOF

[ -f "${OUTPUT_FILE}" ] ||
    fail "ROOT terminó sin crear el archivo esperado: ${OUTPUT_FILE}"

echo "Ejecución EM terminada."
echo "OUTPUT_ROOT=${OUTPUT_FILE}"
