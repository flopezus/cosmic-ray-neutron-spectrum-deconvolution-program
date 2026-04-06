#!/bin/bash

# ==== CONFIGURACIÓN DE PARÁMETROS FÍSICOS ====
CAMPAIGN="SanPedrodeAtacama"          # nombre de campaña
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
TOTAL_EVENTS=386
MAX_PARALLEL=88
EXCLUDED_EVENTS="53 54 55 56 57 58 59 60 61 62 63 64 65"
