#!/bin/bash

#RUN as follows:
# nohup ./run_loop_fit_events_iterative.sh  > output_fit_loop_events_iterative.log 2>&1 &

#~ for start in 1 101 201 301 401 501 601 701 801; do
#~ for start in 1 51 101 151 201 251 301 351; do
for start in 1 51 101 151 201 251 301 351 401 451 501 551 601 651 701 751 801 851 901; do
    #~ end=$((start+99))
    end=$((start+49))
    root -b <<EOC
.L deconv_EM_MC.C
loop_fit_over_events_range("Chapiquilta", $start, $end, 15, 11)
.q
EOC
done
