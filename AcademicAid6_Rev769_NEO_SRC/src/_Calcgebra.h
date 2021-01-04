#ifndef _CALCGEBRA_H_INCLUDED
#define _CALCGEBRA_H_INCLUDED

#include "main.h"

extern WAV* click;
extern SceCtrlData positive, lastpositive, presses;
extern int opacity;
extern pgeFont *thefont17,*thefont15,*thefont19,*thefont29,*irregsigns;
extern Image* bg;
extern char prompt[200];
extern char ansdisplay[100];
extern char ansdisplay1[100];
extern char ansdisplay2[100];
extern char ansdisplay3[100];
extern char ansdisplay4[100];
extern char ansdisplay5[100];
extern char ansdisplay6[100];
extern char ansdisplay7[100];
extern char tempstor[200];
extern Image* bar;
extern Image* blob;
extern double arg1,arg2,arg3,arg4,arg5,answer,extrans;
extern Image* invalg;
extern Image* Misc[2];
extern char ellipsis[5];
extern int ellipsisc;
extern int donecopy;
extern int fade;
extern float VarminY;
extern float VarmaxY;
extern int beginx;
extern int tempvalx;
extern int dist;
extern int cancel;
extern float startval;
extern Image* Xsel;
extern Image* Oback;
extern float left;


void ShowAlgebraList();
void DoAlgebra(int formulanum);

#endif // _CALCGEBRA_H_INCLUDED
