#ifndef ALIRSNUTILS_H
#define ALIRSNUTILS_H

#include <TH1.h>
#include <TGraphErrors.h>

namespace AliRsnUtils
{
   TH1D *Graph2Hist(TGraphErrors *gr, Bool_t useGraphEY = kFALSE, Double_t min = 0.0);
}

#endif
