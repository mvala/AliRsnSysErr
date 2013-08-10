//
// *** Class AliRsnSysErr ***
//
// TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

#include "AliRsnSysErr.h"

ClassImp(AliRsnSysErr)

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : TTask(name, title)
{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : TTask(copy)
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

   return (*this);
}

AliRsnSysErr::~AliRsnSysErr()
{
//
// Destructor
//

}
