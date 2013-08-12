#ifndef __CINT__
#include <TString.h>
#include <TFile.h>
#include <TROOT.h>
#include <TBrowser.h>
#include "AliRsnSysErr.h"
#endif

void test()
{
   Printf("Starting test ...");
   AliRsnSysErr *main = new AliRsnSysErr("RsnSysErr","Root of RsnSysErr");

   AliRsnSysErr *t1 = new AliRsnSysErr("t1","Test 1");
   AliRsnSysErr *t11 = new AliRsnSysErr("t11","Test 1 1");
   AliRsnSysErr *t12 = new AliRsnSysErr("t12","Test 1 2");
   t1->Add(t11);
   t1->Add(t12);

   AliRsnSysErr *t2 = new AliRsnSysErr("t2","Test 2");
   AliRsnSysErr *t21 = new AliRsnSysErr("t21","Test 2 1");
   AliRsnSysErr *t22 = new AliRsnSysErr("t22","Test 2 2");
   t2->Add(t21);
   t2->Add(t22);
   
   main->Add(t1);
   main->Add(t2);

   // main->Print();

   TTask *t = main->GetList("/t1");
   // TTask *t = main->GetList("/t1/t12");
   if (t) t->Print();

   return;

   main->ExecuteTask();

   TFile *f = TFile::Open("rsn_out_test.root","RECREATE");
   main->Write();
   f->Close();

   gROOT->GetListOfBrowsables()->Add(main,main->GetName());

   new TBrowser;   
}
