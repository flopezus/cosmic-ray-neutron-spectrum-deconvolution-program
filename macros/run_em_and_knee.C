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
// nohup root -l -b -q run_em_stop.C > output_run_em_stop.log 2>&1 & 

	
void run_em_and_knee(){

	gROOT->ProcessLine(".L deconv_CRNS.C");
	gROOT->ProcessLine("em_and_knee_loop_event_list_from_singlefile_update(\"LCO\", 15, 200, 11,\"FTFP_BERT\",\"ws\")");
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
  run_em_and_knee(); // just call the "ROOT Script"
  return 0;
}
#endif /* !defined(__CINT__) && !defined(__ACLIC__) */
