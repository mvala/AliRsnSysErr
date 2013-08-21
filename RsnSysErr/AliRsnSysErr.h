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

#include <TList.h>
#include "AliRsnTask.h"

class TH1D;

class AliRsnSysErr : public AliRsnTask
{
public:
   enum EType { kValues=0, kOverBin, kOverMethods, kNTypes };
   enum EActionType { kMean=0, kMax, kMaxDev, kNActions };

   AliRsnSysErr(const char *name="rse", const char *title="");
   AliRsnSysErr(const AliRsnSysErr &copy);
   AliRsnSysErr &operator=(const AliRsnSysErr &copy);
   virtual ~AliRsnSysErr();

   void           Browse(TBrowser *b);
   virtual void   Exec(Option_t *option);

   TH1D          *CreateHistogramFromGraph(const char *path, const char *tmpl="%lg %lg %lg %lg", const char *postfix="orig");
   void           AddHistogramToList(TH1D *h, const char *postfix="orig");
   TH1D          *GetHistogram(const char *postfix="orig");

   Bool_t         ImportDirectories(const char *name, const char *dir,
                                    const char *filename="", const char *tmpl="%lg %lg %lg %lg");

   void           SetType(EType t) {
      fType = t;
   }
   void           SetActionType(EActionType t) {
      fActionType = t;
   }
   Bool_t         SetLevelAction(Int_t level, EType type, EActionType action);

private:

   TList          fList;        // list of histograms
   EType          fType;        // type of output
   EActionType    fActionType;  // type of action

   ClassDef(AliRsnSysErr, 1)
};

#endif
