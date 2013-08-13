//
// *** Class AliRsnTask ***
//
// TODO
//
// authors: Martin Vala (martin.vala@cern.ch)
//          Jan Musinsky (jan.musinsky@cern.ch)
//

#include "AliRsnTask.h"

ClassImp(AliRsnTask)

//__________________________________________________________________________________________________
AliRsnTask::AliRsnTask(const char *name, const char *title) : TTask(name, title),
   fParent(0)
{
//
// Defauult constructor
//

}

//__________________________________________________________________________________________________
AliRsnTask::AliRsnTask(const AliRsnTask &copy) : TTask(copy),
   fParent(copy.fParent)
{
//
// Copy constructor
//

}

//__________________________________________________________________________________________________
AliRsnTask &AliRsnTask::operator=(const AliRsnTask &copy)
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

AliRsnTask::~AliRsnTask()
{
//
// Destructor
//

}


void AliRsnTask::Add(TTask *task)
{
   TTask::Add(task);
   
   AliRsnTask *se = dynamic_cast<AliRsnTask *> (task);
   if (se) se->SetParent(this);
}

void AliRsnTask::Print(Option_t* option) const
{
   
   // Creating spaces for prefix
   TString prefix;
   for (Int_t i=0;i<GetLevel();i++) prefix += "  ";
   
   // Printing info
   Printf("%sname='%s' title='%s' level=%d path=%s", prefix.Data(), GetName(), GetTitle(), GetLevel(), GetFullPath().Data());

   // Printing info of all subtasks
   TIter next(fTasks);
   AliRsnTask *se;
   while ((se = (AliRsnTask*) next())) {
      se->Print();
   }
}

Int_t AliRsnTask::GetLevel() const
{
   if (!fParent) return 0;

   Int_t level=0;
   AliRsnTask *p = GetParent();
   while (p) {
      p = p->GetParent();
      level++;
   }
   return level;
}

TString AliRsnTask::GetFullPath() const
{

   // Get current name
   TString fp = GetName();
   fp.Prepend("/");

   AliRsnTask *p = GetParent();
   while (p) {
      fp.Prepend(p->GetName());
      fp.Prepend("/");         
      p = p->GetParent();
   }
   
   return fp;
}


AliRsnTask *AliRsnTask::GetListByPath(TString path) const
{

   // let's remove first '/'
   TString name = GetName();
   path.Remove(0,name.Length()+path.First('/')+2);

   // let's remove lats '/' 
   if (path.Last('/') == path.Length())
      path.Remove(path.Length()-1,path.Length());

   // if path is null return current object
   if (path.IsNull()) return (AliRsnTask*)this; 
   
   // let's find out current name
   TString curName = path(0,path.First('/'));

   // if curName is null, then path is our name
   if (curName.IsNull()) {
      curName=path;
      return (AliRsnTask*) fTasks->FindObject(curName.Data());
   }

   // let's remove current name from path
   path.Remove(0,curName.Length());

   // let' see if we have task in fTasks
   AliRsnTask *t = (AliRsnTask*) fTasks->FindObject(curName.Data());

   // if not we return 0
   if (!t) return 0;

   // if yes, let's continue searching
   return t->GetListByPath(path);
}
