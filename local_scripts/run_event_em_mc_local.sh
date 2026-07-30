#!/usr/bin/env bash
# Ejecuta un único evento EM-MC con la misma función C++/ROOT de producción,
# sin módulos, arreglos ni comandos de SLURM.

set -euo pipefail
umask 0022

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

usage() {
    cat >&2 <<USAGE
Uso de producción:
  $0 CONFIG_FILE EVENT_ID

Uso docente:
  $0 CONFIG_FILE EVENT_ID TARGET_ACCEPTED MAX_MC_TRIALS MC_MAX_STEPS DIFF_LIMIT
USAGE
}

fail() {
    echo "Error: $*" >&2
    exit 1
}

if [ "$#" -ne 2 ] && [ "$#" -ne 6 ]; then
    usage
    exit 2
fi

CONFIG_INPUT="$1"
EVENT_ID="$2"
CLASSROOM_MODE=0

if [ "$#" -eq 6 ]; then
    CLASSROOM_MODE=1
    TARGET_ACCEPTED="$3"
    MAX_MC_TRIALS="$4"
    MC_MAX_STEPS="$5"
    DIFF_LIMIT="$6"
else
    # Solo se usan para mensajes y rutas de log. La llamada de dos argumentos
    # omite estos parámetros C++ y activa los defaults de producción.
    TARGET_ACCEPTED=10000
    MAX_MC_TRIALS=20000000
    MC_MAX_STEPS=20
    DIFF_LIMIT=0.02
fi

if [[ "${CONFIG_INPUT}" = /* ]]; then
    CONFIG_FILE="${CONFIG_INPUT}"
else
    CONFIG_FILE="${REPO_DIR}/${CONFIG_INPUT}"
fi

[ -f "${CONFIG_FILE}" ] || fail "no existe la configuración: ${CONFIG_FILE}"
CONFIG_FILE="$(readlink -f "${CONFIG_FILE}")"

[[ "${EVENT_ID}" =~ ^[1-9][0-9]*$ ]] ||
    fail "EVENT_ID debe ser un entero positivo."

for value in "${TARGET_ACCEPTED}" "${MAX_MC_TRIALS}" "${MC_MAX_STEPS}"; do
    [[ "${value}" =~ ^[1-9][0-9]*$ ]] ||
        fail "TARGET_ACCEPTED, MAX_MC_TRIALS y MC_MAX_STEPS deben ser enteros positivos."
done

awk -v value="${DIFF_LIMIT}" \
    'BEGIN { exit !(value ~ /^([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][-+]?[0-9]+)?$/ && value > 0) }' ||
    fail "DIFF_LIMIT debe ser un número positivo."

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
        CAMPAIGN_TAG="${CAMPAIGN}_${NEUFTY}"
        ;;
    FTFP_BERT)
        CAMPAIGN_TAG="${CAMPAIGN}_FTFP_BERT_${NEUFTY}"
        ;;
    *)
        fail "PHYLST debe ser QGSP_BERT o FTFP_BERT."
        ;;
esac

if [ "${STEPS}" -eq 0 ]; then
    OUTPUT_BASE="EM_MC_stop"
    OUTPUT_SUFFIX="_MC_stop.root"
else
    OUTPUT_BASE="EM_MC"
    OUTPUT_SUFFIX="_MC.root"
fi

OUTPUT_DIR="${REPO_DIR}/outputs/root/deconv_data_rootfile/${OUTPUT_BASE}/${CAMPAIGN}/${CAMPAIGN_TAG}"
LOG_DIR="${REPO_DIR}/outputs/log/local_em_mc"
OUTPUT_FILE="${OUTPUT_DIR}/EM_unfolding_loop_campaign_${CAMPAIGN}_event_${EVENT_ID}_steps_${STEPS}_timegrid_${TIME_GRID}_ndet_${NDET}${OUTPUT_SUFFIX}"
LOG_FILE="${LOG_DIR}/EM_MC_${CAMPAIGN}_event_${EVENT_ID}_${TIME_GRID}min_target_${TARGET_ACCEPTED}_trials_${MAX_MC_TRIALS}.log"
DECONV_PATH="${REPO_DIR}/macros/deconv_CRNS.C"

mkdir -p "${OUTPUT_DIR}" "${LOG_DIR}" "${REPO_DIR}/outputs/pdf"
[ -w "${OUTPUT_DIR}" ] ||
    fail "no hay permiso de escritura en ${OUTPUT_DIR}"
[ -f "${DECONV_PATH}" ] || fail "no existe la macro ${DECONV_PATH}"
command -v root >/dev/null 2>&1 || fail "ROOT no está disponible en PATH."

echo "Campaña        : ${CAMPAIGN}"
echo "Evento         : ${EVENT_ID}"
echo "Configuración  : ${CONFIG_FILE}"
echo "Modo           : $([ "${CLASSROOM_MODE}" -eq 1 ] && echo docente || echo producción)"
echo "Aceptados meta : ${TARGET_ACCEPTED}"
echo "Intentos máx.  : ${MAX_MC_TRIALS}"
echo "Pasos MC máx.  : ${MC_MAX_STEPS}"
echo "Límite diff    : ${DIFF_LIMIT}"
echo "Salida         : ${OUTPUT_FILE}"
echo "Log            : ${LOG_FILE}"
echo "Mapeo heredado : MAX_STEPS -> bin_seed; BIN_SEED -> random_seed"

if [ "${CLASSROOM_MODE}" -eq 1 ]; then
    OPTIONAL_MC_ARGS=", ${TARGET_ACCEPTED}, ${MAX_MC_TRIALS}, ${MC_MAX_STEPS}, ${DIFF_LIMIT}"
else
    OPTIONAL_MC_ARGS=""
fi

# deconv_CRNS.C construye sus rutas desde ../data y ../outputs.
cd "${SCRIPT_DIR}"

root -l -b 2>&1 <<ROOT_EOF | tee "${LOG_FILE}"
.L ${DECONV_PATH}
if (!gROOT->GetGlobalFunction("em_loop_MC_opt_new_update")) {
    std::cerr << "No se pudo cargar em_loop_MC_opt_new_update" << std::endl;
    gSystem->Exit(1);
}
em_loop_MC_opt_new_update(
    "${CAMPAIGN}",
    ${EVENT_ID},
    ${STEPS},
    ${TIME_GRID},
    ${NDET},
    ${MAX_STEPS},
    ${BIN_SEED},
    "${CUT}",
    "${PHYLST}",
    "${SCF}",
    "${NEUFTY}"${OPTIONAL_MC_ARGS}
);
.q
ROOT_EOF

[ -s "${OUTPUT_FILE}" ] ||
    fail "ROOT terminó sin crear un archivo válido: ${OUTPUT_FILE}"

echo "Ejecución EM-MC terminada."
echo "OUTPUT_ROOT=${OUTPUT_FILE}"
