//
// *** Class AliRsnSysErr ***
//
// TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

#include <TSystem.h>
#include <TError.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TH1.h>
#include <TList.h>
#include <TGraphErrors.h>
#include <TBrowser.h>

#include "AliRsnUtils.h"
#include "AliRsnSysErr.h"

ClassImp(AliRsnSysErr)

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : AliRsnTask(name, title),
   fList(0)
{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : AliRsnTask(copy),
   fList(copy.fList)
{
//
// Copy constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr &AliRsnSysErr::operator=(const AliRsnSysErr &copy)
{
//
// Assignment constructor
//

   TTask::operator=(copy);
   if (this == &copy)
      return *this;

   fList = copy.fList;

   return (*this);
}

AliRsnSysErr::~AliRsnSysErr()
{
//
// Destructor
//
   
   // fList->Delete();
   // SafeDelete(fList);

}

void AliRsnSysErr::Browse(TBrowser *b)
{
   // Browse the list of tasks.
   // It is recommended to add the top level task to the list of
   // ROOT browsables by:
   //    gROOT->GetListOfBrowsables()->Add(myTopLevelTask)

   if (fTasks) fTasks->Browse(b);
   if (fList) b->Add(fList);
   // if (fHistogram) b->Add(fHistogram);
   
}


TH1D *AliRsnSysErr::CreateHistogram(const char *path, const char *tmpl, const char *postfix)
{
   // expanding path so we can use ~, $HOME, ...
   TString fullPath = gSystem->ExpandPathName(path);
   TGraphErrors *gr = new TGraphErrors(fullPath.Data(), tmpl);
   if (!gr) {
      ::Error("AliRsnSysErr::CreateHistogram", TString::Format("Error opening graph from %s !!!", fullPath.Data()).Data());
      return 0;
   }

   gr->SetName(TString::Format("%s_%s", GetFullPath("_", kTRUE).Data(), postfix).Data());

   TH1D *h = AliRsnUtils::Graph2Hist(gr, kFALSE, 0.0);

   // removing tmp graph
   SafeDelete(gr);

   // setting current histogram to fHistogram
   AddHistogramToList(h,postfix);

   return h;
}

void AliRsnSysErr::AddHistogramToList(TH1D *h, const char *postfix) 
{
   if (!h) return;

   TH1D *hOld = 0;
   if (fList) {
      hOld = GetHistogram(postfix);
      if (hOld) {
         fList->Remove(hOld);
         SafeDelete(hOld);
      }
   }

   if (!fList) {
      fList = new TList();
      fList->SetName("Histos");
   }
   fList->Add(h);
   
}

TH1D *AliRsnSysErr::GetHistogram(const char *postfix) 
{

   if (!fList || !fList->GetEntries()) return 0;

   return (TH1D *)fList->FindObject(TString::Format("%s_%s",GetFullPath("_", kTRUE).Data(),postfix).Data());
}


Bool_t AliRsnSysErr::ImportDirectories(const char *dir, const char *filename, const char *tmpl)
{
   TString fullPath = gSystem->ExpandPathName(dir);

   if (gSystem->AccessPathName(fullPath)) {
      ::Error("AliRsnSysErr::ImportDirectories", TString::Format("Directory %s doesn't exist !!!", fullPath.Data()).Data());
      return kFALSE;
   }
   
   TString out = gSystem->GetFromPipe(TString::Format("ls -1 %s", fullPath.Data()).Data());
   if (out.IsNull()) {
      ::Error("AliRsnSysErr::ImportDirectories",
              TString::Format("No files or directories found in '%s' !!!", dir).Data());
      return kFALSE;
   }

   
   TObjArray *t = out.Tokenize("\n");
   TObjString *so;
   TString s, curPath, tmpPath;
   TIter next(t);
   AliRsnSysErr *se;
   while ((so = (TObjString *) next())) {
      s = so->GetString();
      curPath = fullPath+"/"+s;
      if (!gSystem->Exec(TString::Format("[ -f %s ]", curPath.Data()).Data())) {
         // if we have file
         tmpPath = TString::Format("%s/%s",fullPath.Data(), filename).Data();
         if (!curPath.CompareTo(tmpPath.Data()))
            CreateHistogram(curPath.Data(),tmpl);
      } else {
         // if we have directory or link
         se = new AliRsnSysErr(s.Data(),s.Data());
         if (se) {
            Add(se);
            se->ImportDirectories(curPath.Data(), filename, tmpl);
         }
      }
   }

   return kTRUE;
}


void AliRsnSysErr::Exec(Option_t *option)
{
   Printf("Executing: %s level=%d", GetName(), GetLevel());

}
