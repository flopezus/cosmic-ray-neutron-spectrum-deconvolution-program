#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",221,225,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",226,230,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",231,235,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",236,238,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",241,243,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",245,247,0,15,11,42,1,"cut1")

.q
EOC

