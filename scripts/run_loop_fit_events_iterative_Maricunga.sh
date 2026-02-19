#!/bin/bash

#RUN as follows:
# nohup ./run_loop_fit_events_iterative_Maricunga.sh  > output_fit_loop_events_iterative_Maricunga.log 2>&1 &

for start in 1 51 101 151 201 251 301 351 401; do
    #~ end=$((start+99))
    end=$((start+49))
    root -b <<EOC
.L deconv_EM_MC.C
loop_fit_over_events_range("Maricunga", $start, $end, 15, 11)
.q
EOC
done
