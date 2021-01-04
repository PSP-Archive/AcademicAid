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

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

int cancel=0;
Image* bg;
Image* invcalc;
Image* subcalc;
Image* subalg;
Image* subphyz;
Image* board;
Image* subtrig;
Image* number[14];
Image* numhigh[14];
Image* splashimg;
int creditsmsgshown=0;
Image* invalg;
Image* invphyz;
Image* invgeomtrig;
Image* bar;
Image* blob;
Image* Button_g;
Image* Selectorimg;

WAV* moveplace;
WAV* introsound;
WAV* click;
SceCtrlData positive, lastpositive, presses;
pgeFont *thefont17,*thefont15,*thefont19,*thefont29,*irregsigns;
u64 last_tick;
u32 tick_res;
u64 curr_tick;
float curr_ms = 1.0f;
double arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,answer,extrans;
char prompt[200]="";
char ansdisplay[100]="";
char ansdisplay1[100]="";
char ansdisplay2[100]="";
char ansdisplay3[100]="";
char ansdisplay4[100]="";
char ansdisplay5[100]="";
char ansdisplay6[100]="";
char ansdisplay7[100]="";
char tempstor[200]="";
int shady=0;
int texty=0;
int opacity=0;
int frame_count = 0;
int quit=0;
float beginy=65.0f;
const int algy=110;
const int phyzy=130;
const int geomtrigy=150;
const int calcy=170;
float left=0.0f;
float startval=1.0f;
int beginx = 20;
int tempvalx=0;
int dist =4;
float x=0.0f;
float boardx=164.0f;
float boardy=25.0f;
int wantoexit=0;
int menupos=0;
const int itemx = 70;
int menusel=0;
int shadmenusel=0;
int fade=0;
int linesizer=0;
char ellipsis[5]="";
int ellipsisc=0;
int donecopy=0;
float VarminY=0.0f;
float VarmaxY=0.0f;
int subjx=218;
int subjy=72;
int currxselx=0;

extern unsigned char Algebra_start[];
extern unsigned char Algebra_size[];
extern unsigned char AlgebraInvert_start[];
extern unsigned char AlgebraInvert_size[];
extern unsigned char Selector_start[];
extern unsigned char Selector_size[];
extern unsigned char Back_start[];
extern unsigned char Back_size[];
extern unsigned char BackPress_start[];
extern unsigned char BackPress_size[];
extern unsigned char Bar_start[];
extern unsigned char Bar_size[];
extern unsigned char BG_start[];
extern unsigned char BG_size[];
extern unsigned char Blob_start[];
extern unsigned char Blob_size[];
extern unsigned char Board_start[];
extern unsigned char Board_size[];
extern unsigned char D0_start[];
extern unsigned char D0_size[];
extern unsigned char D0High_start[];
extern unsigned char D0High_size[];
extern unsigned char D1_start[];
extern unsigned char D1_size[];
extern unsigned char D1High_start[];
extern unsigned char D1High_size[];
extern unsigned char D2_start[];
extern unsigned char D2_size[];
extern unsigned char D2High_start[];
extern unsigned char D2High_size[];
extern unsigned char D3_start[];
extern unsigned char D3_size[];
extern unsigned char D3High_start[];
extern unsigned char D3High_size[];
extern unsigned char D4_start[];
extern unsigned char D4_size[];
extern unsigned char D4High_start[];
extern unsigned char D4High_size[];
extern unsigned char D5_start[];
extern unsigned char D5_size[];
extern unsigned char D5High_start[];
extern unsigned char D5High_size[];
extern unsigned char D6_start[];
extern unsigned char D6_size[];
extern unsigned char D6High_start[];
extern unsigned char D6High_size[];
extern unsigned char D7_start[];
extern unsigned char D7_size[];
extern unsigned char D7High_start[];
extern unsigned char D7High_size[];
extern unsigned char D8_start[];
extern unsigned char D8_size[];
extern unsigned char D8High_start[];
extern unsigned char D8High_size[];
extern unsigned char D9_start[];
extern unsigned char D9_size[];
extern unsigned char D9High_start[];
extern unsigned char D9High_size[];
extern unsigned char Dot_start[];
extern unsigned char Dot_size[];
extern unsigned char DotHigh_start[];
extern unsigned char DotHigh_size[];
extern unsigned char Geomtrig_start[];
extern unsigned char Geomtrig_size[];
extern unsigned char GeomtrigInvert_start[];
extern unsigned char GeomtrigInvert_size[];
extern unsigned char Line_start[];
extern unsigned char Line_size[];
extern unsigned char Minus_start[];
extern unsigned char Minus_size[];
extern unsigned char MinusHigh_start[];
extern unsigned char MinusHigh_size[];
extern unsigned char Physics_start[];
extern unsigned char Physics_size[];
extern unsigned char PhysicsInvert_start[];
extern unsigned char PhysicsInvert_size[];
extern unsigned char Plane_start[];
extern unsigned char Plane_size[];
extern unsigned char Test_start[];
extern unsigned char Test_size[];
extern unsigned char Xstart_start[];
extern unsigned char Xstart_size[];
extern unsigned char Sselect_start[];
extern unsigned char Sselect_size[];
extern unsigned char Oquit_start[];
extern unsigned char Oquit_size[];
extern unsigned char Button_glow_start[];
extern unsigned char Button_glow_size[];
extern unsigned char memabcFont_start[];
extern unsigned char memabcFont_size[];
extern unsigned char credtext_start[];
extern unsigned char credtext_size[];
extern unsigned char Equals_start[];
extern unsigned char Equals_size[];
extern unsigned char EqualsHigh_start[];
extern unsigned char EqualsHigh_size[];
extern unsigned char Reset_start[];
extern unsigned char Reset_size[];
extern unsigned char ResetHigh_start[];
extern unsigned char ResetHigh_size[];
extern unsigned char Plus_start[];
extern unsigned char Plus_size[];
extern unsigned char PlusHigh_start[];
extern unsigned char PlusHigh_size[];
extern unsigned char Subtract_start[];
extern unsigned char Subtract_size[];
extern unsigned char SubtractHigh_start[];
extern unsigned char SubtractHigh_size[];
extern unsigned char Multiply_start[];
extern unsigned char Multiply_size[];
extern unsigned char MultiplyHigh_start[];
extern unsigned char MultiplyHigh_size[];
extern unsigned char Divide_start[];
extern unsigned char Divide_size[];
extern unsigned char DivideHigh_start[];
extern unsigned char DivideHigh_size[];
extern unsigned char Cancel_start[];
extern unsigned char Cancel_size[];
extern unsigned char CancelHigh_start[];
extern unsigned char CancelHigh_size[];
extern unsigned char sqrtHigh_start[];
extern unsigned char sqrtHigh_size[];
extern unsigned char sqrtimg_start[];
extern unsigned char sqrtimg_size[];
extern unsigned char cbrtHigh_start[];
extern unsigned char cbrtHigh_size[];
extern unsigned char cbrtimg_start[];
extern unsigned char cbrtimg_size[];
extern unsigned char calculator_start[];
extern unsigned char calculator_size[];
extern unsigned char calculatorinvert_start[];
extern unsigned char calculatorinvert_size[];
extern unsigned char Textbox_start[];
extern unsigned char Textbox_size[];
Image* Xsel;
Image* Oback;
Image* Oquit;
Image* Misc[2];
Image* start;
Image* Add;
Image* AddHigh;
Image* Subtract;
Image* SubtractHigh;
Image* Multiply;
Image* MultiplyHigh;
Image* Divide;
Image* DivideHigh;
Image* Reset;
Image* ResetHigh;
Image* Cancel;
Image* CancelHigh;
Image* Equals;
Image* EqualsHigh;
Image* Textbox;
Image* cbrtimg;
Image* cbrtHigh;
Image* sqrtimg;
Image* sqrtHigh;

float diagselaccel=3.0f;//1.2f;

int accelsub=29;
int flickerpreventer=1;
int colorhigh = 0xff2d4dc0; //0xff2a48b4;//0xff173ab4; //0xFF2A449E

#endif // MAIN_H_INCLUDED
