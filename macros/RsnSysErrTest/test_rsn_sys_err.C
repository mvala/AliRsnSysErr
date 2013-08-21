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
   AliRsnSysErr *main = new AliRsnSysErr("RsnSysErr","Root of RsnSysErr");
   // main->CreateHistogram("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/KTPCnsig30_STD2010_PRIMARY_00/RFE","%lg %lg %lg %lg");

   // main->ImportDirectories("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/","R");
   main->ImportDirectories("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/","RFE");

   Bool_t rc;
   AliRsnSysErr::EType type;
   AliRsnSysErr::EActionType actType;

   type = AliRsnSysErr::kValues;
   actType = AliRsnSysErr::kMax;
   rc = main->SetLevelAction(0, type, actType);
   if (!rc) return;

   type = AliRsnSysErr::kValues;
   actType = AliRsnSysErr::kMaxDev;
   rc = main->SetLevelAction(1, type, actType);
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
