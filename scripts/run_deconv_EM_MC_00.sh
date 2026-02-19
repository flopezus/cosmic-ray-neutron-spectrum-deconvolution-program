#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",98,99,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",101,103,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",105,109,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",110,114,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",117,121,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",123,123,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",125,128,0,15,11,42,1,"cut1")
.q
EOC

