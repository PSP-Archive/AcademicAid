/*
    Academic Aid Scholastic Suite
    Copyright (C) 2007-2008  Vivek Javvaji (mr305) (First time GUI designer + Coder + Amateur P.S. Artist)
    Total build Revision: Refer to BuildInfo.txt

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMMONRESOURCES_H_INCLUDED
#define COMMONRESOURCES_H_INCLUDED

#include <pspdebug.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <psppower.h>
#include <malloc.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <time.h>
#include <psprtc.h>
#include <string.h>
#include "../common/graphics.h"
#include "../Common/pgeFont.h"
#include "../common/wavloader.h"
#include <math.h>
#include <pspmath.h>
#include <psputility.h>

#define RGBA(r,g,b,a) ((r) | ((g)<<8) | ((b)<<16) | ((a)<<24))
#define sync() sceDisplayWaitVblankStart()
#define FlushBadData() sceKernelDcacheWritebackAll()
#define PI 3.1415926535
#define pput pspDebugScreenPrintf
#define pset pspDebugScreenSetXY
#define minYpos 92
#define maxYpos 130
#define MAX_OPACITY 205
#define CLR_SHAD_ANS 0xFF787878//C4C4C9
#define CLR_ANS RGB(144,229,188) //(51,105,33,255)
#define CLR_ANS_PROMPT1 RGB(255,255,255)//RGB(238,203,173)//0xffadcbee
#define CLR_ANS_PROMPT RGB(255,255,255)//RGB(238,203,173)//0xffadcbee

#endif // COMMONRESOURCES_H_INCLUDED
