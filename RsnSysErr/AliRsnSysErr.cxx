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
#include <TH2.h>
#include <TList.h>
#include <TGraphErrors.h>
#include <TBrowser.h>

#include "AliRsnUtils.h"
#include "AliRsnSysErr.h"

ClassImp(AliRsnSysErr)

//______________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : AliRsnTask(name, title),
   fList(0),
   fAxisLoop(kY),
   fActions(0),
   fInitValue(0.0),
   fValue(fInitValue)
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
   fAxisLoop(copy.fAxisLoop),
   fActions(copy.fActions),
   fInitValue(copy.fInitValue),
   fValue(copy.fValue)
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
   fAxisLoop = copy.fAxisLoop;
   fActions = copy.fActions;
   fInitValue = copy.fInitValue;
   fValue = copy.fValue;

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

   SafeDelete(fActions);

}

//______________________________________________________________________________
void AliRsnSysErr::Init()
{
   //
   // Init
   //

   if (!fList) {
      fList = new TList();
      fList->SetName("Histos");
   }
}


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

   Init();
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
Bool_t AliRsnSysErr::ImportDirectories(const char *postfix, const char *dir, const char *filename, const char *tmpl)
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

   Init();

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
            TH1D *h = CreateHistogramFromGraph(curPath.Data(),tmpl, postfix);
            if (!h) return kFALSE;
         }
      } else {
         // if we have directory or link
         se = new AliRsnSysErr(s.Data(),s.Data());
         if (se) {
            se->Init();
            Add(se);
            rc = se->ImportDirectories(postfix, curPath.Data(), filename, tmpl);
            if (!rc) return kFALSE;
         }
      }
   }

   return kTRUE;
}

//______________________________________________________________________________
Bool_t AliRsnSysErr::SetLevelAction(Int_t level, TArrayI *actions, AliRsnSysErr::ELoopAxis axisLoop, Double_t initVal)
{
   //
   // SetLevelAction
   //

//    if (fParent) {
//       ::Error("AliRsnSysErr::SetLevelAction", "You can set actions on main AliRsnSysErr (with level 0) !!!");
//       return kFALSE;
//    }

   if (axisLoop<0 || axisLoop>=kNLoopAxis) {
      ::Error("AliRsnSysErr::SetLevelAction", "Wrong EAxisLoop type !!!");
      return kFALSE;
   }

   if (!actions) {
      ::Error("AliRsnSysErr::SetLevelAction", "TArrayI 'actions' is null !!!");
      return kFALSE;
   }

   if (!level) {
      SetAxisLoopType(axisLoop);
      SetActions(actions);
      SetInitValue(initVal);
      return kTRUE;
   }

   TIter next(fTasks);
   AliRsnSysErr *se;
   Int_t l=0;
   while ((se = (AliRsnSysErr *)next())) {
      if (se->GetLevel() == level) {
         se->SetAxisLoopType(axisLoop);
         se->SetActions(actions);
         se->SetInitValue(initVal);
      } else {
         if (!se->SetLevelAction(level, actions, axisLoop, initVal)) return kFALSE;
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
//    Printf("Executing: %s level=%d", GetName(), GetLevel());
//    if (fList) {
//       Printf("fList=%d",fList->GetEntries());
//       fList->Print();
//    }

   const char *nameTmp="pt";

   // if there is no action we return
   if (!fActions) return;

   if (!fTasks || fTasks->GetEntries()<=0) return;

   AliRsnSysErr *se = (AliRsnSysErr *) fTasks->At(0);

   TH1D *h = se->GetHistogram(nameTmp);
   if (!h) return;
   Printf("axisLoop=%d actions=%d", fAxisLoop, fActions ? fActions->GetSize() : -1);


   Int_t nBinsX = h->GetNbinsX();
   Int_t nBinsY = fTasks->GetEntries();
   Printf("Creating TH2D with nBinsX=%d nBinsY=%d",nBinsX, nBinsY);

   TH2D *hTmp = new TH2D(TString::Format("%s_h2",GetFullPath("_",kTRUE).Data()).Data(),
                         TString::Format("%s (TmpH2)",GetFullPath("_",kTRUE).Data()).Data(),
                         nBinsX, -0.5, nBinsX - 0.5,
                         nBinsY, -0.5, nBinsY - 0.5);

   fList->Add(hTmp);
   TIter next(fTasks);
   Int_t i,c=1;
   while((se = (AliRsnSysErr *)next())) {
      h = se->GetHistogram(nameTmp);
      for (i=1; i<h->GetNbinsX()+1; i++) {
         if (c==1) hTmp->GetXaxis()->SetBinLabel(i,TString::Format("%.2f",h->GetXaxis()->GetBinCenter(i)).Data());
         hTmp->SetBinContent(i,c,h->GetBinContent(i));
      }
      hTmp->GetYaxis()->SetBinLabel(c,TString::Format("%s",se->GetName()).Data());
      c++;
   }
//    hTmp->Draw("BOX");
//    hTmp->Print("all");

   Double_t *val, result;
   Int_t n;
   if (fAxisLoop == kX) {
      n = h->GetNbinsX();
      val = new Double_t[n];
      c = 0;
      next.Reset();
      while((se = (AliRsnSysErr *)next())) {
         h = se->GetHistogram(nameTmp);
         for (i=1; i<n+1; i++) {
            // set Array
            val[i-1] = h->GetBinContent(i);
         }

         // apply all actions
         fValue = fInitValue;
         for (Int_t iAct=0; iAct < fActions->GetSize(); iAct++) {
            result = Calculate((AliRsnSysErr::EActionType) TMath::Abs(fActions->At(iAct)), val, n);
            if (fActions->At(iAct)>=0) {
               fValue = result;
            }
            Printf("=== result[%d,%d]=%f fValue=%f", iAct, fActions->At(iAct), result, fValue);
         }
         c++;
      }
   } else if (fAxisLoop == kY) {
      n=fTasks->GetEntries();
      val = new Double_t[n];

      for (i=1; i<h->GetNbinsX()+1; i++) {
         c = 0;
         next.Reset();
         while((se = (AliRsnSysErr *)next())) {
            h = se->GetHistogram(nameTmp);
            // set Array
            val[c++] = h->GetBinContent(i);
         }
         // calculate
         for (Int_t j=0; j<n; j++)
            Printf("val[%d,%d]=%f",i,j, val[j]);

         fValue = fInitValue;
         for (Int_t iAct=0; iAct < fActions->GetSize(); iAct++) {
            result = Calculate((AliRsnSysErr::EActionType) TMath::Abs(fActions->At(iAct)), val, n);
            if (fActions->At(iAct)>=0) {
               fValue = result;
            }
            Printf("=== result[%d,%d]=%f fValue=%f", iAct, fActions->At(iAct), result, fValue);
         }
      }
   }

   delete [] val;

}

Double_t AliRsnSysErr::Calculate(AliRsnSysErr::EActionType actionType, Double_t *inputVal, Int_t n)
{
   switch (actionType) {
      case kMin:
         return AliRsnUtils::Min(inputVal, n);
         break;
      case kMax:
         return AliRsnUtils::Max(inputVal, n);
         break;
      case kAverage:
         return AliRsnUtils::Average(inputVal, n);
         break;
      case kMean:
         // TODO bin centers
         return AliRsnUtils::Mean(inputVal, n/*, binCenters*/);
         break;
      case kStdDev:
         return AliRsnUtils::StdDev(inputVal, n);
         break;
      case kMinDev:
         return AliRsnUtils::MinDev(inputVal, n, fValue);
         break;
      case kMaxDev:
         return AliRsnUtils::MaxDev(inputVal, n, fValue);
         break;
      default:
         break;
   }
   return 0.0;
}
