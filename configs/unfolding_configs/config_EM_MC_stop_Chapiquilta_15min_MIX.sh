#!/bin/bash

# ==== CONFIGURACIÓN DE PARÁMETROS FÍSICOS ====
CAMPAIGN="Chapiquilta"  # nombre de campaña
STEPS=0                 # EM con criterio de stop
TIME_GRID=15            # tamaño de la grilla de tiempo en min
NDET=11                 # número de detectores
MAX_STEPS=100           # máximo de steps EM
BIN_SEED=1              # 1 (random seed)
CUT="cut1"              # nombre del corte
PHYLST="FTFP_BERT"      # Response Functions Physics List used in geant4 sim (QGSP_BERT or FTFP_BERT)
SCF="ws"                # SCALE FACTOR, ws: incluye 1/4 en RF, wos: no incluye 1/4 en RF
NEUFTY="MIX"           # ISO, MIX o BEAM, Tipo de hipotesis para el campo  neutronico usado en el calculo de RF

# ==== CONFIGURACIÓN DEL ARRAY ====
TOTAL_EVENTS=838
MAX_PARALLEL=88

SELECTED_EVENTS="155 157 396 405 451 457 467 472 507 524 538 543 544 546 548 549 551 588 598 603 674 675 704 784 804"
EXCLUDED_EVENTS="85 86 87 88 150 630 631 632 633 634 635 636 757 837 838"

