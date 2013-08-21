// Authors: Jan Musinsky (jan.musinsky@cern.ch)
//          Martin Vala  (martin.vala@cern.ch)
// Date:    2013-08-12

#include <TCanvas.h>
#include <TROOT.h>
#include <TGClient.h>
#include <TObjArray.h>

#include "AliRsnSysErrViewer.h"

ClassImp(AliRsnSysErrViewer)

//______________________________________________________________________________
AliRsnSysErrViewer::AliRsnSysErrViewer()
   : TGraphRsnErrors()
{
   // Default constructor
}
//______________________________________________________________________________
AliRsnSysErrViewer::~AliRsnSysErrViewer()
{
   // Destructor
}
//______________________________________________________________________________
void AliRsnSysErrViewer::Flash(Option_t *option)
{
   TString opt = option;
   opt.ToLower();
   if      (opt.Contains("exam1")) Printf("%s", option);
   else if (opt.Contains("exam2")) Printf("%s", option);
   TVirtualPad *save = gPad;

   TCanvas *c = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c_flash");
   if (!GetShowFlash() && c) { // close canvas after disable SetShowFlash
      delete c;
      if (save) save->cd();
      return;
   }
   if (!c) {
      Int_t ww = 600;
      c = new TCanvas("c_flash", "", gClient->GetDisplayWidth() - ww, 0, ww, ww*1.20);
      c->Divide(1, 2);
   } else c->Clear("D"); // subpads are cleared but not deleted

   TObject *obj;
   c->cd(1);
   if (obj) obj->Draw();
   c->cd(2);
   if (obj) obj->Draw();
   c->Update();

   if (save) save->cd();
}

