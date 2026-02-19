#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

void run_chapiquilta_em_mc_stop_4() { // La función principal tiene el mismo nombre que el archivo
    gROOT->ProcessLine(".L /home/flopez/LIN/TESIS_DOC/Analysis/deconv/deconv_CRNS.C");
    gROOT->ProcessLine("em_loop_events_MC_opt_new(\"Chapiquilta\",31,35,0,15,11,42,1,\"cut1\")");
}

#if !defined(__CINT__) && !defined(__ACLIC__)
int main(int /*argc*/, char ** /*argv*/) {
    run_chapiquilta_em_mc_stop_4(); // Llama a la función principal
    return 0;
}
#endif /* !defined(__CINT__) && !defined(__ACLIC__) */
