#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

//
// "ROOT Script" entry point (the same name as the "filename's base").
//
// [bash/csh] root load_macro.c
// [bash/csh] root load_macro.c++
// root [0] .x load_macro.cxx
// root [0] .x load_macro.cxx++
//

// RUN USING
// nohup root -l -b -q run_em_mc_stop.C > output.log 2>&1 &
	
void run_em_mc_stop(){

	gROOT->ProcessLine(".L deconv_CRNS.C");
	//~ gROOT->ProcessLine("em_loop_events_MC_opt("RetenDesierto",30,30,0,15,11,42,1,"cut1")");
	gROOT->ProcessLine("em_loop_events_MC_opt_new(\"Chapiquilta\",1,10,0,15,11,42,1,\"cut1\")");
}

#if !defined(__CINT__) && !defined(__ACLIC__)
//
// "Standalone Application" entry point ("main").
//
// `root-config --cxx --cflags` -o RunMe RunMe.cxx `root-config --libs`
// ./RunMe
//
int main(int /*argc*/, char ** /*argv*/)
{
  run_em_mc_stop(); // just call the "ROOT Script"
  return 0;
}
#endif /* !defined(__CINT__) && !defined(__ACLIC__) */
