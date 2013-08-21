// Without this macro the THtml doc for TMath can not be generated
// #if !defined(R__ALPHA) && !defined(R__SOLARIS) && !defined(R__ACC) && !defined(R__FBSD)
// NamespaceImp(AliRsnUtils)
// #endif

#include <TError.h>
#include <TString.h>
#include <TMath.h>
#include <TH1.h>
#include <TGraphErrors.h>
#include "AliRsnUtils.h"

//______________________________________________________________________________
TH1D *AliRsnUtils::Graph2Hist(TGraphErrors *gr, Bool_t useGraphEY, Double_t min)
{
   //
   // Creating Histogram (TH1D) from TGraphErrors
   //

   // we return 0, if no grpah
   if ((!gr) || (!gr->GetN())) {
      ::Error("AliRsnUtils::Graph2Hist", "Graph 'gr' is null or has no points !!!");
      return 0;
   }

   // Finding range of graph
   Double_t xMin, xMax, yMin, yMax;
   gr->ComputeRange(xMin, yMin, xMax, yMax);

   // check if min is less then xMax of graph
   if (min > xMax) {
      ::Error("AliRsnUtils::Graph2Hist", "Value 'min' is higher then maximum of x axis of graph 'gr' !!!");
      return 0;
   }

   // clonig graph for internal useage
   gr = (TGraphErrors *) gr->Clone();

   // sorting graph, so x values are sorted correctly
   gr->Sort();

   // getting all values and errors from graph gr
   Double_t *x, *y, *ex, *ey;
   x = gr->GetX();
   y = gr->GetY();
   ex = gr->GetEX();
   ey = gr->GetEY();

   Bool_t isExNonZero = kTRUE;
   Int_t i;
   // check if ex is non-zero
   for (i = 0; i < gr->GetN() ; ++i) {
      if (ex[i] < 1e-15) {
         isExNonZero = kFALSE;
         break;
      }
   }

   // Creating array of bins for histogram
   Int_t nPoints = gr->GetN();
   Int_t nBins = nPoints + 1;
   Double_t bins[nBins];


   if (isExNonZero) {
      for (i = 0; i < nPoints ; ++i) {
         bins[i] = x[i] - ex[i];
      }
      bins[nPoints] = x[nPoints - 1] + ex[nPoints - 1];
   } else {
      ::Warning("AliRsnUtils::Graph2Hist", "One of value ErrorX (ex) of graph 'gr' is zero !!!");
      ::Warning("AliRsnUtils::Graph2Hist", TString::Format("We are going to guess histogram starting from min=%f !!!", min).Data());
      ::Warning("AliRsnUtils::Graph2Hist", "Check if histogram is as you expected !!!");

      Double_t d;
      // setting low-edge of first bin
      bins[0] = min;
      for (i = 0; i < gr->GetN() ; ++i) {
         d = x[i] - min;
         min = x[i] + d;
         bins[i + 1] = x[i] + d;
         // TODO : Add check for range and so
      }

   }

   TH1D *h = new TH1D(TString::Format("%s", gr->GetName()).Data(), "", nBins - 1, bins);

   // FILL values
   for (i = 1; i <= h->GetNbinsX(); ++i) {
      h->SetBinContent(i, y[i - 1]);
      if (useGraphEY) h->SetBinError(i, ey[i - 1]);

   }

   // cleanup
   delete gr;

   return h;
}

Double_t AliRsnUtils::Min(Double_t *val, Int_t n)
{
   Double_t min = (Double_t) kMaxLong64;
   for(Int_t i=0;i<n;i++) {
      min =  TMath::Min(val[i],min);
   }
   return min;
}

Double_t AliRsnUtils::Max(Double_t *val, Int_t n)
{
   Double_t max = (Double_t) -kMaxLong64;
   for(Int_t i=0;i<n;i++) {
      max =  TMath::Max(val[i],max);
   }
   return max;
}

Double_t AliRsnUtils::Average(Double_t * val, Int_t n)
{
   return AliRsnUtils::Mean(val, n);
}

Double_t AliRsnUtils::Mean(Double_t *val, Int_t n, Double_t *binCenters)
{
   Double_t sum = 0.0;
   for(Int_t i=0;i<n;i++) {
      if (binCenters) sum += val[i]*binCenters[i];
      else sum += val[i];
   }
   return sum/n;
}

Double_t AliRsnUtils::StdDev(Double_t *val, Int_t n, Double_t *binCenters)
{
   Double_t sum = 0.0;
   Double_t mean = AliRsnUtils::Mean(val, n, binCenters);
   for(Int_t i=0;i<n;i++) {
      sum += TMath::Power(val[i]-mean,2);
   }
   return TMath::Sqrt(sum)/(n-1);
}

Double_t AliRsnUtils::MinDev(Double_t *val, Int_t n, Double_t refVal)
{
   Double_t min = (Double_t) kMaxLong64;
   for(Int_t i=0;i<n;i++) {
      min =  TMath::Min(TMath::Abs(val[i]-refVal),min);
   }
   return min;
}

Double_t AliRsnUtils::MaxDev(Double_t *val, Int_t n, Double_t refVal)
{
   Double_t max = (Double_t) -kMaxLong64;
   for(Int_t i=0;i<n;i++) {
      max =  TMath::Max(TMath::Abs(val[i]-refVal),max);
   }
   return max;
}
