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

private:

   ClassDef(AliRsnSysErr, 1)
};

#endif
