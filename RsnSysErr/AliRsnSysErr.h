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

   void           Browse(TBrowser *b);
   virtual void	Exec(Option_t* option);

   TH1D          *CreateHistogramFromGraph(const char *path, const char *tmpl="%lg %lg %lg %lg", const char *postfix="orig");
   void           AddHistogramToList(TH1D*h, const char *postfix="orig");
   TH1D          *GetHistogram(const char *postfix="orig");

   Bool_t         ImportDirectories(const char *dir, const char *filename="", const char *tmpl="%lg %lg %lg %lg");

private:

   TList *fList;

   ClassDef(AliRsnSysErr, 1)
};

#endif
