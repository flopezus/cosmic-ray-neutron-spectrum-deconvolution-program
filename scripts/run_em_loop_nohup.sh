#!/bin/bash

# Archivo de salida del log
LOGFILE="em_loop_nohup.out"

nohup root -l -b <<EOF > $LOGFILE 2>&1 &
.L deconv_CRNS.C
em_loop_steps_update("LCO",70,500,15,11,500,"cut1","FTFP_BERT");
.q
EOF

echo "Proceso lanzado con nohup. Revisa el log en $LOGFILE"
