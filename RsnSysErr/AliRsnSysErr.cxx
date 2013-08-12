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
AliRsnSysErr::AliRsnSysErr(const char *name, const char *title) : TTask(name, title),
   fParent(0)
{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnSysErr::AliRsnSysErr(const AliRsnSysErr &copy) : TTask(copy),
   fParent(copy.fParent)
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

   fParent = copy.fParent;

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
   Printf("Exec: %s level=%d", GetName(), GetLevel());

}

void AliRsnSysErr::Add(TTask *task)
{
   TTask::Add(task);
   
   AliRsnSysErr *se = dynamic_cast<AliRsnSysErr *> (task);
   if (se) se->SetParent(this);
}


Int_t AliRsnSysErr::GetLevel() const
{
   if (!fParent) return 0;

   Int_t level=0;
   AliRsnSysErr *p = GetParent();
   while (p) {
      p = p->GetParent();
      level++;
   }
   return level;
}
