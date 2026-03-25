#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

if [ $# -lt 3 ]; then
  echo "Uso: $0 CAMPAIGN TIME_GRID NEUFTY" >&2
  echo "Ejemplo: $0 LCO 15 BEAM" >&2
  exit 1
fi

CAMPAIGN="$1"
TIME_GRID="$2"
NEUFTY="$3"
PHYLST="FTFP_BERT"

# Ejecuta la concatenación previa
"${SCRIPT_DIR}/merge_files_stats.sh" "$CAMPAIGN" "$TIME_GRID" "$NEUFTY"

# Archivo generado por merge_files_stats.sh
file="${REPO_DIR}/outputs/root/deconv_data_rootfile/EM_MC_stop/${CAMPAIGN}/${CAMPAIGN}_${PHYLST}_${NEUFTY}/${CAMPAIGN}_${TIME_GRID}min_stat.txt"

if [[ ! -f "$file" ]]; then
  echo "Error: no existe el archivo de entrada: $file" >&2
  exit 1
fi

awk '
  /Event:/ {
    if (match($0, /Event:[[:space:]]*([0-9]+)/, m)) {
      curr = m[1] + 0
      events[curr] = 1
      if (min == "" || curr < min) min = curr
      if (max == "" || curr > max) max = curr
    }
  }
  /Accepted:/ {
    if (curr != "" && match($0, /Accepted:[[:space:]]*[0-9]+\/[0-9]+[[:space:]]*\(([0-9.]+)\)%/, m)) {
      acc[curr] = m[1] + 0
    }
  }
  END {
    if (min == "") {
      print "No events found in file." > "/dev/stderr"
      exit 1
    }

    count100 = 0
    countNot = 0
    missingCount = 0
    total_range = max - min + 1

    for (i = min; i <= max; i++) {
      if (i in acc) {
        sumAcc += acc[i]
      }

      if (i in events) {
        if (i in acc) {
          if (acc[i] == 100) {
            count100++
          } else {
            countNot++
            notItems[countNot] = i " (" sprintf("%.1f", acc[i]) "%)"
          }
	} else {
          countNot++
          notItems[countNot] = i " (NA)"
          missingAcc++
        }
      } else {
	missingCount++
        missingList = missingList (missingList ? ", " : "") i
      }
    }

    print "Archivo analizado: " FILENAME
    print "Eventos totales (rango): " total_range " (del " min " al " max ")"

    pct100 = (total_range > 0) ? (count100 * 100 / total_range) : 0
    pctNot = (total_range > 0) ? (countNot * 100 / total_range) : 0
    globalPct = (total_range > 0) ? (sumAcc / total_range) : 0
    globalRem = 100 - globalPct

    print "Eventos completados al 100%: " count100 " (" sprintf("%.1f", pct100) "%)"

    base = "Eventos sin completar al 100%: " countNot " (" sprintf("%.1f", pctNot) "%)"
    if (countNot == 0) {
      print base
    } else {
      print base " ->"
      line = "  " notItems[1]
      items_on_line = 1
      for (i = 2; i <= countNot; i++) {
        if (items_on_line == 6) {
          print line
          line = "  " notItems[i]
          items_on_line = 1
        } else {
          line = line ", " notItems[i]
          items_on_line++
        }
      }
      print line
    }

    print "Eventos no procesados (faltan en el rango): " missingCount (missingCount ? " -> " missingList : "")
    print "Avance global (incluye parciales): " sprintf("%.1f", globalPct) "%, restante: " sprintf("%.1f", globalRem) "%"
  }
' "$file"




