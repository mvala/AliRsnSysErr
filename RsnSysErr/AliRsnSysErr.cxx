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
#include <TH1.h>
#include <TGraphErrors.h>

#include "AliRsnUtils.h"
#include "AliRsnSysErr.h"

ClassImp(AliRsnSysErr)

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : AliRsnTask(name, title),
   fHistogram(0)

{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : AliRsnTask(copy),
   fHistogram(copy.fHistogram)
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

   fHistogram = copy.fHistogram;

   return (*this);
}

AliRsnSysErr::~AliRsnSysErr()
{
//
// Destructor
//

   SafeDelete(fHistogram);

}


TH1D *AliRsnSysErr::CreateHistogram(const char *path, const char *tmpl)
{
   // expanding path so we can use ~, $HOME, ...
   TString fullPath = gSystem->ExpandPathName(path);
   TGraphErrors *gr = new TGraphErrors(fullPath.Data(), tmpl);
   if (!gr) {
      ::Error("AliRsnSysErr::CreateHistogram", "Error opening graph from %s !!!",fullPath.Data());
      return 0;
   }

   TH1D *h = AliRsnUtils::Graph2Hist(gr, kFALSE, 0.0);

   // removing tmp graph
   SafeDelete(gr);

   // setting current histogram to fHistogram
   SetHistoram(h);

   return h;
}

void AliRsnSysErr::SetHistoram(TH1D *h)
{
   SafeDelete(fHistogram);
   fHistogram = h;
}

void AliRsnSysErr::Exec(Option_t *option)
{
   Printf("Executing: %s level=%d", GetName(), GetLevel());

}
