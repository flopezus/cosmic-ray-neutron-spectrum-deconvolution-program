#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",160,163,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",165,169,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",170,173,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",175,178,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",181,184,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",186,190,0,15,11,42,1,"cut1")
.q
EOC

