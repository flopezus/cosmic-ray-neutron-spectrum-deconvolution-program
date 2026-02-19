#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",130,132,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",134,136,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",138,138,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",140,144,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",145,148,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",150,153,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",155,159,0,15,11,42,1,"cut1")

.q
EOC

