#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",93,93,0,15,11,42,1,"cut1")
.q
EOC

