#!/bin/bash
root -b <<EOC
.L deconv_CRNS.C
em_loop_events_MC_opt("RetenDesierto",191,195,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",196,200,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",201,201,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",203,207,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",209,210,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",213,217,0,15,11,42,1,"cut1")
em_loop_events_MC_opt("RetenDesierto",218,219,0,15,11,42,1,"cut1")	
.q
EOC

