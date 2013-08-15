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

//______________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : AliRsnTask(name, title),
   fList(0),
   fType(kValues),
   fActions(0)
{
   //
   // Defauult constructor
   //
   
   // We need that current task is executed after sub-tasks
   fExecTaskBefore = kFALSE;
}

//______________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : AliRsnTask(copy),
   fList(copy.fList),
   fType(copy.fType),
   fActions(copy.fActions)
{
   //
   // Copy constructor
   //

}

//______________________________________________________________________________
AliRsnSysErr &AliRsnSysErr::operator=(const AliRsnSysErr &copy)
{
   //
   // Assignment constructor
   //

   TTask::operator=(copy);
   if (this == &copy)
      return *this;

   fList = copy.fList;
   fType = copy.fType;
   fActions = copy.fActions;

   return (*this);
}

//______________________________________________________________________________
AliRsnSysErr::~AliRsnSysErr()
{
   //
   // Destructor
   //

   // fList->Delete();
   // SafeDelete(fList);

}

//______________________________________________________________________________
void AliRsnSysErr::Browse(TBrowser *b)
{
   // Browse the list of tasks.
   // It is recommended to add the top level task to the list of
   // ROOT browsables by:
   //    gROOT->GetListOfBrowsables()->Add(myTopLevelTask)

   if (fTasks) fTasks->Browse(b);
   if (fList) b->Add(fList);
}


//______________________________________________________________________________
TH1D *AliRsnSysErr::CreateHistogramFromGraph(const char *path, const char *tmpl, const char *postfix)
{
   //
   // CreateHistogramFromGraph
   //
   
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

//______________________________________________________________________________
void AliRsnSysErr::AddHistogramToList(TH1D *h, const char *postfix)
{
   //
   // AddHistogramToList
   //
   
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

//______________________________________________________________________________
TH1D *AliRsnSysErr::GetHistogram(const char *postfix)
{
   //
   // GetHistogram
   //

   if (!fList || !fList->GetEntries()) return 0;

   return (TH1D *)fList->FindObject(TString::Format("%s_%s",GetFullPath("_", kTRUE).Data(),postfix).Data());
}


//______________________________________________________________________________
Bool_t AliRsnSysErr::ImportDirectories(const char *dir, const char *filename, const char *tmpl)
{
   //
   // ImportDirectories
   //
   
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

   Bool_t rc;
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
         if (!curPath.CompareTo(tmpPath.Data())) {
            TH1D *h = CreateHistogramFromGraph(curPath.Data(),tmpl);
            if (!h) return kFALSE;
         }
      } else {
         // if we have directory or link
         se = new AliRsnSysErr(s.Data(),s.Data());
         if (se) {
            Add(se);
            rc = se->ImportDirectories(curPath.Data(), filename, tmpl);
            if (!rc) return kFALSE;
         }
      }
   }

   return kTRUE;
}


//______________________________________________________________________________
void AliRsnSysErr::Exec(Option_t *option)
{
   //
   // Exec
   //
   Printf("Executing: %s level=%d", GetName(), GetLevel());

}

//______________________________________________________________________________
Bool_t AliRsnSysErr::SetLevelAction(Int_t level, AliRsnSysErr::EType type, TBits *actions)
{
   //
   // SetLevelAction
   //
   
   if (fParent) {
      ::Error("AliRsnSysErr::SetLevelAction", "You can set actions on main AliRsnSysErr (with level 0) !!!");
      return kFALSE;
   }
   
   if (type<0 || type>=kNTypes) {
      ::Error("AliRsnSysErr::SetLevelAction", "Wrong type !!!");
      return kFALSE;
   }
   
   if (!actions) {
      ::Error("AliRsnSysErr::SetLevelAction", "'actions' is null !!!");
      return kFALSE;
   }
   
   fType = type;
   fActions = actions;
   
   return kTRUE;
}
