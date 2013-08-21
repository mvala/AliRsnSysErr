#ifndef ALIRSNSYSERRVIEWER_H
#define ALIRSNSYSERRVIEWER_H

#include "TGraphRsnErrors.h"

class AliRsnSysErrViewer : public TGraphRsnErrors
{

public:
   AliRsnSysErrViewer();
   AliRsnSysErrViewer(Int_t n);
   AliRsnSysErrViewer(Int_t n, const Float_t *x, const Float_t *y, const Float_t *ex = 0, const Float_t *ey = 0);
   AliRsnSysErrViewer(Int_t n, const Double_t *x, const Double_t *y, const Double_t *ex = 0, const Double_t *ey = 0);
   AliRsnSysErrViewer(const char *filename, const char *format = "%lg %lg %lg %lg", Option_t *option = "");
   virtual ~AliRsnSysErrViewer();

   virtual void  Flash(Option_t *option = "");

private:


   ClassDef(AliRsnSysErrViewer, 1) // AliRsnSysErrViewer class
};

#endif
