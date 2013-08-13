//
// *** Class AliRsnSysErr ***
//
//  TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

#ifndef ALIRSNSYSERR_H
#define ALIRSNSYSERR_H

#include "AliRsnTask.h"
class TH1D;
class AliRsnSysErr : public AliRsnTask {
public:
   AliRsnSysErr(const char *name="rse", const char*title="");
   AliRsnSysErr(const AliRsnSysErr &copy);
   AliRsnSysErr &operator=(const AliRsnSysErr &copy);
   virtual ~AliRsnSysErr();

   virtual void	Exec(Option_t* option);

   TH1D          *CreateHistoram(const char *path, const char *tmpl);
   void           SetHistoram(TH1D*h);
   TH1D          *GetHistogram() const { return fHistogram; }

private:

   TH1D* fHistogram;

   ClassDef(AliRsnSysErr, 1)
};

#endif
