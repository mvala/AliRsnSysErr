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

#include <TTask.h>

class AliRsnSysErr : public TTask {
public:
   AliRsnSysErr(const char *name="rse", const char*title="");
   AliRsnSysErr(const AliRsnSysErr &copy);
   AliRsnSysErr &operator=(const AliRsnSysErr &copy);
   virtual ~AliRsnSysErr();

   virtual void	Add(TTask* task);
   virtual void	Exec(Option_t* option);

   void SetParent(AliRsnSysErr *se) { fParent = se; }
   AliRsnSysErr *GetParent() const { return fParent; }

   Int_t GetLevel() const;

private:

   AliRsnSysErr *fParent;

   ClassDef(AliRsnSysErr, 1)
};

#endif
