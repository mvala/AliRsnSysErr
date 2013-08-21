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

#include <Rtypes.h>
#include <TArrayI.h>

#include "AliRsnTask.h"

class TH1D;
class AliRsnSysErr : public AliRsnTask
{
public:
   enum ELoopAxis { kX=0, kY, kNLoopAxis };
   enum EActionType {
      kNothing=0,
      kMin,
      kMax,
      kAverage,
      kMean,
      kStdDev,
      kMinDev,
      kMaxDev,
      kNActions };

   AliRsnSysErr(const char *name="rse", const char *title="");
   AliRsnSysErr(const AliRsnSysErr &copy);
   AliRsnSysErr &operator=(const AliRsnSysErr &copy);
   virtual ~AliRsnSysErr();

   void           Browse(TBrowser *b);
   virtual void   Exec(Option_t *option);
   void           Init();

   TH1D          *CreateHistogramFromGraph(const char *path, const char *tmpl="%lg %lg %lg %lg", const char *postfix="orig");
   void           AddHistogramToList(TH1D *h, const char *postfix="orig");
   TH1D          *GetHistogram(const char *postfix="orig");

   Bool_t         ImportDirectories(const char* postfix, const char* dir, const char* filename = "", const char* tmpl = "%lg %lg %lg %lg");

   void           SetAxisLoopType(ELoopAxis t) { fAxisLoop = t; }
   void           SetActions(TArrayI *actions) { fActions = actions; }
   Bool_t         SetLevelAction(Int_t level, TArrayI *actions, AliRsnSysErr::ELoopAxis axisLoop=kY, Double_t initVal=0.0);
   void           SetInitValue(Double_t val=0.0) { fInitValue = val; }

   TArrayI       *GetActions() { return fActions; }

   Double_t       Calculate(AliRsnSysErr::EActionType actionType, Double_t *inputVal, Int_t n, Double_t *extraVal=0);

private:

   TList         *fList;        // list of histograms
   ELoopAxis      fAxisLoop;    // type of axis loop
   TArrayI       *fActions;     // array of actions
   Double_t       fInitValue;   // init value value
   Double_t       fValue;       // current value

   ClassDef(AliRsnSysErr, 1)
};

#endif
