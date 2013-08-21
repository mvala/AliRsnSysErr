#ifndef __CINT__
#include <TString.h>
#include <TFile.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TH1.h>
#include "AliRsnSysErr.h"
#endif

void test_rsn_sys_err()
{
   Printf("Starting test ...");
   AliRsnSysErr *main = new AliRsnSysErr("MaxDev","My MaxDev");
   main->ImportDirectories("pt", "~/Documents/Work/Presentations/2013/RESONANCE_2013-08-16/analysis/2013-08-16/pp_2.76_DATA_LHC11a_ESD/TPC30/0","RFE");

   Bool_t rc;
   AliRsnSysErr::ELoopAxis axisLoop;
   TArrayI *actions;

   axisLoop = AliRsnSysErr::kY;
//    axisLoop = AliRsnSysErr::kX;
   Int_t nActions = 5;
   actions = new TArrayI(nActions);
   actions->AddAt(-AliRsnSysErr::kMax,0);
   actions->AddAt(AliRsnSysErr::kMean,1);
   actions->AddAt(-AliRsnSysErr::kStdDev,2);
   actions->AddAt(-AliRsnSysErr::kMaxDev,3);
   actions->AddAt(-AliRsnSysErr::kMinDev,4);
//    actions->AddAt(AliRsnSysErr::kStdDev,1);
//    actions->AddAt(AliRsnSysErr::kMaxDev,2);
//    actions->AddAt(AliRsnSysErr::kMax,3);
//    actions->AddAt(AliRsnSysErr::kAverage,4);
   rc = main->SetLevelAction(0, actions, axisLoop, 1.2);
   if (!rc) return;

   main->Print();
   main->ExecuteTask();
//    main->Exec("");
//    main->ExecuteTasks("");

   TFile *f = TFile::Open("rsn_out_test_sys_err.root","RECREATE");
   main->Write();
   f->Close();

   Printf("=== DONE ===");
}
