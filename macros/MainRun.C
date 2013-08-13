#ifndef __CINT__
#include <TString.h>
#include <TStopwatch.h>
#endif

void MainRun(TString macro, TString macro_argc, TString projectDir = "") {

   gSystem->Load("libGui.so");
   gSystem->Load("libRsnSysErr.so");

   gSystem->AddIncludePath(TString::Format("-I%sRsnSysErr", projectDir.Data()).Data());
   TStopwatch timer;
   timer.Start();

   gROOT->ProcessLine(TString::Format(".L %s+", macro.Data()).Data());
   macro.ReplaceAll(".C","");
   gROOT->ProcessLine(TString::Format("%s(%s)", macro.Data(),macro_argc.Data()).Data());

   timer.Stop();
   timer.Print();
}
