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
   // main->CreateHistogram("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/KTPCnsig30_STD2010_PRIMARY_00/RFE","%lg %lg %lg %lg");

   // main->ImportDirectories("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/","R");
   main->ImportDirectories("~/ALICE/RSN_OUT/2013-08-16/OUT/TPC30/0/","RFE");

   // main->ExecuteTask();
   main->Print();


   TFile *f = TFile::Open("rsn_out_test_sys_err.root","RECREATE");
   main->Write();
   f->Close();


   return;
   AliRsnSysErr *t = (AliRsnSysErr *) main->GetListByPath("/RsnSysErr/KTPCnsig30_STD2010_PRIMARY_00");
   if (!t) return;
   TH1D *h = t->GetHistogram();
   if (h) h->Print("all");

   t = (AliRsnSysErr *) main->GetListByPath("/RsnSysErr/KTPCnsig30_STD2010_PRIMARY_CHI2ITS036_00");
   if (!t) return;
   h = t->GetHistogram();
   if (h) h->Print("all");


   gROOT->GetListOfBrowsables()->Add(main,main->GetName());

   new TBrowser;
}
