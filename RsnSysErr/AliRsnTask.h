//
// *** Class AliRsnTask ***
//
//  TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

#ifndef ALIRSNTASK_H
#define ALIRSNTASK_H

#include <TTask.h>

class TList;
class AliRsnTask : public TTask
{
public:
   AliRsnTask(const char *name="rsnTask", const char *title="Rsn Task");
   AliRsnTask(const AliRsnTask &copy);
   AliRsnTask &operator=(const AliRsnTask &copy);
   virtual ~AliRsnTask();

   virtual void   Add(TTask *task);
   virtual void   Add(AliRsnTask *se) { Add((TTask *)se); }
   virtual void   Print(Option_t *option = "") const;

   void           SetParent(AliRsnTask *se) { fParent = se; }
   AliRsnTask    *GetParent() const { return fParent; }
   Int_t          GetLevel() const;
   TString        GetFullPath(TString delim="/", Bool_t removeFirstChar = kFALSE) const;
   AliRsnTask    *GetListByPath(TString path="/") const;

private:

   AliRsnTask *fParent;

   ClassDef(AliRsnTask, 1)
};

#endif
