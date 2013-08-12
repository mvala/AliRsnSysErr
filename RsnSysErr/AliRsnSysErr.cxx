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
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : AliRsnTask(name, title)

{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : AliRsnTask(copy)
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


void AliRsnSysErr::Exec(Option_t *option)
{
   Printf("Executing: %s level=%d", GetName(), GetLevel());

}
