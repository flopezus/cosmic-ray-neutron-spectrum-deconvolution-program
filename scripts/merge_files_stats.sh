  GNU nano 5.6.1                                              merge_files_stats.sh                                                        
#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

if [ $# -lt 3 ]; then
    echo "Uso: $0 CAMPAIGN TIME_GRID NEUFTY"
    echo "Ejemplo: $0 LCO 15 BEAM"
    exit 1
fi

CAMPAIGN="$1"
TIME_GRID="$2"
NEUFTY="$3"

PHYLST="FTFP_BERT"

INPUT_DIR="${REPO_DIR}/outputs/root/deconv_data_rootfile/EM_MC_stop/${CAMPAIGN}/${CAMPAIGN}_${PHYLST}_${NEUFTY}"
OUTPUT_FILE="${INPUT_DIR}/${CAMPAIGN}_${TIME_GRID}min_stat.txt"

if [ ! -d "$INPUT_DIR" ]; then
    echo "Error: no existe el directorio de entrada:"
    echo "  $INPUT_DIR"
    exit 1
fi

mapfile -t files < <(find "$INPUT_DIR" -maxdepth 1 -type f -name '*_event_*.txt' | sort -V)

if [ ${#files[@]} -eq 0 ]; then
    echo "Error: no se encontraron archivos '*_event_*.txt' en:"
    echo "  $INPUT_DIR"
    exit 1
fi

{
    for f in "${files[@]}"; do
        cat "$f"
        echo
    done
} > "$OUTPUT_FILE"

echo "Archivo generado:"
echo "  $OUTPUT_FILE"
echo "Se concatenaron ${#files[@]} archivos."




