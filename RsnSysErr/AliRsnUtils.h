#ifndef ALIRSNUTILS_H
#define ALIRSNUTILS_H

#include <Rtypes.h>

class TGraphErrors;
class TH1D;
namespace AliRsnUtils
{
   TH1D *Graph2Hist(TGraphErrors *gr, Bool_t useGraphEY = kFALSE, Double_t min = 0.0);

   Double_t Min(Double_t *val, Int_t n);
   Double_t Max(Double_t *val, Int_t n);
   Double_t Average(Double_t *val, Int_t n);
   Double_t Mean(Double_t *val, Int_t n, Double_t *binCenters = 0);
   Double_t StdDev(Double_t *val, Int_t n, Double_t *binCenters = 0);
   Double_t MaxDev(Double_t *val, Int_t n, Double_t refVal = 0.0);
   Double_t MinDev(Double_t *val, Int_t n, Double_t refVal = 0.0);
}

#endif
