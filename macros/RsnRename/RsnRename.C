#ifndef __CINT__
#include <TString.h>
#include <TFile.h>
#include <TKey.h>
#include <TList.h>
#include <THnSparse.h>
#include <TSystem.h>
#endif
void RsnRename(TString fileIn="AnalysisResults.root", TString outBase = "/tmp/alice/rsn/LHC11a/RSN001/PhiKK/STD2010/NCLS70")
{

   Bool_t ignoreMixing=kFALSE;
//    ignoreMixing=kTRUE;
   const char *axisName[] = {"IM", "PT", "Y", "ETA" };

   TString sListName, fileFullPath;
   TFile *fOut;
   TList *lOutExtraInfo;

   TFile *f = TFile::Open(fileIn.Data(),"READ");
   if (!f) return;
   f->Print("all");
   TKey *key;
   TIter next(f->GetListOfKeys());
   TList *l;
   while ((key = (TKey *)next())) {
      key->Print();
      lOutExtraInfo = new TList();
      lOutExtraInfo->SetName("ExtraInfo");
      sListName = key->GetName();
      sListName.ReplaceAll("RsnHistMini_Phi_PhiNsigma:","");
      sListName.ReplaceAll("RsnHistMini_Phi_PhiNsigma_","");
      sListName.ReplaceAll("RsnHistMini_Phi_PDG:quality","PDG");

      if (sListName.Contains("STD2011")) outBase.ReplaceAll("STD2010","STD2011");

      sListName = sListName(0,sListName.First('_'));
      fileFullPath = TString::Format("%s/%s",outBase.Data(),sListName.Data());
      gSystem->mkdir(fileFullPath.Data(),kTRUE);
      fileFullPath+="/RsnOutput.root";
      fOut = TFile::Open(fileFullPath.Data() ,"RECREATE");
      l = (TList *)key->ReadObj();
      TIter nextList(l);
      TObject *obj;
      while((obj = (TObject *)nextList())) {
         TString sName = obj->GetName();
         if (obj->InheritsFrom("THnSparse")) {
            obj->Print();
            if (sName.Contains("Resphi")) sName.Append("_Resolution");
            if (sName.Contains("MCGenphi")) sName.Append("_Generated");
            if (ignoreMixing && sName.Contains("Mixing")) continue;
            sName = sName(sName.Last('_')+1,sName.Length());
            Printf("%s",sName.Data());
            THnSparse *clone = (THnSparse *) obj;
            clone->SetName(sName);
            for (Int_t i=0; i<clone->GetNdimensions(); i++) {
               TAxis *a = clone->GetAxis(i);
               a->SetName(axisName[i]);
            }
            clone->Write();
         } else {
            if (!sName.CompareTo("hEventStat")) obj->Write();
            else lOutExtraInfo->Add(obj);
         }
      }
      fOut->WriteObjectAny(lOutExtraInfo,"TList",lOutExtraInfo->GetName());
      lOutExtraInfo->Delete();
      delete lOutExtraInfo;
   }
   fOut->Close();
}
