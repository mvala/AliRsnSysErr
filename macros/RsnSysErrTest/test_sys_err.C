#ifndef __CINT__
#include <TString.h>
#include <TFile.h>
#include <TROOT.h>
#include <TBrowser.h>
#include <TH1.h>
#include "AliRsnSysErr.h"
#endif

void test_sys_err()
{
   Printf("Starting test ...");
   AliRsnSysErr *main = new AliRsnSysErr("RsnSysErr","Root of RsnSysErr");
   main->CreateHistogram("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/KTPCnsig30_STD2010_PRIMARY_00/RFE","%lg %lg %lg %lg");

   main->ExecuteTask();

   TH1D *h = main->GetHistogram();
   if (h) h->Print("all");

   TFile *f = TFile::Open("rsn_out_test_sys_err.root","RECREATE");
   main->Write();
   f->Close();

   gROOT->GetListOfBrowsables()->Add(main,main->GetName());

   new TBrowser;   
}
