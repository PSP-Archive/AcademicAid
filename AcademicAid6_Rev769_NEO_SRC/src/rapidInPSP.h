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

#ifndef RAPIDINPSP_H_INCLUDED
#define RAPIDINPSP_H_INCLUDED

#include "includes.h"

extern int cancel;
extern Image* bg;
extern Image* number[14];
extern Image* Button_g;
extern Image* numhigh[14];
extern SceCtrlData positive, lastpositive, presses;
extern pgeFont *thefont17,*thefont15,*thefont19,*thefont29,*irregsigns;
extern Image* Misc[2];
extern Image* start;
extern Image* Oback;

double TakeInput(char varname[100]);

#endif // RAPIDINPSP_H_INCLUDED
