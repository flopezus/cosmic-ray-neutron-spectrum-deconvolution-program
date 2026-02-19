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
// nohup root -l -b -q run_loop_fit_events.C > output_fit_events.log 2>&1 &
	
void run_loop_fit_events(){

	gROOT->ProcessLine(".L deconv_EM_MC.C");
	//~ gROOT->ProcessLine("loop_fit_over_events_range(\"Chapiquilta\",1,260,15,11)");
	//~ gROOT->ProcessLine("loop_fit_over_events_range(\"Chapiquilta\",1,400,15,11)");
	//~ gROOT->ProcessLine("loop_fit_over_events_range(\"Chapiquilta\",371,390,15,11)");
	gROOT->ProcessLine("loop_fit_over_events_range(\"Chapiquilta\",391,430,15,11)");
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
  run_loop_fit_events(); // just call the "ROOT Script"
  return 0;
}
#endif /* !defined(__CINT__) && !defined(__ACLIC__) */
