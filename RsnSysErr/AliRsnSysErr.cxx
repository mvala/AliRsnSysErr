//
// *** Class AliRsnSysErr ***
//
// TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

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


TH1D *AliRsnSysErr::CreateHistoram(const char *path, const char *tmpl) {

   TGraphErrors *gr = new TGraphErrors(path, tmpl);
   if (!gr) return 0;

   TH1D *h = AliRsnUtils::Graph2Hist(gr, kFALSE, 0.0);

   delete gr;

   return h;
}

void AliRsnSysErr::SetHistoram(TH1D*h)  
{ 
   delete fHistogram; 
   fHistogram = h;
}

void AliRsnSysErr::Exec(Option_t *option)
{
   Printf("Executing: %s level=%d", GetName(), GetLevel());

}
