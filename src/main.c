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

#include "includes.h"
#include "main.h"
#include "rapidInPSP.h"
#include "misc.h"
#include <pspfpu.h>
// #include "_calcgebra.h"

// (ALL)Global vars in main.h

PSP_MODULE_INFO("Academic Aid Suite", 0, 6, 0);
PSP_MAIN_THREAD_ATTR(0|THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();
//PSP_STACK_SIZE_MAX();
pspUtilityMsgDialogParams dialog;

int VisuallyEnhance();
void sioInit(int baud);
int sioReadChar(void);

static int running = 1;
int mokitUNplugged;
int showmsgmokit;
int termcount;
int set;
int setupp;
int yvel;

int exit_callback(int arg1, int arg2, void *common) {
	sceKernelExitGame();
	running = 0;
	return 0;
}

int CallbackThread(SceSize args, void *argp) {
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}

int SetupCallbacks(void) {
	int thid = sceKernelCreateThread("CallbackThread", CallbackThread, 17, 4000, PSP_THREAD_ATTR_USER, 0);
	if (thid >= 0) sceKernelStartThread(thid, 0, 0);
	return thid;
}

inline void EndDrawing(){
   sceGuFinish();
    sceGuSync(0, 0);
    flipScreen();
}

inline void FinishAlg(){
    donecopy=0;
    ShowAlgebraList();
}

inline void FinishPhyz(){
    donecopy=0;
    ShowPhysicsList();
}

inline void FinishGeomtrig(){
    donecopy=0;
    ShowGeometrigList();
}

//The starting point
void MainMenu(){
    int opacty=0xff;
    int selLocked=0;
    int trans=0;
    int showcredits=0;
    int doaction=0;
    int down=1;
    int opaAccel=0;
    int subopaAccel=0;
    int subopacty=0xff;
    int invert=0;
    int selopa=0xff;
    yvel=0;
    termcount=0;
    showmsgmokit=0;
    set=0;
    setupp=0;
    if (mokitUNplugged!=1) mokitUNplugged=0;
    while (running)
    {
        guStart();
        clearScreen(0);
        sceGuColor(0xFFFFFFFF);
        sceCtrlPeekBufferPositive(&positive,1);
        presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
        lastpositive = positive;

        if (selopa<0xff && !invert && selLocked==0) selopa++;
        if (selopa==0xff && selLocked==0) invert=1;
        if (invert && selopa>75 && selLocked==0) selopa--;
        if (invert && selopa==75 && selLocked==0) invert=0;

        //if (!mokitUNplugged) { pset(0,1); pput("%d",yvel); }

        if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 165 && yvel < 255 &&  set==0 &&  (menupos!=3))
        {
             set=1;
              down=1;
            if (doaction ==0) doaction=1;
            opaAccel=0;
            subopaAccel=22;
            selopa=230;
            opacty=0;
            subopacty=0;
            menupos++;
            WAV_Play(click);
        }

         if (yvel < 110  && setupp==0 && (menupos!=0))
        {
             setupp=1;
             down=0;
            if (doaction ==0) doaction=1;
            opaAccel=0;
            subopaAccel=22;
            selopa=230;
            opacty=0;
            subopacty=0;
            menupos--;
            WAV_Play(click);
            sceKernelDelayThread(250000);
        }
        if (set && setupp==0 && yvel <= 130 && yvel >= 115)
                {
                    set=0;
                }

        if (setupp && yvel >= 110)
                {
                    setupp=0;
                }

        }

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }

//DEBUG GUI Design
//pset(0,0);
//pput("Sellckd: %d subopa: %d trans: %d",selLocked,subopaAccel,trans);
//if (positive.Buttons & PSP_CTRL_LTRIGGER)
//{
//        if (positive.Lx < 80) subjx-=1;
//        if (positive.Lx > 140) subjx+=1;
//        if (positive.Ly < 80) subjy-=1;
//        if (positive.Ly > 140) subjy+=1;
//}
//else
//{
//        if (positive.Lx < 80) boardx-=0.1f;
//        if (positive.Lx > 140) boardx+=0.1f;
//        if (positive.Ly < 80) boardy-=0.1f;
//        if (positive.Ly > 140) boardy+=0.1f;
//}

        if (selLocked !=1 && creditsmsgshown) //nothing chosen
        {
        if ((presses.Buttons & PSP_CTRL_DOWN) && (menupos!=3))
        {
            down=1;
            if (doaction ==0) doaction=1;
            opaAccel=0;
            subopaAccel=22;
            selopa=230;
            opacty=0;
            subopacty=0;
            menupos++;
            WAV_Play(click);
        }
        if ((presses.Buttons & PSP_CTRL_UP) && (menupos!=0))
        {
            down=0;
            if (doaction ==0) doaction=1;
            opaAccel=0;
            subopaAccel=22;
            selopa=230;
            opacty=0;
            subopacty=0;
            menupos--;
            WAV_Play(click);
        }
        }

        sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
        blit(bg,0.0f,0.0f);
        blit(board,boardx,boardy);
        if (selLocked) //something chosen
        {
//            if (invert<5) invert++;
//            if (trans < 0xff) trans+=invert;
//            //sceGuColor(RGBA(trans,0,0,0xff-trans));
            //if (trans>=0xff) { selLocked=2; }
            sceGuColor(0xFFFFFFFF);
            sceGuFinish();
            sceGuSync(0, 0);
            transition();
        }
        blit(Xsel,370.0f,235.0f);
        pgeFontActivate(thefont29);
        pgeFontPrint(thefont29,141,44/*41*/,"Academic Aid", 0xFF2176EE);//7DAACD); //Shadow
        pgeFontPrint(thefont29,140,43,"Academic Aid", 0xFF3EFF00);//0xFF55FF00);

        pgeFontActivate(thefont17);

        if (menupos!=0) pgeFontPrint(thefont17,itemx,algy,"Calculus", CLR_ANS_PROMPT1);
        if (menupos!=1) pgeFontPrint(thefont17,itemx,phyzy,"Physics",CLR_ANS_PROMPT1);
        if (menupos!=2) pgeFontPrint(thefont17,itemx,geomtrigy,"Trigonometry", CLR_ANS_PROMPT1);
        if (menupos!=3) pgeFontPrint(thefont17,itemx,calcy,"Calculator", CLR_ANS_PROMPT1);


        if (opacty<253) opacty+=opaAccel;
        if (subopacty<253) subopacty+=subopaAccel;
        if (subopaAccel>0) subopaAccel--;
        if (opaAccel<10/*22*/) opaAccel++;

        switch (menupos)
        {
        case 0:
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,itemx+1,algy+1,"Calculus", 0xFF7DAACD); //Shadow
            pgeFontPrintX(thefont17,itemx,algy,"Calculus", colorhigh,&currxselx);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            sceGuColor(RGBA(0xff,0xff,0xff,0xff-subopacty));
            blit(subphyz,(float)subjx,(float)subjy);
            sceGuColor(RGBA(0xff,0xff,0xff,opacty));
            blit(subalg,subjx,subjy); //45
            sceGuColor(RGBA(0xff,0xff,0xff,selopa));
            blit(Selectorimg,currxselx + 5,algy-13);
            sceGuColor(0xFFFFFFFF);

            diagselaccel=4.0f; //later used for animation

            break;
        case 1:
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,itemx+1,phyzy+1,"Physics", 0xFF7DAACD); //Shadow
            pgeFontPrintX(thefont17,itemx,phyzy, "Physics", colorhigh,&currxselx);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            sceGuColor(RGBA(0xff,0xff,0xff,0xff-subopacty));
            if (down) blit(subalg,subjx,subjy);
            else
            blit(subtrig,subjx,subjy);
            sceGuColor(RGBA(0xff,0xff,0xff,opacty));
            blit(subphyz,subjx,subjy);
            sceGuColor(RGBA(0xff,0xff,0xff,selopa));
            blit(Selectorimg,currxselx + 5,phyzy-13);
            sceGuColor(0xFFFFFFFF);

            diagselaccel=4.5f; //later used for animation

            break;
        case 2:
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,itemx+1,geomtrigy+1,"Trigonometry", 0xFF7DAACD); //Shadow
            pgeFontPrintX(thefont17,itemx,geomtrigy,"Trigonometry", colorhigh,&currxselx);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            sceGuColor(RGBA(0xff,0xff,0xff,0xff-subopacty));
            if (down) blit(subphyz,subjx,subjy);
            else
            blit(subcalc,subjx,subjy);
            sceGuColor(RGBA(0xff,0xff,0xff,opacty));
            blit(subtrig,subjx,subjy); //45
            sceGuColor(RGBA(0xff,0xff,0xff,selopa));
            blit(Selectorimg,currxselx + 5,geomtrigy-13);
            sceGuColor(0xFFFFFFFF);

            diagselaccel=4.9f; //later used for animation

            break;
       case 3:
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,itemx+1,calcy+1,"Calculator", 0xFF7DAACD); //Shadow
            pgeFontPrintX(thefont17,itemx,calcy,"Calculator", colorhigh,&currxselx);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            sceGuColor(RGBA(0xff,0xff,0xff,0xff-subopacty));
            blit(subtrig,subjx,subjy);
            sceGuColor(RGBA(0xff,0xff,0xff,opacty));
            blit(subcalc,subjx,subjy); //45
            sceGuColor(RGBA(0xff,0xff,0xff,selopa));
            blit(Selectorimg,currxselx + 5,calcy-13);
            sceGuColor(0xFFFFFFFF);

        diagselaccel=5.2f; //later used for animation

        break;
        default: break;
        }

        if (presses.Buttons & PSP_CTRL_CROSS)
        {
            WAV_Play(moveplace);
            selLocked=1;
            selopa=0xff;
        }

        if  (showcredits)
        {
        if (opacity < 0xff) opacity++;
        drawQuad(0,0,480,272,RGBA(0,0,0,opacity));
        if (opacity==0xff) credits();
        }

        if (presses.Buttons & PSP_CTRL_TRIANGLE)
        {
        fade=0;
        showcredits=1;
        }

        if (presses.Buttons & PSP_CTRL_CIRCLE && creditsmsgshown) sceKernelExitGame();

        if ((fade) && (opacity>=5))
        {
            drawQuad(0,0,480,272,RGBA(0,0,0,opacity));
            opacity-=5;
        }

        if (creditsmsgshown==0) {
        sceGuFinish();
        sceGuSync(0, 0);
        }
        else
        {
        EndDrawing();
        if (!selLocked && opacty!=0xff) sync();
        }

        if (creditsmsgshown==0){
        switch(sceUtilityMsgDialogGetStatus()) {

        case 2:
	    sceUtilityMsgDialogUpdate(2);
	    break;

        case 3:
	    sceUtilityMsgDialogShutdownStart();
	    creditsmsgshown=1;
	    break;

        case 0:
	    return;
        }

        sceDisplayWaitVblankStart();
        flipScreen();

        }

}
}

int main(){

    pspfpu_set_enable(0); //DISABLE FPU exceptions -- Very important

    pspDebugScreenInit();
    mokitUNplugged=0;

    //(SetupCallbacks() < 0) ? pput("%08X") : pset(0,0); --Sacrificed for sound and memory
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    initGraphics();
    WAV_Init();
    sceRtcGetCurrentTick(&last_tick);
    tick_res = sceRtcGetTickResolution();
    scePowerSetClockFrequency (333, 333, 166);
    menusel=itemx- 15;
    shadmenusel=menusel +1;

    pgeFontInit();
    thefont17 = pgeFontLoadMem(memabcFont_start,(int)memabcFont_size,  17, PGE_FONT_SIZE_PIXELS, 128);
    thefont15 = pgeFontLoadMem(memabcFont_start,(int)memabcFont_size, 15, PGE_FONT_SIZE_PIXELS, 128);
    thefont19 = pgeFontLoadMem(memabcFont_start, (int)memabcFont_size,21, PGE_FONT_SIZE_PIXELS, 128);
    thefont29 = pgeFontLoadMem(memabcFont_start, (int)memabcFont_size,26, PGE_FONT_SIZE_PIXELS, 256);
    irregsigns = pgeFontLoadMem(memabcFont_start, (int)memabcFont_size,12, PGE_FONT_SIZE_PIXELS, 128);
    click=WAV_Load("./Misc/menu.305");
    moveplace=WAV_Load("./Misc/move.305");
    FlushBadData();

        int modid =0; pspSdkLoadStartModule("sioDriver.prx", PSP_MEMORY_PARTITION_KERNEL);
        if (modid < 0){
       while(1)
       {
        pspDebugScreenSetXY(0,0);
        pspDebugScreenPrintf("Report this error to 305: 0x%08X\n", modid);
        }
        }
sioInit(510416);


    int splash=1;

     if (splash)
     {//Cool Intro
    introsound=WAV_Load("./Misc/intro.305");
    splashimg=loadImageMemory(Test_start,(int)Test_size);
    const int fx=480;
    const int fspeed=30;
    const int faccel=1;
    int speed=fspeed;
    int accel=faccel;
    x=fx;
    while (running)
    {
    guStart();
    clearScreen(0xFFFFFF);
     sceCtrlPeekBufferPositive(&positive,1);
     if (positive.Buttons & PSP_CTRL_LTRIGGER && positive.Buttons & PSP_CTRL_RTRIGGER && positive.Buttons & PSP_CTRL_TRIANGLE && positive.Buttons & PSP_CTRL_LEFT ) break; //for testing purposes
      if (x>0)
    {
    if (speed>accel) speed -=accel;
    if (x>=1) x -=speed;
    blit(splashimg,(float)x,0.0f);
    }
    if (x<=0)
    {
    fade=1;
    if (opacity==0)
        {
        sceKernelDelayThread(1000000);
        WAV_Play(introsound);
        sceKernelDelayThread(6000000);
        }
    if (opacity < 253) {
    if( splash<22) splash++;
    opacity +=splash;
    blit(splashimg,0.0f,0.0f);
    drawQuad(0,0,480,272,RGBA(0,0,0,opacity));
    }
    if (opacity>=253) {
        opacity=255;
    sceGuFinish();
    sceGuSync(0, 0);
    //opacity=0xff;
    break;
    }
    }
    EndDrawing();
    sync();
    FlushBadData();
    }
    freeImage(splashimg);
    WAV_Unload(introsound);
    FlushBadData();
    }//Intro


    board=loadImageMemory(Board_start,(int)Board_size);
    bg=loadImageMemory(BG_start,(int)BG_size);
    subalg=loadImageMemory(Algebra_start,(int)Algebra_size);
    subphyz=loadImageMemory(Physics_start,(int)Physics_size);
    subtrig=loadImageMemory(Geomtrig_start,(int)Geomtrig_size);
    number[0]=loadImageMemory(D0_start,(int)D0_size);
    number[1]=loadImageMemory(D1_start,(int)D1_size);
    number[2]=loadImageMemory(D2_start,(int)D2_size);
    number[3]=loadImageMemory(D3_start,(int)D3_size);
    number[4]=loadImageMemory(D4_start,(int)D4_size);
    number[5]=loadImageMemory(D5_start,(int)D5_size);
    number[6]=loadImageMemory(D6_start,(int)D6_size);
    number[7]=loadImageMemory(D7_start,(int)D7_size);
    number[8]=loadImageMemory(D8_start,(int)D8_size);
    number[9]=loadImageMemory(D9_start,(int)D9_size);
    number[11]=loadImageMemory(Minus_start,(int)Minus_size);
    number[12]=loadImageMemory(Dot_start,(int)Dot_size);
    Button_g = loadImageMemory(Button_glow_start,(int)Button_glow_size);

    numhigh[0]=loadImageMemory(D0High_start,(int)D0High_size);
    numhigh[1]=loadImageMemory(D1High_start,(int)D1High_size);
    numhigh[2]=loadImageMemory(D2High_start,(int)D2High_size);
    numhigh[3]=loadImageMemory(D3High_start,(int)D3High_size);
    numhigh[4]=loadImageMemory(D4High_start,(int)D4High_size);
    numhigh[5]=loadImageMemory(D5High_start,(int)D5High_size);
    numhigh[6]=loadImageMemory(D6High_start,(int)D6High_size);
    numhigh[7]=loadImageMemory(D7High_start,(int)D7High_size);
    numhigh[8]=loadImageMemory(D8High_start,(int)D8High_size);
    numhigh[9]=loadImageMemory(D9High_start,(int)D9High_size);
    numhigh[11]=loadImageMemory(MinusHigh_start,(int)MinusHigh_size);
    numhigh[12]=loadImageMemory(DotHigh_start,(int)DotHigh_size);

    Misc[0]= loadImageMemory(Line_start,(int)Line_size);
    Misc[1]= loadImageMemory(Plane_start,(int)Plane_size);
    invalg=loadImageMemory(AlgebraInvert_start,(int)AlgebraInvert_size);
    invphyz=loadImageMemory(PhysicsInvert_start,(int)PhysicsInvert_size);
    invgeomtrig=loadImageMemory(GeomtrigInvert_start,(int)GeomtrigInvert_size);
    bar= loadImageMemory(Bar_start,(int)Bar_size);
    blob= loadImageMemory(Blob_start,(int)Blob_size);
    Xsel = loadImageMemory(Sselect_start,(int)Sselect_size);
    Oback = loadImageMemory(Back_start,(int)Back_size);
    Oquit=loadImageMemory(Oquit_start,(int)Oquit_size);
    start = loadImageMemory(Xstart_start,(int)Xstart_size);

    Add = loadImageMemory(Plus_start,(int)Plus_size);
    AddHigh = loadImageMemory(PlusHigh_start,(int)PlusHigh_size);
    Subtract = loadImageMemory(Subtract_start,(int)Subtract_size);
    SubtractHigh = loadImageMemory(SubtractHigh_start,(int)SubtractHigh_size);
    Multiply = loadImageMemory(Multiply_start,(int)Multiply_size);
    MultiplyHigh = loadImageMemory(MultiplyHigh_start,(int)MultiplyHigh_size);
    Divide = loadImageMemory(Divide_start,(int)Divide_size);
    DivideHigh = loadImageMemory(DivideHigh_start,(int)DivideHigh_size);
    Equals = loadImageMemory(Equals_start,(int)Equals_size);
    EqualsHigh = loadImageMemory(EqualsHigh_start,(int)EqualsHigh_size);
    Reset = loadImageMemory(Reset_start,(int)Reset_size);
    ResetHigh = loadImageMemory(ResetHigh_start,(int)ResetHigh_size);
    Cancel = loadImageMemory(Cancel_start,(int)Cancel_size);
    CancelHigh = loadImageMemory(CancelHigh_start,(int)CancelHigh_size);

    sqrtimg = loadImageMemory(sqrtimg_start,(int)sqrtimg_size);
    sqrtHigh = loadImageMemory(sqrtHigh_start,(int)sqrtHigh_size);
    cbrtimg = loadImageMemory(cbrtimg_start,(int)cbrtimg_size);
    cbrtHigh= loadImageMemory(cbrtHigh_start,(int)cbrtHigh_size);

    subcalc= loadImageMemory(calculator_start,(int)calculator_size);
    invcalc= loadImageMemory(calculatorinvert_start,(int)calculatorinvert_size);

    Textbox = loadImageMemory(Textbox_start,(int)Textbox_size);
    Selectorimg = loadImageMemory(Selector_start,Selector_size);

    ConfigureDialog(&dialog, sizeof(dialog));
    //dialog.unknown[1] = 1; OLD PSPSDK
    dialog.mode=PSP_UTILITY_MSGDIALOG_MODE_TEXT;
    strcpy(dialog.message, "Press Triangle for Credits \
                            Press Circle to Exit");

    sceUtilityMsgDialogInitStart(&dialog);
    MainMenu();
    return 1;
}

void ShowAlgebraList(){
    float beginy=68.0f;
    int dist=2;
    int item1y=beginy + 25;
    int item2y=beginy + 45+dist;
    int item3y=beginy + 65+dist*2;
    int item4y=beginy + 85+dist*3;
    int item5y=beginy + 105+dist*4;
    int item6y=beginy + 125+dist*5;
    int item7y=beginy + 145+dist*6;
    int item8y=beginy + 165+dist*7;
    accelsub=28;

    const int totalitems = 7;
      static int pos=0;
    #define beginxx 20
    #define beginxshad 21
    flickerpreventer=1;
    linesizer=0;

     while (running)
    {
        {
             //GENERIC initialization
            if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
            //FlushBadData();
            if (presses.Buttons & PSP_CTRL_CIRCLE) MainMenu();
                if (flickerpreventer!=1)
                {
                guStart();
                clearScreen(0);
                }
                flickerpreventer=0;
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                RenderImage(bg,0,73,480,272,0,72,480,200,0);
                sceGuColor(RGBA(0xff,0xff,0xff,70));
                blit( invalg ,235,125);
                sceGuColor(0xFFFFFFFF);
                pgeFontActivate(thefont17);
            //}
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;
        } //BLOCK close

               if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 165 && set==0 && pos<totalitems)
        {
             set=1;
            pos+=1;
            WAV_Play(click);
        }

         if (yvel < 110  && setupp==0 && pos>0)
        {
             setupp=1;
            pos-=1;
            WAV_Play(click);
            sceKernelDelayThread(250000);
        }
        if (set && setupp==0 && yvel <= 130 && yvel >= 115)
                {
                    set=0;
                }

        if (setupp && yvel >= 110)
                {
                    setupp=0;
                }

        }

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }

        if (presses.Buttons & PSP_CTRL_DOWN && pos<totalitems)
        {
            pos+=1;
            WAV_Play(click);
        }
        if  (presses.Buttons & PSP_CTRL_UP && pos>0)
        {
            pos-=1;
            WAV_Play(click);
        }

       pgeFontPrint(thefont17,beginxshad,item1y+1,"Solve solution and statistics of a Quadratic equation",CLR_ANS_PROMPT);
        if (pos==0) pgeFontPrint(thefont17,beginxx,item1y,"Solve solution and statistics of a Quadratic equation",colorhigh);

       pgeFontPrint(thefont17,beginxshad,item2y+1,"Calculate extended Arithmetic sequences and sum",CLR_ANS_PROMPT);
        if (pos==1)pgeFontPrint(thefont17,beginxx,item2y,"Calculate extended Arithmetic sequences and sum",colorhigh);


       pgeFontPrint(thefont17,beginxshad,item3y+1,"Calculate extended Geometric sequences and sum",CLR_ANS_PROMPT);
        if (pos==2)pgeFontPrint(thefont17,beginxx,item3y,"Calculate extended Geometric sequences and sum",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item4y+1,"Solve the Geometry of two points and the Graph",  CLR_ANS_PROMPT);
        if (pos==3)pgeFontPrint(thefont17,beginxx,item4y,"Solve the Geometry of two points and the Graph", colorhigh); //

        pgeFontPrint(thefont17,beginxshad,item5y+1,"Find the Determinant of 2x2 Matrix",CLR_ANS_PROMPT);
       if (pos==4)pgeFontPrint(thefont17,beginxx,item5y,"Find the Determinant of 2x2 Matrix",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item6y+1,"Find the Determinant of 3x3 Matrix",CLR_ANS_PROMPT);
       if (pos==5)pgeFontPrint(thefont17,beginxx,item6y,"Find the Determinant of 3x3 Matrix",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item7y+1,"Find 2nd, 3rd or Nth Root of a number",CLR_ANS_PROMPT);
       if (pos==6)pgeFontPrint(thefont17,beginxx,item7y,"Find 2nd, 3rd or Nth Root of a number",colorhigh);

       pgeFontPrint(thefont17,beginxshad,item8y+1,"Solve a Logarithmic equation function",CLR_ANS_PROMPT);
       if (pos==7)pgeFontPrint(thefont17,beginxx,item8y,"Solve a Logarithmic equation function",colorhigh);

       sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);

       blitcrop(bg,0,0,480,72);
       linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
       blit(bar,455,80);
       blit(blob,450,92);

        if (linesizer <= 253) { sceGuColor(RGBA(255,255,255,abs(-253+linesizer)));
        blitAlphaImageToScreen(0,item1y-10,480,272,bg,0,item1y-10);
        sceGuColor(0xffffffff); }

       pgeFontActivate(thefont17);
       pgeFontPrint(thefont17,11,66,"Select an item from the list below:",0xFF2b5a8b);//CLR_SHAD_ANS);
       pgeFontPrint(thefont17,10,65,"Select an item from the list below:",0xffadcbee);//0xFF7DAACD);
       pgeFontActivate(thefont29);
       pgeFontPrint(thefont29,168,41,"Calculus",0xFF2176EE); //Shadow
       pgeFontPrint(thefont29,167,40,"Calculus", 0xFF3EFF00);



        EndDrawing();
        sync();
        if (presses.Buttons & PSP_CTRL_CROSS) { WAV_Play(moveplace); DoAlgebra(pos); }

}
}

void ShowPhysicsList(){
    float beginy=68.0f;
    int dist=2;
    int item1y=beginy + 25;
    int item2y=beginy + 45+dist;
    int item3y=beginy + 65+dist*2;
    int item4y=beginy + 85+dist*3;
    int item5y=beginy + 105+dist*4;
    int item6y=beginy + 125+dist*5;
    const int totalitems = 5;
    #define beginxx 20
    #define beginxshad 21
    static int pos=0;
    flickerpreventer=1;
    linesizer=0;
    accelsub=28;
    while (running)
    {
        { //GENERIC initialization
             if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
            //FlushBadData();
            if (presses.Buttons & PSP_CTRL_CIRCLE) MainMenu();
            if (flickerpreventer!=1)
            {
            if (opacity != MAX_OPACITY) //Stuck fixer
            {
                guStart();
                clearScreen(0);
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                RenderImage(bg,0,73,480,272,0,72,480,200,0);
                sceGuColor(RGBA(0xff,0xff,0xff,70));
                blit( invphyz ,235.0f,125.0f);
            sceGuColor(0xFFFFFFFF);

                pgeFontActivate(thefont17);
            }
            }
            flickerpreventer=0;
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;
        } //BLOCK close

                   if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 165 && set==0 && pos<totalitems)
        {
             set=1;
            pos+=1;
            WAV_Play(click);
        }

         if (yvel < 110  && setupp==0 && pos>0)
        {
             setupp=1;
            pos-=1;
            WAV_Play(click);
            sceKernelDelayThread(250000);
        }
        if (set && setupp==0 && yvel <= 130 && yvel >= 115)
                {
                    set=0;
                }

        if (setupp && yvel >= 110)
                {
                    setupp=0;
                }

        }

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }

        if (presses.Buttons & PSP_CTRL_DOWN && pos<totalitems)
        {
            pos+=1;
            WAV_Play(click);
        }
        if  (presses.Buttons & PSP_CTRL_UP && pos>0)
        {
            pos-=1;
            WAV_Play(click);
        }

//G=6.67x10-11 N.m2/kg2

        pgeFontPrint(thefont17,beginxshad,item1y+1,"Newtons Law of Universal Gravity between two objects",CLR_ANS_PROMPT);
        if (pos==0) pgeFontPrint(thefont17,beginxx,item1y,"Newtons Law of Universal Gravity between two objects",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item2y+1,"Find Average Acceleration from Velocity and Time",CLR_ANS_PROMPT);
        if (pos==1) pgeFontPrint(thefont17,beginxx,item2y,"Find Average Acceleration from Velocity and Time",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item3y+1,"Final Dist from Init Dist, Time, Velocity & Acceleration",CLR_ANS_PROMPT);
        if (pos==2) pgeFontPrint(thefont17,beginxx,item3y,"Final Dist from Init Dist, Time, Velocity & Acceleration",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item4y+1,"Final Velocity from Init. Velocity, Dist & Acceleration",CLR_ANS_PROMPT);
        if (pos==3) pgeFontPrint(thefont17,beginxx,item4y,"Final Velocity from Init. Velocity, Dist & Acceleration",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item5y+1,"Max Dist of Projectile going up or down [w/time]",CLR_ANS_PROMPT);
        if (pos==4) pgeFontPrint(thefont17,beginxx,item5y,"Max Dist of Projectile going up or down [w/time]",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item6y+1,"Max Height/Range/time/stats of a Projectile [Angle]",CLR_ANS_PROMPT);
        if (pos==5) pgeFontPrint(thefont17,beginxx,item6y,"Max Height/Range/time/stats of a Projectile [Angle]",colorhigh);

        // H = (((Initvel * (sin Tita))*(Initvel * (sin Tita)))/19.6)
        // d = ((Intvel*Intvel) * sin( 2 * Tita))/9.8

          if (flickerpreventer!=1)
            {
       sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
       blitcrop(bg,0.0f,0.0f,480.0f,72.0f);
    linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
        blit(bar,455.0f,80.0f);
       blit(blob,450.0f,92.0f);
        if (linesizer <= 253) { sceGuColor(RGBA(255,255,255,abs(-253+linesizer)));
        blitAlphaImageToScreen(0,item1y-10,480,272,bg,0,item1y-10);
        sceGuColor(0xffffffff); }

            }


       pgeFontActivate(thefont17);
       pgeFontPrint(thefont17,11,66,"Select an item from the list below:",0xFF2b5a8b);//CLR_SHAD_ANS);
       pgeFontPrint(thefont17,10,65,"Select an item from the list below:",0xffadcbee);//0xFF7DAACD);
       pgeFontActivate(thefont29);
       pgeFontPrint(thefont29,185,41,"Physics", 0xFF2176EE); //Shadow
       pgeFontPrint(thefont29,184,40,"Physics", 0xFF3EFF00);

        EndDrawing();
        sync();
        if (presses.Buttons & PSP_CTRL_CROSS) { WAV_Play(moveplace); DoPhysics(pos); }

        }
}

void ShowGeometrigList(){
    float beginy=68.0f;
    int dist=2;
    int item1y=beginy + 25;
    int item2y=beginy + 45+dist;
    int item3y=beginy + 65+dist*2;
    int item4y=beginy + 85+dist*3;
    int item5y=beginy + 105+dist*4;
    int item6y=beginy + 125+dist*5;
    int item7y=beginy + 145+dist*6;
    int item8y=beginy + 165+dist*7;

    const int totalitems = 7;
    #define beginxx 20
    #define beginxshad 21
    static int pos=0;
    linesizer=0;
    accelsub=28;
    flickerpreventer=1;

     while (running)
    {

        { //GENERIC initialization
             if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
           //FlushBadData();
            if (presses.Buttons & PSP_CTRL_CIRCLE) MainMenu();
                if (flickerpreventer!=1)
                {
                guStart();
                clearScreen(0);
                }
                flickerpreventer=0;
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                RenderImage(bg,0,73,480,272,0,72,480,200,0);
                sceGuColor(RGBA(0xff,0xff,0xff,70));
                blit( invgeomtrig ,235.0f,125.0f);
                sceGuColor(0xFFFFFFFF);

                pgeFontActivate(thefont17);
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;
        } //BLOCK close

                   if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 165 && set==0 && pos<totalitems)
        {
             set=1;
            pos+=1;
            WAV_Play(click);
        }

         if (yvel < 110  && setupp==0 && pos>0)
        {
             setupp=1;
            pos-=1;
            WAV_Play(click);
            sceKernelDelayThread(250000);
        }
        if (set && setupp==0 && yvel <= 130 && yvel >= 115)
                {
                    set=0;
                }

        if (setupp && yvel >= 110)
                {
                    setupp=0;
                }

        }

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }


        if (presses.Buttons & PSP_CTRL_DOWN && pos<totalitems)
        {
            pos+=1;
            WAV_Play(click);
        }
        if ( presses.Buttons & PSP_CTRL_UP && pos>0)
        {
            pos-=1;
            WAV_Play(click);
        }

        pgeFontPrint(thefont17,beginxshad,item1y+1,"Lateral, Total Surface Area & Volume of a Cylinder",CLR_ANS_PROMPT);
        if (pos==0) pgeFontPrint(thefont17,beginxx,item1y,"Lateral, Total Surface Area & Volume of a Cylinder",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item2y+1,"Lateral, Total Surface Area & Volume of a Cuboid",CLR_ANS_PROMPT);
        if (pos==1) pgeFontPrint(thefont17,beginxx,item2y,"Lateral, Total Surface Area & Volume of a Cuboid",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item3y+1,"(Lateral) Surface Area & Volume of a (Hemi)Sphere",CLR_ANS_PROMPT);
        if (pos==2) pgeFontPrint(thefont17,beginxx,item3y,"(Lateral) Surface Area & Volume of a (Hemi)Sphere",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item4y+1,"Lateral, Total Surface Area & Volume of a Pyramid",CLR_ANS_PROMPT);
        if (pos==3) pgeFontPrint(thefont17,beginxx,item4y,"Lateral, Total Surface Area & Volume of a Pyramid",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item5y+1,"Area of a Triangle by using the lengths of 3 sides only",CLR_ANS_PROMPT);
        if (pos==4) pgeFontPrint(thefont17,beginxx,item5y,"Area of a Triangle by using the lengths of 3 sides only",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item6y+1,"Find the area of an equilateral triangle by using a side",CLR_ANS_PROMPT);
        if (pos==5) pgeFontPrint(thefont17,beginxx,item6y,"Find the area of an equilateral triangle by using a side",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item7y+1,"Convert an angle measured in Radians to Degrees",CLR_ANS_PROMPT);
        if (pos==6) pgeFontPrint(thefont17,beginxx,item7y,"Convert an angle measured in Radians to Degrees",colorhigh);

        pgeFontPrint(thefont17,beginxshad,item8y+1,"Convert an angle measured in Degrees to Radians",CLR_ANS_PROMPT);
        if (pos==7) pgeFontPrint(thefont17,beginxx,item8y,"Convert an angle measured in Degrees to Radians",colorhigh);

       sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);

       blitcrop(bg,0.0f,0.0f,480.0f,72.0f);
      linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
      blit(bar,455.0f,80.0f);
       blit(blob,450.0f,92.0f);
       if (linesizer <= 253) { sceGuColor(RGBA(255,255,255,abs(-253+linesizer)));
        blitAlphaImageToScreen(0,item1y-10,480,272,bg,0,item1y-10);
        sceGuColor(0xffffffff); }


       pgeFontActivate(thefont17);
       pgeFontPrint(thefont17,11,66,"Select an item from the list below:",0xFF2b5a8b);//CLR_SHAD_ANS);
       pgeFontPrint(thefont17,10,65,"Select an item from the list below:",0xffadcbee);//0xFF7DAACD);
       pgeFontActivate(thefont29);
       pgeFontPrint(thefont29,160,41,"Trigonometry", 0xFF2176EE); //Shadow
       pgeFontPrint(thefont29,159,40,"Trigonometry", 0xFF3EFF00);

        sync();
        EndDrawing();
        if (presses.Buttons & PSP_CTRL_CROSS) { WAV_Play(moveplace); DoGeomtrig(pos); }

        }
}

void DoPhysics(int formulanum){
    float beginy=68.0f;
    int currarg=0;
    ellipsisc =0;
    double time=0;
    double velocity=0;
    double finalvel=0;
    double extra=0.0;
    int disableit=0;
    linesizer=0;
    accelsub=28;
    while (running)
    {
    { //Init
         if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;

            //FlushBadData();
            guStart();
            clearScreen(0xffffffff);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            RenderImage(bg,0,73,480,272,0,72,480,200,0);
            sceGuColor(RGBA(0xff,0xff,0xff,70));
            blit( invphyz ,235,125);

            pgeFontActivate(thefont17);
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;

            ellipsisc++;
          if (ellipsisc ==10)
                strcpy( ellipsis,"");
            else if (ellipsisc ==20)
                strcpy( ellipsis,".");
            else if (ellipsisc ==30)
                strcpy( ellipsis,"..");
            else if (ellipsisc ==40){
                strcpy( ellipsis,"...");
                ellipsisc=0;
            }
        }
    if (formulanum==0)
    { // Newtons Law of Universal Gravity between two objects
            if (donecopy==0)
            {
                strcpy(prompt,"Newtons Law of Universal Gravity between two objects");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Mass of 1st object: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Mass of 2nd object: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Radius/Distance between objects: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 3:

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The force between the objs is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:
                    arg1=TakeInput("Mass1");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:
                    arg2=TakeInput("Mass2");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 3:
                    arg3=TakeInput("Distance/Radius");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=6.67 * (pow(10,-11))*((arg1*arg2)/(arg3*arg3));
                        sprintf(ansdisplay,"%g Newtons",answer);
                    }
                    break;

                case 4:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula
    if (formulanum==1)
    { // Average Acceleration from velocity and time
            if (donecopy==0)
            {
                strcpy(prompt,"Average Acceleration from velocity and time");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Final Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                pgeFontPrintX(thefont17,beginx,beginy + 45,"Tip: To find Avg. Velocity enter distance",CLR_ANS_PROMPT,&tempvalx);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Init. Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontPrintX(thefont17,beginx,beginy + 65,"Tip: Enter '0' if only one velocity/dist is given",CLR_ANS_PROMPT,&tempvalx);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Time: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"Average Velocity/Accel is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:
                    arg1=TakeInput("Final Dist.");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:
                    arg2=TakeInput("Initial Dist.");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 3:
                    arg3=TakeInput("Time");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=((arg1-arg2)/(arg3));
                        sprintf(ansdisplay,"%g m/s or m/s.s",answer);
                    }
                    break;

                case 4:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula
    if (formulanum==2)
    { //"Final Dist from Init. Dist, time , velocity and (acceleration)"

            if (donecopy==0)
            {
                strcpy(prompt,"Final Distance from Initial Distance, time & Velocity");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Distance",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the time: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Final Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontPrintX(thefont17,beginx,beginy + 45,"Tip: Enter '0' if only one velocity is given",CLR_ANS_PROMPT,&tempvalx);
                break;

            case 4:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Acceleration: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 5:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Final Distance is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:
                    arg1=TakeInput("Initial Dist");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:
                    arg2=TakeInput("Time");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 3:
                    arg3=TakeInput("Final Velocity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 4:
                    arg4=TakeInput("Initial Velocity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 5:
                    arg5=TakeInput("Acceleration");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=(arg1+(arg3-arg4)*arg2)+(0.5*arg5*arg2*arg2);
                        sprintf(ansdisplay,"%g m",answer);
                    }
                    break;

                case 6:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula
    if (formulanum==3)
    { //Final Velocity from Init. Velocity, Distance & acceleration
            if (donecopy==0)
            {
                strcpy(prompt,"Final Velocity from Init. Velocity, Distance & acceleration");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Distance: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Acceleration: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Final Velocity is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Initial Velocity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("Distance");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 3:

                    arg3=TakeInput("Acceleration");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=sqrt(arg1*arg1+(2*arg3*arg2));
                        sprintf(ansdisplay,"%g m/s",answer);
                    }
                    break;

                case 4:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula
    if (formulanum==4)
    { //Distance of projectile thrown straight up/down.
            if (donecopy==0)
            {
                strcpy(prompt,"The maximum height of a projectile thrown up or down");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Height: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Time: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Override the Accel. due to gravity? [Right to skip] ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontPrint(thefont17,beginx,beginy + 45,"Default: Thrown up",CLR_ANS_PROMPT);
                pgeFontPrint(thefont17,beginx,beginy + 65,"Enter 9.8 for free falling object",CLR_ANS_PROMPT);
                if (presses.Buttons & PSP_CTRL_RIGHT)
                {
                    arg4=-9.8;
                    currarg++;
                    answer=(((0.5*arg4)*(arg3*arg3))+(arg1*arg3)+arg2);
                    sprintf(ansdisplay,"%g m/s",answer);
                }
                break;

            case 4:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The maximum Displacement/height is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Initial Velocity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("Initial Height");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 3:

                    arg3=TakeInput("Time");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;


                case 4:

                    arg4=TakeInput("Accel due to gravity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=fabs(((0.5*arg4)*(arg3*arg3))+(arg1*arg3)+arg2);
                        sprintf(ansdisplay,"%g m",answer);
                    }
                    break;

                case 5:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula
    if (formulanum==5)
    { //Max Height/X-Range of a Projectile [w/ Angle]

            if (donecopy==0)
            {
                strcpy(prompt,"Max Height/X-Range of a Projectile thrown @ an angle");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial Velocity: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Initial height from ground: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Angle to the ground: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The max. height is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The maximum X-Distance/range is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"X-Velocity is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay2,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 85+dist*4,"Y-Velocity [Bef. peak height]: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay3,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 85+dist*4,ansdisplay3,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 105+dist*5,"Final Y-Velocity [Bef. hitting ground]: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 106+dist*5,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 105+dist*5,ansdisplay6,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 125+dist*6,"Final Vector is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 126+dist*6,ansdisplay4,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 125+dist*6,ansdisplay4,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 145+dist*7,"Time to reach peak height: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 146+dist*7,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 145+dist*7,ansdisplay5,CLR_ANS); //0xFFCE8149

                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Initial Velocity");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 2:

                    arg2=TakeInput("Initial Height");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 3:
                    arg3=TakeInput("Angle");
                    if (cancel)
                    {
                         currarg -=1;
                        cancel=0;
                    }
                    else
                    {

                        answer=((pow(arg1 * sin(arg3 * PI/180),2))/19.6)+arg2;
                        sprintf(ansdisplay,"%g m",answer);
                        answer=( arg1*arg1 * sin( (2 * arg3) * PI/180))/9.8;
                        sprintf(ansdisplay1,"%g m",answer);
                        answer= arg1* cos(arg3 * PI/180);
                        sprintf(ansdisplay2,"%g m/s",answer);

                        answer=velocity=arg1* sin(arg3 * PI/180);
                        sprintf(ansdisplay3,"%g m/s",answer); //Y velocity

                        time = answer = fabs((arg1* sin(arg3 * PI/180))/-9.8);
                        sprintf(ansdisplay5,"%g secs",answer);

                        finalvel=answer = -9.8 * time;
                        sprintf(ansdisplay6,"%g",answer);

                        answer = sqrt(  pow(arg1* cos(arg3 * PI/180),2) +  pow( arg1* sin(arg3 * PI/180),2) );
                        extra = (atan(velocity/(arg1* cos(arg3 * PI/180)) )) * 180/PI;
                        sprintf(ansdisplay4,"%g m/s @ %g Degrees",answer,extra);

                    }
                    break;

                case 4:
                    FinishPhyz();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula


        { //Term
           sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            blitcrop(bg,0,0,480,72);
            linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
            if (disableit!=1) blit(Xsel,300,235);
            blit(Oback,380,235);
            blitAlphaImageToScreen(0,272-12,480,272,bg,0,272-12);
  //size 29
            pgeFontActivate(thefont29);
            pgeFontPrint(thefont29,185,41,"Physics", 0xFF2176EE); //Shadow
            pgeFontPrint(thefont29,184,40,"Physics", 0xFF3EFF00);
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,beginx-11+left,66,prompt,0xFF2b5a8b); //size 17
            pgeFontPrint(thefont17,beginx-12+left,65,prompt,0xffadcbee);
            sync();
            EndDrawing();
            if (presses.Buttons & PSP_CTRL_CIRCLE)
            {
                donecopy=0;
                presses.Buttons =0;
                break;
            }
        }
    }
}

void DoGeomtrig(int formulanum){
    float beginy=68.0f;
    int currarg=0;
    ellipsisc =0;
    int disableit=0;
    linesizer=0;
    accelsub=28;
    while (running)
    {
    { //Init
        if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
            //FlushBadData();
            guStart();
            clearScreen(0);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            RenderImage(bg,0,73,480,272,0,72,480,200,0);
            sceGuColor(RGBA(0xff,0xff,0xff,70));
            blit( invgeomtrig ,235,125);
                sceGuColor(0xFFFFFFFF);

            pgeFontActivate(thefont17);
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;

            ellipsisc++;
              if (ellipsisc ==10)
                strcpy( ellipsis,"");
            else if (ellipsisc ==20)
                strcpy( ellipsis,".");
            else if (ellipsisc ==30)
                strcpy( ellipsis,"..");
            else if (ellipsisc ==40){
                strcpy( ellipsis,"...");
                ellipsisc=0;
            }
            }
    if (formulanum==0)
    { // Lateral and total surface area and the volume of a cylinder
            if (donecopy==0)
            {
                strcpy(prompt,"The Lateral, Total Surface Area and Volume of a Cylinder");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Radius of the Cylinder: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Height of the Cylinder: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 2:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Lateral surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Total surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The Volume is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay2,CLR_ANS); //0xFFCE8149
                disableit=1;


                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Radius");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("Height");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }

                else
                    {
                        answer=(PI) * 2 * arg1 * arg2;
                        sprintf(ansdisplay,"%g sq.m",answer);
                        answer=(PI) * 2 * arg1 * (arg1 + arg2);
                        sprintf(ansdisplay1,"%g sq.m",answer);
                        answer=(PI) * arg1 * arg1 * arg2;
                        sprintf(ansdisplay2,"%g cu.m",answer);
                    }
                    break;

                case 3:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==1)
    { // Lateral and total surface area and the volume of a cube/cuboid
            if (donecopy==0)
            {
                strcpy(prompt,"The Lateral, Total Surface Area and Volume of a Cylinder");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Length of the Cuboid: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Width of the Cuboid: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Height of the Cuboid: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 3:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Lateral surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Total surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The Volume is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay2,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Length");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("Width");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 3:

                    arg3=TakeInput("Height");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }

                else
                    {
                        answer=2 * arg3 * (arg1 + arg2);
                        sprintf(ansdisplay,"%g sq.m",answer);
                        answer=2 * ((arg1*arg2)+(arg2*arg3)+(arg3*arg1));
                        sprintf(ansdisplay1,"%g sq.m",answer);
                        answer=arg1*arg2*arg3;
                        sprintf(ansdisplay2,"%g cu.m",answer);
                    }
                    break;

                case 4:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==2)
    { // Lateral and total surface area and the volume of a sphere
            if (donecopy==0)
            {
                strcpy(prompt,"The Lateral, Total Surface Area and Volume of a (hemi)Sphere");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Radius of the Sphere: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"--Sphere--",CLR_ANS_PROMPT,&tempvalx);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The Volume of Sphere/Hemisphere is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay1,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 85+dist*4,"--Hemisphere--",CLR_ANS_PROMPT,&tempvalx);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 105+dist*4,"The Lateral surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 106+dist*4,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 105+dist*4,ansdisplay2,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 125+dist*5,"The Total surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 126+dist*5,ansdisplay3,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 125+dist*5,ansdisplay3,CLR_ANS); //0xFFCE8149
                disableit=1;


                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Radius");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                else
                    {
                        answer=4 * (PI) * (arg1 * arg1);
                        sprintf(ansdisplay,"%g sq.m",answer);
                        answer=(4/3) * (PI) * (arg1 * arg1 * arg1);
                        sprintf(ansdisplay1,"%g/%g cu.m",answer,answer/2.0f);

                        answer=(4 * (PI) * (arg1 * arg1))/2.0f;
                        sprintf(ansdisplay2,"%g sq.m",answer);
                        answer=((4 * (PI) * (arg1 * arg1))/2.0f) + ((PI) * (arg1 * arg1));
                        sprintf(ansdisplay3,"%g sq.m",answer);
                    }
                    break;

                case 2:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==3)
    { // Lateral and total surface area and the volume of a cylinder
            if (donecopy==0)
            {
                strcpy(prompt,"The Lateral, Total Surface Area and Volume of [ANY] Pyramid");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Height of the pyramid: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the slant height: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the one side of the base: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the another side of the base: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;


            case 4:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Lateral surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Total surface area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The Volume is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay2,CLR_ANS); //0xFFCE8149
                disableit=1;


                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Perimeter of Base");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("Slant Height");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 3:

                    arg3=TakeInput("Side 1");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 4:

                    arg4=TakeInput("Side 2");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=0.5f * ((arg3+arg4)*2) * arg2;
                        sprintf(ansdisplay,"%g sq.m",answer);
                        answer=(0.5f * ((arg3+arg4)*2) * arg2 )+(arg3*arg4);
                        sprintf(ansdisplay1,"%g sq.m",answer);
                        answer=((float)(1/3)*(arg3*arg4)*(arg1));
                        sprintf(ansdisplay2,"%g cu.m",answer);
                    }
                    break;

                case 5:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==4)
    { // Area of a triangle from 3 sides
            if (donecopy==0)
            {
                strcpy(prompt,"The area of a triangle by using 3 sides only");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the length of first side: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the length of second side: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the length of third side: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The area of the triangle is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Semi-Perimeter is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS); //0xFFCE814
                disableit=1;
                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("1st side");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;
                case 2:

                    arg2=TakeInput("2nd side");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 3:

                    arg3=TakeInput("3rd side");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        extrans= answer=(arg1+arg2+arg3)/2;
                        sprintf(ansdisplay1,"%g",answer);
                        answer=sqrt(extrans * (extrans - arg1) * (extrans - arg2) * (extrans - arg3));
                        sprintf(ansdisplay,"%g sq.units",answer);
                    }
                    break;

                case 4:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==5)
    { // Area of an equilateral triangle
            if (donecopy==0)
            {
                strcpy(prompt,"The area of an equilateral triangle");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the side: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The area is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Side Length");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=(sqrt(3)*arg1 * arg1)/4;
                        sprintf(ansdisplay,"%g sq.units",answer);
                    }
                    break;

                case 2:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==6)
    { // Radians to degrees
            if (donecopy==0)
            {
                strcpy(prompt,"Radians to Degrees Converter");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Angle in #PIE# Radians: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Angle in degrees is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Angle in Radians");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=arg1 * (180/(22/7));
                        sprintf(ansdisplay,"%g Degrees",answer);
                    }
                    break;

                case 2:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

    if (formulanum==7)
    { // Degrees to radians
            if (donecopy==0)
            {
                strcpy(prompt,"Degrees to radians Converter");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Angle in Degrees: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Angle in Radians is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS); //0xFFCE8149
                disableit=1;

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:

                    arg1=TakeInput("Angle in Degrees");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=arg1 * ((22/7)/180);
                        sprintf(ansdisplay,"%g #PIE# Radians",answer);
                    }
                    break;

                case 2:
                    FinishGeomtrig();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula


        { //Term
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            blitcrop(bg,0,0,480,72);
            linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
            if (disableit!=1) blit(Xsel,300,235);
            blit(Oback,380,235);
            //size 29
            pgeFontActivate(thefont29);
            pgeFontPrint(thefont29,174,41,"Trigonometry", 0xFF2176EE); //Shadow
            pgeFontPrint(thefont29,173,40,"Trigonometry", 0xFF3EFF00);
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,beginx-11+left,66,prompt,0xFF2b5a8b); //size 17
            pgeFontPrint(thefont17,beginx-12+left,65,prompt,0xffadcbee);
            sync();
            EndDrawing();
            if (presses.Buttons & PSP_CTRL_CIRCLE)
            {
                donecopy=0;
                presses.Buttons =0;
                break;
            }
        }
    }
}

void DoAlgebra(int formulanum){
    float beginy=68.0f;
    float mover=0.0f;
    int currarg=0;
    int disableit=0;
    ellipsisc =0;
    float accel=0.5f;
    int lift=0;
    int delayaaa=0;
    int smooothen=0;
    int direec=2;
    linesizer=0;
    accelsub=28;
        while (running)
    {
            { //Init
                if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
            //FlushBadData();
            guStart();
            clearScreen(0xffffffff);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            RenderImage(bg,0,73,480,272,0,72,480,200,0);
            sceGuColor(RGBA(0xff,0xff,0xff,70));
            blit( invalg ,235.0f,125.0f);
            sceGuColor(0xFFFFFFFF);

            pgeFontActivate(thefont17);
            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;

        ellipsisc++;
          if (ellipsisc ==10)
                strcpy( ellipsis,"");
            else if (ellipsisc ==20)
                strcpy( ellipsis,".");
            else if (ellipsisc ==30)
                strcpy( ellipsis,"..");
            else if (ellipsisc ==40){
                strcpy( ellipsis,"...");
                ellipsisc=0;
            }
        }

        if (formulanum==0)
        { // Quadratic Solution
            if (donecopy==0)
            {
                strcpy(prompt,"Quadratic Equation Axx+Bx+c");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Value of A: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis,0xFF000000);
                break;

            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Value of B: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Value of C: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 3:

                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                smooothen=0;


            if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 155 && beginy>= VarminY)
        {
            delayaaa++;
            smooothen=1;
            lift=0;
            if (delayaaa==2) { if (accel < 5.0f) accel +=0.2f; delayaaa=0;}
            mover = 0.1f+accel;
            beginy -= mover;
            direec=1;
        }

         if (yvel < 110 && beginy<= VarmaxY)
        {
            delayaaa++;
            smooothen=1;
            lift=0;
            if (delayaaa==2) { if (accel < 5.0f) accel+=0.2f; delayaaa=0; }
            mover = 0.1f+accel;
            beginy += mover;
            direec=0;
        }
    } //main block

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }



                if (positive.Buttons & PSP_CTRL_DOWN && beginy>= VarminY)
                {
                    delayaaa++;
                    smooothen=1;
                    lift=0;
                    if (delayaaa==2) { if (accel < 5.0f) accel +=0.2f; delayaaa=0;}
                    mover = 0.1f+accel;
                    beginy -= mover;
                    direec=1;
                }

                if (positive.Buttons & PSP_CTRL_UP && beginy<= VarmaxY)
                {
                    delayaaa++;
                    smooothen=1;
                    lift=0;
                    if (delayaaa==2) { if (accel < 5.0f) accel+=0.2f; delayaaa=0; }
                    mover = 0.1f+accel;
                    beginy += mover;
                    direec=0;
                }

                if (lift !=2) lift++;
                if (lift==2)
                {
                    accel=0.0f;
                    if (mover<=0) { mover = 0.0f; direec=2; }

                    if (direec)
                    {
                        if (mover>0) mover -=  0.1;
                        if (beginy>= VarminY) beginy -= mover;
                    }

                    if (direec==0)
                    {
                        if (mover>0) mover -= 0.1;
                        if (beginy<= VarmaxY) beginy += mover;
                    }
                }
                blit(bar,455,80);
                blit(blob,450,(((100-       (((beginy+ -VarminY)/(VarmaxY + -VarminY))*100.0f)       )/100) * maxYpos) + minYpos);
                blit(Misc[1],beginx , beginy + 175+dist*8);
                if (smooothen) sceGuTexFilter(GU_LINEAR,GU_LINEAR);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Solution of equation: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25,ansdisplay,CLR_ANS); //0xFFCE8149

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45 +dist,"Factored form: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist,ansdisplay5,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 125+dist*5,"Discriminant:  ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 126+dist*5,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 125+dist*5,ansdisplay1,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*2,"X intercept: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*2,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*2,ansdisplay2,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 85+dist*3,"Derivative: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*3,ansdisplay3,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 85+dist*3,ansdisplay3,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 105+dist*4,"The graph goes: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 106+dist*4,ansdisplay4,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 105+dist*4,ansdisplay4,CLR_ANS);
                disableit=1;

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 145+dist*6,"Area under the X-Axis: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 146+dist*6,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 145+dist*6,ansdisplay6,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 165+dist*7,"The equation's minimum is at: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 166+dist*7,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 165+dist*7,ansdisplay7,CLR_ANS);

                float xset=0.0f;
                float resulting=0.0f;
                float x0=0.0f,y0=0.0f;
                float x11=0.0f,y11=0.0f;
                int cnt=0;

                for (xset=-15.0f; xset < 15.0f ; xset+=0.1f)
                {
                    resulting = ((arg1 * xset * xset ) + (arg2 * xset) + arg3);
                    x11=xset*20.0f + 160.0f;
                    y11=((beginy + 295.0f)+(float)dist*8.0f)-resulting*20.0f;


                    //175.0f+120.0f=295.0f
                    if (cnt!=0 && y11>=beginy + 175+dist*8)
                    //(xset + 160.0f)-0.01,((beginy+295.0f+(float)dist*8.0f) + resulting)-0.01,xset + 160.0f,(beginy+295.0f+(float)dist*8.0f) + resulting,0xFF0000FF);
                    GuDrawLine(x0,y0,x11,y11,0xFF000000);
                    cnt++;
                    x0=x11;
                    y0=y11;

                }

                break;
            } //Close Switch
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 0: //Do nothing.. Since user did nothin'
                    break;

                case 1:
                    arg1=TakeInput("A");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                        sprintf(prompt,"Quadratic equation %gxx+Bx+C",arg1);

                    break;

                case 2:
                    arg2=TakeInput("B");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                        sprintf(prompt,"Quadratic equation %gxx+%gx+C",arg1,arg2);
                    break;

                case 3:
                    arg3=TakeInput("C");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(prompt,"Quadratic equation %gxx+%gx+%g",arg1,arg2,arg3);
                        answer=((arg2*arg2) - (4 * arg1 * arg3));
                        sprintf(ansdisplay1,"%g",answer);
                        if (answer>0)
                        {
                            answer=((-arg2 + (float)(sqrt (arg2*arg2 - (4*arg1*arg3))))/ 2 * arg1);
                            sprintf(ansdisplay, "(%g, ",answer);
                            sprintf(ansdisplay5,"(X+%g)",answer);
                            answer=((-arg2 - (float)(sqrt (arg2*arg2 - (4*arg1*arg3))))/ 2 * arg1);
                            sprintf(tempstor,"%g)",answer);
                            strcat(ansdisplay,tempstor);
                            sprintf(tempstor,"(X+%g)",answer);
                            strcat(ansdisplay5,tempstor);
                        }
                        else if (answer==0)
                        {
                            answer=((-arg2 + (float)(sqrt (arg2*arg2 - (4*arg1*arg3))))/ 2 * arg1);
                            sprintf(ansdisplay, "%g only",answer);
                            sprintf(ansdisplay5,"(X+%g)(X+%g)",answer,answer);
                        }
                        else
                        {
                        sprintf(ansdisplay, "NO REAL ROOTS");
                        sprintf(ansdisplay5, "N/A");
                        }

                        answer=((-arg2)/2*arg1);
                        sprintf(ansdisplay2,"(%g,0)",answer);

                        sprintf(ansdisplay3,"%gX+%g",2*arg1,arg2);

                        if (arg1 > 0) sprintf( ansdisplay4,"Upwards");
                        else if (arg1 < 0) sprintf( ansdisplay4,"Downwards");

                        float answer1=0.0f;
                        float answer2=0.0f;
                        answer1=((-arg2 + (float)(sqrt (arg2*arg2 - (4*arg1*arg3))))/ 2 * arg1);
                        answer2=((-arg2 - (float)(sqrt (arg2*arg2 - (4*arg1*arg3))))/ 2 * arg1);


                            //Math.abs(((a/3)*x1*x1*x1 + (b/2)*x1*x1 + c*x1))+Math.abs((a*x2*x2*x2)/3 + (b*x2*x2)*.5 + (c*x2));
                        answer = fabs(((arg1/3)*answer1*answer1*answer1 + (arg2/2)*answer1*answer1 + arg3*answer1)) + fabs((arg1*answer2*answer2*answer2)/3 + (arg2*answer2*answer2)*0.5 + (arg3*answer2));
                        sprintf(ansdisplay6,"%g",answer);

                        extrans =answer = -arg2 / (2* arg1);
                        sprintf(ansdisplay7,"(%g,",answer);

                        //a*ansrnd[5]*ansrnd[5]+b*ansrnd[5]+c ;
                        answer = arg1 * extrans * extrans + arg2 * extrans + arg3;
                        sprintf( tempstor, "%g)",answer);
                        strcat(ansdisplay7,tempstor);

                        VarminY = -200.0f;
                        VarmaxY = 68.0f;

                    }
                    break;

                case 4:
                    FinishAlg();
                    break;
                } //Switch
            } //X Pressed
        } //Forumula

        else if (formulanum==3)
        { // Distance between two points
            if (donecopy==0)
            {
                sprintf(prompt,"Point stats of A(-,-) B(-,-)");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter X1 coordinate: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter Y1 coordinate: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter X2 coordinate: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter Y2 coordinate: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 4:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Scale for the Graph[Press Right for Best-Fit]: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 5:
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                smooothen=0;

    if (!mokitUNplugged)
        {
        sioPutchar(0x32);
        yvel=sioGetChar();

        //stop trying to read sio if motion kit is NOT plugged in
        if (yvel ==1280)
       {
           termcount++;
           if (termcount==100)
           {
           mokitUNplugged=1;
           showmsgmokit=1;
           }
       }

        if (yvel > 155 && beginy>= VarminY)
        {
            delayaaa++;
            smooothen=1;
            lift=0;
            if (delayaaa==2) { if (accel < 5.0f) accel +=0.2f; delayaaa=0;}
            mover = 0.1f+accel;
            beginy -= mover;
            direec=1;
        }

         if (yvel < 110 && beginy<= VarmaxY)
        {
            delayaaa++;
            smooothen=1;
            lift=0;
            if (delayaaa==2) { if (accel < 5.0f) accel+=0.2f; delayaaa=0; }
            mover = 0.1f+accel;
            beginy += mover;
            direec=0;
        }
    } //main block

        if (mokitUNplugged && showmsgmokit)
        {
         if (termcount<400) { termcount++; pset(0,0); pput("Motion Kit Not detected! "); }
         if (termcount==400) showmsgmokit=0;
        }

                if (positive.Buttons & PSP_CTRL_DOWN && beginy>= VarminY)
                {
                    delayaaa++;
                    smooothen=1;
                    lift=0;
                    if (delayaaa==2) { if (accel < 5.0f) accel +=0.2f; delayaaa=0;}
                    mover = 0.1f+accel;
                    beginy -= mover;
                    direec=1;
                }

                if (positive.Buttons & PSP_CTRL_UP && beginy<= VarmaxY)
                {
                    delayaaa++;
                    smooothen=1;
                    lift=0;
                    if (delayaaa==2) { if (accel < 5.0f) accel+=0.2f; delayaaa=0; }
                    mover = 0.1f+accel;
                    beginy += mover;
                    direec=0;
                }

                if (lift !=2) lift++;
                if (lift==2)
                {
                    accel=0.0f;
                    if (mover<=0) { mover = 0.0f; direec=2; }

                    if (direec)
                    {
                        if (mover>0) mover -=  0.1;
                        if (beginy>= VarminY) beginy -= mover;
                    }

                    if (direec==0)
                    {
                        if (mover>0) mover -= 0.1;
                        if (beginy<= VarmaxY) beginy += mover;
                    }
                }
                blit(bar,455,80);
                blit(blob,450,(((100-       (((beginy+ -VarminY)/(VarmaxY + -VarminY))*100.0f)       )/100) * maxYpos) + minYpos);
                blit(Misc[1],beginx , beginy+95+dist*4);
                if (smooothen) sceGuTexFilter(GU_LINEAR,GU_LINEAR);
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The distance between the points is ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Midpoint is ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay2,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The Slope is ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay1,CLR_ANS);
                disableit=1;
                pgeFontActivate(thefont17);
                pgeFontPrint(thefont17,beginx,beginy + 85+dist*4,ansdisplay3,CLR_ANS_PROMPT);
                pgeFontPrint(thefont17,beginx+160,beginy+215+10,tempstor+dist*4,0xff000000);
                GuDrawLine(beginx+((arg1*20)*arg5)+140 , beginy+95+dist*4+120-((arg2*20)* arg5), beginx+((arg3*20) * arg5)+140, beginy+95+dist*4+120-((arg4*20)*arg5), 0xFF000000);
                sceGuTexFilter(GU_NEAREST,GU_NEAREST);


{  //Old algorithm

//                if ((presses.Buttons & PSP_CTRL_DOWN) && (mover>=-0.1f))
//                {
//                    mover=-3.0f;
//                }
//                if ((mover <=-0.1f) && (beginy >=-85))
//                {
//                    mover +=0.1f;
//                    beginy += mover;
//                    if (beginy==65) mover=0.0f;
//                    //sceKernelDelayThread(100000);
//                }
//
//                if (presses.Buttons & PSP_CTRL_UP) mover=3.0f;
//
//                if ((mover >= 0.1f) && (beginy < 66))
//                {
//                    mover -=0.1f;
//                    beginy += mover;
//                    if (beginy==65) mover=0.0f;
//                }
//
}

                break;
            } //Switch
            if ((presses.Buttons & PSP_CTRL_RIGHT) && (currarg==4))
            {
                arg5 = 1;
                if ( fabs(arg1) >6 || fabs(arg2)>6 || fabs(arg3)>6 || fabs(arg4)>6)
                {
                    arg5 = 0.5;
                    if ( fabs(arg1*0.5) > 6 || fabs(arg2*0.5) > 6 || fabs(arg3*0.5) > 6 || fabs(arg4*0.5) > 6)
                    {
                        arg5 = 0.2;
                        if ( fabs(arg1*0.2) > 6 || fabs(arg2*0.2) > 6 || fabs(arg3*0.2) > 6 || fabs(arg4*0.2) > 6)
                        {
                        arg5 = 0.1;
                        if ( fabs(arg1*0.1) > 6 || fabs(arg2*0.1) > 6 || fabs(arg3*0.1) > 6 || fabs(arg4*0.1) > 6) arg5 = 0.1/2;
                        }
                    }
                }
                sprintf(tempstor,"%g",1/arg5);
                sprintf(ansdisplay3,"Scale: 1 cm - %g units",1/arg5);
                currarg++;
            }

            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);

                switch (currarg)
                {
                case 0:
                    break;

                case 1:
                    arg1=TakeInput("x1");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                        sprintf(prompt,"Point stats of A(%g,-) B(-,-)",arg1);
                    break;

                case 2:
                    arg2=TakeInput("y1");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                        sprintf(prompt,"Point stats of A(%g,%g) B(-,-)",arg1,arg2);
                    break;

                case 3:
                    arg3=TakeInput("x2");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                        sprintf(prompt,"Point stats of A(%g,%g) B(%g,-)",arg1,arg2,arg3);
                    break;

                case 4:
                    arg4=TakeInput("y2");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(prompt, "Point stats of A(%g,%g) B(%g,%g)",arg1,arg2,arg3,arg4);
                        answer=sqrt (((arg3-arg1)*(arg3-arg1)) + ((arg4-arg2)*(arg4-arg2)));
                        sprintf(ansdisplay, "%g",answer);
                        answer=(arg1+arg3)/2;
                        sprintf(ansdisplay2, "(%g,",answer);
                        answer=(arg2+arg4)/2;
                        sprintf(tempstor,"%g)",answer);
                        strcat(ansdisplay2,tempstor);
                        VarminY = -85.0f;
                        VarmaxY = 68.0f;

                        if (arg3-arg1==0) sprintf(ansdisplay1, "UNDEFINED.");
                        else
                        {
                            answer=(arg4-arg2)/(arg3-arg1);
                            sprintf(ansdisplay1, "%g",answer);
                        }
                    } //Case
                    break;

                case 5:
                    arg5=TakeInput("'Scale 1 Cm to ?? units'");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    sprintf(tempstor,"%g",1/arg5);
                    sprintf(ansdisplay3,"Scale: 1 cm - %g units",1/arg5);
                    break;

                case 6:
                    FinishAlg();
                    break;
                } //Switch
            } //X Pressed

        } //Forumula

        else if (formulanum==4)
        { // 2x2 matrix determinant
            if (donecopy==0)
            {
                sprintf(prompt,"Determinant of 2x2 Matrix");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemA: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);

                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,"[A  B]",CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,"[A  B]",CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,"[C  D]",CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,"[C  D]",CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemB: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemC: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemD: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 4:
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                smooothen=0;

                pgeFontActivate(thefont19);
                sprintf(ansdisplay1,"[%g %g]",arg1,arg2);
                sprintf(ansdisplay2,"[%g %g]",arg3,arg4);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay1,CLR_ANS);

                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay2,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,"The determinant is ",CLR_ANS_PROMPT,&tempvalx);

                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay,CLR_ANS);



                break;
            } //Switch

            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);

                switch (currarg)
                {
                case 0:
                    break;

                case 1:
                    arg1=TakeInput("ItemA");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay5,"[%g B]",arg1);
                        sprintf(ansdisplay6,"[C  D]");
                    }
                    break;

                case 2:
                    arg2=TakeInput("ItemB");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay5,"[%g %g]",arg1,arg2);
                    }
                    break;

                case 3:
                    arg3=TakeInput("ItemC");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay6,"[%g  D]",arg3,arg4);
                    }
                    break;

                case 4:
                    arg4=TakeInput("ItemD");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=(arg1*arg4)-(arg2*arg3);
                        sprintf(ansdisplay, "%g",answer);

                    } //Case
                    break;

                case 5:
                    FinishAlg();
                    break;
                } //Switch
            } //X Pressed

        } //Forumula

else if (formulanum==5)
        { // 2x2 matrix determinant
            if (donecopy==0)
            {
                sprintf(prompt,"Determinant of 3x3 Matrix");
                donecopy=1;
            }
            switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemA: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);

                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,"[A  B  C]",CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,"[A  B  C]",CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,"[D  E  F]",CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,"[D  E  F]",CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,"[G  H  I]",CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,"[G  H  I]",CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemB: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemC: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 3:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemD: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;

            case 4:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemE: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;

            case 5:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemF: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;

            case 6:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemG: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;

            case 7:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemH: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;

            case 8:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter itemI: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay5,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 45+dist*2,ansdisplay5,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay6,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 65+dist*3,ansdisplay6,CLR_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay7,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 85+dist*4,ansdisplay7,CLR_ANS);
                pgeFontActivate(thefont17);

                break;
            case 9:
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                smooothen=0;

                pgeFontActivate(thefont19);
                sprintf(ansdisplay1,"[%g %g %g]",arg1,arg2,arg3);
                sprintf(ansdisplay2,"[%g %g %g]",arg4,arg5,arg6);
                sprintf(ansdisplay3,"[%g %g %g]",arg7,arg8,arg9);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay1,CLR_ANS);

                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay2,CLR_ANS);

                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay3,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay3,CLR_ANS);


                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 85+dist*4,"The determinant is ",CLR_ANS_PROMPT,&tempvalx);

                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 86+dist*4,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 85+dist*4,ansdisplay,CLR_ANS);

                break;
            } //Switch

            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);

                switch (currarg)
                {
                case 0:
                    break;

                case 1:
                    arg1=TakeInput("ItemA");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay5,"[%g B C]",arg1);
                        sprintf(ansdisplay6,"[D  E F]");
                        sprintf(ansdisplay7,"[G  H I]");
                    }
                    break;

                case 2:
                    arg2=TakeInput("ItemB");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay5,"[%g %g C]",arg1,arg2);
                    }
                    break;

                case 3:
                    arg3=TakeInput("ItemC");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay5,"[%g %g %g]",arg1,arg2,arg3);
                    }
                    break;

                case 4:
                    arg4=TakeInput("ItemD");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay6,"[%g E F]",arg4);
                    } //Case
                    break;

                case 5:
                    arg5=TakeInput("ItemE");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay6,"[%g %g F]",arg4,arg5);
                    }
                    break;

                case 6:
                    arg6=TakeInput("ItemF");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay6,"[%g %g %g]",arg4,arg5,arg6);
                    } //Case
                    break;

                case 7:
                    arg7=TakeInput("ItemG");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay7,"[%g H I]",arg7);
                    }
                    break;


                case 8:
                    arg8=TakeInput("ItemH");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay7,"[%g %g I]",arg7,arg8);
                    }
                    break;


                case 9:
                    arg9=TakeInput("ItemI");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        sprintf(ansdisplay7,"[%g %g %g]",arg7,arg8,arg9);
                        answer=( ((arg1*arg5*arg9)+(arg2*arg6*arg7)+(arg3*arg4*arg8)) - ((arg7*arg5*arg3)+(arg8*arg6*arg1)+(arg9*arg4*arg2)) );//(7*5*3+8*6*1+9*4*2)
                        sprintf(ansdisplay,"%g",answer);
                    }
                    break;


                case 10:
                    FinishAlg();
                    break;
                } //Switch
            } //X Pressed

        } //Forumula


        else if (formulanum==6)
        { // 2/3rd/Nth root
            if (donecopy==0) {
                sprintf(prompt,"Square/Cube/Nth Root");
                donecopy=1;
            }
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 1:
                    arg1=TakeInput("Number");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                    sprintf(prompt,"Square/Cube/Nth Root of %g",arg1);
                    answer=(float)sqrt(arg1);
                    sprintf(ansdisplay,"%g",answer);
                    answer=pow(arg1,1.0/3.0);
                    sprintf(ansdisplay1,"%g",answer);
                    }
                    break;

                case 2:
                    arg2=TakeInput("N");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=pow(arg1,(float)(1.0f/arg2));
                        sprintf(ansdisplay2,"%g",answer);
                    }
                    break;

                case 3:
                    FinishAlg();
                    break;
                } //Switch Case Close
            } //IF X pressed close
             switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the number: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Square root: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Cube root: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65 +dist *3,"Enter 'N'[Press O to skip]: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 65+dist*3,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,"The Square root: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The Cube root: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay1,CLR_ANS);

                sprintf(ansdisplay4, "The %gth root: ",arg2);
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 65+dist*3,ansdisplay4,CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 66+dist*3,ansdisplay2,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 65+dist*3,ansdisplay2,CLR_ANS);
                disableit=1;
                break;
            } //Close Switch
         } //Forumula close

        else if (formulanum==1)
        { //Arithmetic Series
            if (donecopy==0) {
                sprintf(prompt,"Arithmetic Series solver");
                donecopy=1;
            }
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 1:
                    arg1=TakeInput("1st number");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 2:
                    arg2=TakeInput("Common Difference");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                   break;
                case 3:
                    arg3=TakeInput("Pos in the Series");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=(float)(arg1 + ((arg3-1)*(arg2)));
                        sprintf(ansdisplay,"The number %g term in the arithmetic seq is: ", arg3);
                        sprintf(ansdisplay1,"%g",answer);
                        answer=(float)(arg3 * (arg1 + (arg1 + ((arg3-1) * arg2)) ))/2;
                        sprintf(ansdisplay2,"%g",answer);
                    }
                    break;

                case 4:
                    FinishAlg();
                    break;
                } //Switch
            } //Pressed
             switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the 1st number in the series: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Common difference:",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the position in the series 'N': ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                 break;
           case 3:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,ansdisplay,CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay1,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The sum of terms in the series is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay2, CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay2, CLR_ANS);

                sprintf(ansdisplay3,"The series beginning with %gth Term below-> ",startval);
                pgeFontActivate(thefont17);
                pgeFontPrint(thefont17,beginx,beginy+65+dist*3,ansdisplay3,CLR_ANS_PROMPT);
                sprintf(ansdisplay4,"< %g, %g, %g, %g, %g >", arg1 + ((startval-1.0f)*(arg2))      ,       arg1 + ((startval+1.0f-1.0f)*(arg2))   ,    arg1 + ((startval+2.0f-1.0)*(arg2))        ,       arg1 + ((startval+3.0f-1.0f)*(arg2))      ,       arg1 + ((startval+4.0f-1.0f)*(arg2)));
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,beginx+1,beginy+86+5+dist*3,ansdisplay4,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,beginx,beginy+85+5+dist*3,ansdisplay4,CLR_ANS);
                disableit=1;
                if (positive.Buttons & PSP_CTRL_RTRIGGER) startval+=1.0f;

                if ((positive.Buttons & PSP_CTRL_LTRIGGER) && (startval > 1.0f)) startval -=1.0f;

                if (positive.Buttons & PSP_CTRL_RIGHT)
                {
                    startval+=1.0f;
                    sceKernelDelayThread(100000);
                }
                if ((positive.Buttons & PSP_CTRL_LEFT) && (startval > 1.0f))
                {
                    startval-=1.0f;
                    sceKernelDelayThread(100000);
                }

                break;
            }//Switch
         }//Forumula

        else if (formulanum==2)
        { //Geometric Series

        if (donecopy==0) {
        sprintf(prompt,"Geometric Series solver");
                donecopy=1;
            }
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 1:
                    arg1=TakeInput("1st number");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 2:
                    arg2=TakeInput("Common Ratio");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                   break;
                case 3:
                    arg3=TakeInput("Pos in the Series");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=(float)(arg1 * (pow(arg2,arg3-1)));
                        sprintf(ansdisplay,"The number %g term in the Geometric series is: ", arg3);
                        sprintf(ansdisplay1,"%g",answer);
                        answer=(float)(( arg1 *  (1 - pow(arg2,arg3))    )/ (1 - arg2));
                        sprintf(ansdisplay2,"%g",answer);
                    }
                    break;

                case 4:
                    FinishAlg();
                    break;
                } //Switch
            } //Pressed
             switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the 1st number in the Series: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 1:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the Common Ratio:",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 2:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the position in the series 'N': ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                 break;
           case 3:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,ansdisplay,CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay1,CLR_ANS);

                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 45+dist*2,"The sum of terms in the series is: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 46+dist*2,ansdisplay2, CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 45+dist*2,ansdisplay2, CLR_ANS);

                sprintf(ansdisplay3,"The series beginning with %gth Term below-> ",startval);
                pgeFontActivate(thefont17);
                pgeFontPrint(thefont17,beginx,beginy+65+dist*3,ansdisplay3,CLR_ANS_PROMPT);
                sprintf(ansdisplay4,"< %g, %g, %g, %g, %g >", arg1 * (pow(arg2,startval-1.0f))      ,     arg1 * (pow(arg2,startval+1.0-1.0f))   ,   arg1 * (pow(arg2,startval+2.0-1.0f))      ,       arg1 * (pow(arg2,startval+3.0-1.0f))      ,       arg1 * (pow(arg2,startval+4.0-1.0f)));
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,beginx+1,beginy+86+5+dist*3,ansdisplay4,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,beginx,beginy+85+5+dist*3,ansdisplay4,CLR_ANS);

                disableit=1;
                if (positive.Buttons & PSP_CTRL_RTRIGGER) startval+=1.0f;

                if ((positive.Buttons & PSP_CTRL_LTRIGGER) && (startval > 1.0f)) startval -=1.0f;

                if (positive.Buttons & PSP_CTRL_RIGHT)
                {
                    startval+=1.0f;
                    sceKernelDelayThread(100000);
                }
                if ((positive.Buttons & PSP_CTRL_LEFT) && (startval > 1.0f))
                {
                    startval-=1.0f;
                    sceKernelDelayThread(100000);
                }

                break;
            }//Switch
        }//Formula

        else if (formulanum==7)
        { // Simple Logarithms
            if (donecopy==0) {
                sprintf(prompt,"Simple Logarithmic solver");
                donecopy=1;
            }
            if (presses.Buttons & PSP_CTRL_CROSS)
            {
             currarg+=1; WAV_Play(moveplace);
                switch (currarg)
                {
                case 1:
                    arg1=TakeInput("The number");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    break;

                case 2:
                    arg2=TakeInput("Base");
                    if (cancel)
                    {
                        currarg -=1;
                        cancel=0;
                    }
                    else
                    {
                        answer=log(arg1)/log(arg2);
                        sprintf(ansdisplay,"The Log %g to base %g is: ",arg1,arg2);
                        sprintf(ansdisplay1,"%g",answer);
                    }
                    break;

                case 3:
                    FinishAlg();
                    break;
                } //Switch Case Close
            } //IF X pressed close
             switch (currarg)
            {
            case 0:
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the number: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;
            case 1:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25,"Enter the base: ",CLR_ANS_PROMPT,&tempvalx);
                pgeFontPrint(thefont17,tempvalx,beginy + 25,ellipsis, 0xFF000000);
                break;

            case 2:
                pgeFontActivate(thefont17);
                pgeFontPrintX(thefont17,beginx,beginy + 25+dist,ansdisplay,CLR_ANS_PROMPT,&tempvalx);
                pgeFontActivate(thefont19);
                pgeFontPrint(thefont19,tempvalx+1,beginy + 26+dist,ansdisplay1,CLR_SHAD_ANS);
                pgeFontPrint(thefont19,tempvalx,beginy + 25+dist,ansdisplay1,CLR_ANS);
                disableit=1;

                break;
            } //Close Switch
         } //Forumula close

        { //Term

            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            blitcrop(bg,0,0,480,72);
            linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
            if (disableit!=1) blit(Xsel,300,235);
            blit(Oback,380,235);

            blitAlphaImageToScreen(0,272-12,480,272,bg,0,272-12);

            //size 29
            pgeFontActivate(thefont29);
            pgeFontPrint(thefont29,168,41,"Calculus", 0xFF2176EE); //Shadow
            pgeFontPrint(thefont29,167,40,"Calculus", 0xFF3EFF00);
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,beginx-11+left,66,prompt,0xFF2b5a8b); //size 17
            pgeFontPrint(thefont17,beginx-12+left,65,prompt,0xffadcbee);
            //stats();
            EndDrawing();
            sync();
            if (presses.Buttons & PSP_CTRL_CIRCLE)
            {
                donecopy=0;
                presses.Buttons =0;
                ShowAlgebraList();
            }
        }

    }//While
}

#define FOCUS_ON_TEXTBOX_INPUT ((where == 0 ) || (where == 2 ))
#define BTN_CE 4
#define BTN_RESET 5

#define CROSS_PRESSED presses.Buttons & PSP_CTRL_CROSS
#define START_PRESSED presses.Buttons & PSP_CTRL_START

void cCalculator(){
    flickerpreventer=1;
    ellipsisc=0;
    int place=0;
    int where=0;
    double val=0.0;
    double result=0.0;
    double resultchanger=0.0;
    int operand=0; //0==none 1=add 2=subtract 3=multiply 4= divide;
    int opa=0;
    int rev=0;
    u32 glowcolor=0;
    int downplace=0;
    int downplacepos=0;
    int initialnumberinputted=0;
    linesizer=0;
    accelsub=28;
     while (running)
    {
            { //GENERIC initialization
            if (linesizer<0x1E0) linesizer+=accelsub;
            if (accelsub>2) accelsub--;
            //FlushBadData();
            if (presses.Buttons & PSP_CTRL_CIRCLE) MainMenu();
                if (flickerpreventer!=1)
                {
                guStart();
                clearScreen(0);
                }
                flickerpreventer=0;
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                RenderImage(bg,0,73,480,272,0,72,480,200,0);
                sceGuColor(RGBA(0xff,0xff,0xff,70));
                blit( invcalc ,235,125);
                sceGuColor(0xFFFFFFFF);
                pgeFontActivate(thefont17);
            sceCtrlReadBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;
            ellipsisc++;
            if (ellipsisc ==10)
                strcpy( ellipsis,"");
            else if (ellipsisc ==20)
                strcpy( ellipsis,".");
            else if (ellipsisc ==30)
                strcpy( ellipsis,"..");
            else if (ellipsisc ==40){
                strcpy( ellipsis,"...");
                ellipsisc=0;
            }
              //pset(0,0);
        //pput("Op %d Whr: %d Plc: %d Res: %g Resch: %g",operand,where,place,result,resultchanger);

       sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
       blit(Textbox,20,90);
       blitcrop(bg,0,0,480,72);
       linesizer!=0x1E0 ? blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,1) : blitresize(Misc[0],240-(linesizer/2),65,linesizer,Misc[0]->imageHeight,0) ;
       blit(start,285,235);
       blit(Oback,380,235);
        } //BLOCK close

            { //glow opacity controllers
            if (rev==0) { //glow button
            if (opa<0xff) opa+=5;
            if  (opa==0xff) rev=1;
            }
            if (rev) {
            if (opa>0) opa-=5;
            if  (opa==0) rev=0;
            }
            glowcolor = RGBA(0xff,0xff,0xff,opa);
            }

            if (FOCUS_ON_TEXTBOX_INPUT) { // Ellipsis sequence -> ... display code
            place=-10;
            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,448,125,ellipsis, 0xFFFFFFFF);
            }

            { //Button Image Display + Operation Selection
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);

            if (where==1) { //select operation / operand

            if (presses.Buttons & PSP_CTRL_RIGHT)
            {
                if (downplace==0 && place < 6) place+=1;
                if (downplace==1 && downplacepos < 1) downplacepos+=1;
                //WAV_Play(moveplace);
            }
            if (presses.Buttons & PSP_CTRL_LEFT)
            {
                if (downplace==0 && place > 0) place-=1;
                if (downplace==1 && downplacepos > 0) downplacepos-=1;
                //WAV_Play(moveplace);
            }
            if (presses.Buttons & PSP_CTRL_DOWN)
                {
                    if (downplace!=1) downplace=1;
                    downplacepos=0;
                    //WAV_Play(moveplace);
                }
            if (presses.Buttons & PSP_CTRL_UP)
                {
                if (downplace==1) downplace=0;
                place=0;
                //WAV_Play(moveplace);
                }
            } //BLOCK close

            if (downplace==1 && downplacepos==0 && place!=-10)
            {
                sceGuColor(glowcolor);
                blit(Button_g,65-10,210-9);
                sceGuColor(0xFFFFFFFF);
                blit(sqrtHigh,65,210);
            }
            else
            blit(sqrtimg,65,210);

            if (downplace==1 && downplacepos==1  && place!=-10)
            {
                sceGuColor(glowcolor);
                blit(Button_g,65+45-10,210-9);
                sceGuColor(0xFFFFFFFF);
                blit(cbrtHigh,65+45,210);
            }
            else
            blit(cbrtimg,65+45,210);


            if (downplace==0 && place==0)
            {
                sceGuColor(glowcolor);
                blit(Button_g,55-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(AddHigh,55,160);
            }
            else
            blit(Add,55,160);

            if (downplace==0 && place==1)
            {
                sceGuColor(glowcolor);
                blit(Button_g,100-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(SubtractHigh,100,160);
            }
            else
            blit(Subtract,100,160);

            if (downplace==0 && place==2)
            {
                sceGuColor(glowcolor);
                blit(Button_g,145-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(MultiplyHigh,100+45,160);
            }
            else
            blit(Multiply,100+45,160);

            if (downplace==0 && place==3)
            {
                sceGuColor(glowcolor);
                blit(Button_g,190-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(DivideHigh,100+45*2,160);
            }
            else
            blit(Divide,100+45*2,160);

            if (downplace==0 && place==4)
            {
                sceGuColor(glowcolor);
                blit(Button_g,(110+45*3)-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(CancelHigh,110+45*3,160);
            }
            else
            blit(Cancel,110+45*3,160);

            if (downplace==0 && place==5)
            {
                sceGuColor(glowcolor);
                blit(Button_g,(110+45*4)-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit (ResetHigh,110+45*4,160);
            }
            else
            blit (Reset,110+45*4,160);

            if (downplace==0 && place==6)
            {
                sceGuColor(glowcolor);
                blit(Button_g,(120+45*5)-10,160-9);
                sceGuColor(0xFFFFFFFF);
                blit(EqualsHigh,120+45*5,160);
            }
            else
            blit(Equals,120+45*5,160);

            } //Block

            { // Button Press action

                if (CROSS_PRESSED) {
                    if (place==BTN_CE) { //CE
                        operand=0;
                        resultchanger=0.0;
                        presses.Buttons = 0;
                        WAV_Play(click);
                    }

                    if (place==BTN_RESET) { //RESET
                        operand=0;
                        resultchanger=0.0;
                        result=0.0;
                        val=0.0;
                        presses.Buttons = 0;
                        WAV_Play(click);
                    }

                    if (where==0) { //init input
                        WAV_Play(moveplace);
                        val=TakeInput("Number");
                        if (cancel)
                            {
                                cancel=0;
                                where=0;
                                place=-10;
                                val=result;
                                presses.Buttons = 0;
                            }
                            else
                            {
                                if (initialnumberinputted==0) initialnumberinputted=1;
                            where=1;
                            place=0;
                            result=val;
                            downplace=0;
                            downplacepos=0;
                            presses.Buttons = 0;
                            }
                    }

                    if (where==2) {
                            WAV_Play(moveplace);
                            resultchanger=TakeInput("Number");
                            if (cancel)
                            {
                                cancel=0;
                                where=2;
                                place=-10;
                                presses.Buttons = 0;
                            }
                            else
                            {
                            where=3;
                            place=6;
                            result=resultchanger;
                            downplace=0;
                            downplacepos=0;
                            presses.Buttons = 0;
                            }
                    }

                    if (downplace==1) { // SQRT OR CBRT pressed
                        if (downplacepos==0)
                        {
                        WAV_Play(click);
                        result = sqrt(result);
                        val=result;
                        resultchanger=0.0f;
                        }
                        else if(downplace==1)
                        {
                        WAV_Play(click);
                        result = pow(result,1.0/3.0);
                        val=result;
                        resultchanger=0.0f;
                        }
                        presses.Buttons = 0;
                    }
                } //cross_PRESS block close

                if (where==3 && place==6 && CROSS_PRESSED) { //Calculation done. Focus on =
                    WAV_Play(click);
                    if (operand==1) result=val+resultchanger;
                    if (operand==2) result=val-resultchanger;
                    if (operand==3) result=val*resultchanger;
                    if (operand==4) result=val/resultchanger;
                    where=0;
                    place=-10;
                    presses.Buttons = 0;
                    }

                if (where==1) {//choose operation/operand
                        if ((place<=3) && (CROSS_PRESSED))
                        {
                        operand=place+1;
                        where=2;
                        place=-10;
                        presses.Buttons = 0;
                        WAV_Play(click);
                        }

                        if ( (place==6 && CROSS_PRESSED) || START_PRESSED )
                        {
                        if (operand==1) result=val+resultchanger;
                        if (operand==2) result=val-resultchanger;
                        if (operand==3) result=val*resultchanger;
                        if (operand==4) result=val/resultchanger;
                        where=0;
                        presses.Buttons = 0;
                        WAV_Play(click);
                        }
                    }

                if (START_PRESSED) {
                if (where==2) {
                WAV_Play(moveplace);
                where=3;
                resultchanger=result;
                place=6;
                presses.Buttons = 0;
                downplace=0;
                downplacepos=0;
            }

                if (where==0) {//take value in display
            WAV_Play(moveplace);
            where=1;
            place=0;
            val=result;
            presses.Buttons = 0;
            downplace=0;
            downplacepos=0;
            }
                }
            } //BLOCK CLOSE

            sprintf(ansdisplay,"%f",result);
            pgeFontActivate(thefont29);
            if (result==0.0) sprintf(ansdisplay,"0");
            pgeFontPrint(thefont29,30,120,ansdisplay,0xFF000000);

       pgeFontActivate(thefont17);
       pgeFontPrint(thefont17,11,66,"The clean and tidy calc: ",0xFF2b5a8b);//CLR_SHAD_ANS);
       pgeFontPrint(thefont17,10,65,"The clean and tidy calc: ",0xffadcbee);//0xFF7DAACD);
       pgeFontActivate(thefont29);
       pgeFontPrint(thefont29,163,41,"Calculator", 0xFF2176EE); //Shadow
       pgeFontPrint(thefont29,162,40,"Calculator", 0xFF3EFF00);

        EndDrawing();
        sync();
        if (presses.Buttons & PSP_CTRL_CIRCLE) MainMenu();
        }
        }

void transition(){
    scePowerSetClockFrequency (333, 333, 166); //cwcheat CPU fixer
    float mover=0.0f; //Main title
    float moveritems=70.0f; //Subjects text movers
    float moveritemsaccel=0.1f;
    float moveraccel=0.5f;
    float itemover=0.0f;
    int wherey=0;
    float algx=0.0f;
    float geomx=0.0f;
    float calcx=0.0f;
    flickerpreventer=1;
    while (running)
    {
        //stats(); - fps for debug mode
        if (flickerpreventer!=1)
        {
        guStart();
        clearScreen(0);
        }
        flickerpreventer=0;
        sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
        blit(bg,0,0);
        pgeFontActivate(thefont17);
        sceCtrlReadBufferPositive(&positive,1); //We want a Vblank

        //pset(0,0);
        //pput("Itemover: %f Diagselaccel: %f",itemover,diagselaccel);

        if(positive.Buttons & PSP_CTRL_LTRIGGER) sceKernelDelayThread(70000);

        if (mover>261.0f) //Diagonal selection animation
        {
            if (diagselaccel >0.5f) diagselaccel -=0.1f;
            if (algx < 108.0f) algx+=diagselaccel;
            if (algx < 104.0f) geomx=algx;
            if (algx < 93.0f) calcx=algx;
                //sceKernelDelayThread(3500);
                if (menupos==0)
                {
                    if (itemover<75.0f)
                    {
                    itemover+=diagselaccel;
                    pgeFontPrint(thefont17,itemx+1.0f+algx,algy+1-itemover,"Calculus", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx+algx,algy-itemover,"Calculus", 0xFF3EFF00);//0xff2d4dc0);
                    }
                    if (itemover>=75.0f) ShowAlgebraList();
                }
                if (menupos==1)
                {
                    if (itemover<95.0f)
                    {
                    itemover+=diagselaccel;
                    pgeFontPrint(thefont17,itemx+1.0f+algx,phyzy+1-itemover,"Physics", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx+algx,phyzy-itemover,"Physics", 0xFF3EFF00);
                    }
                    if (itemover>=95.0f) ShowPhysicsList();
                }
                if (menupos==2)
                {
                    if (itemover<115.0f)
                    {
                    itemover+=diagselaccel;
                    pgeFontPrint(thefont17,itemx+1.0f+geomx,geomtrigy+1-itemover,"Trigonometry", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx+geomx,geomtrigy-itemover,"Trigonometry", 0xFF3EFF00);
                    }
                    if (itemover>=115.0f) ShowGeometrigList();
            }
                if (menupos==3)
                {
                    if (itemover<134.0f)
                    {
                    itemover+=diagselaccel;
                    pgeFontPrint(thefont17,itemx+1.0f+calcx,calcy+1-itemover,"Calculator", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx+calcx,calcy-itemover,"Calculator", 0xFF3EFF00);
                    }
                    if (itemover>=134.0f)  cCalculator();
            }

            }
        if (mover<=261.0f) //Animation code
        {
            moveraccel+=0.1f;
            mover+=moveraccel; //2
                /*if (moveritemsaccel<5.5f)*/ moveritemsaccel+=0.1f;//0.01f;
                if (moveritems>=-84.0f) moveritems-= moveritemsaccel; //6;
                sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                blit (board, boardx+(float)mover,boardy);
                sceGuColor(0xffffffff);
                switch (menupos)
                {
                    case 0:
                    blit(subalg,subjx+(float)mover,subjy);
                    break;
                    case 1:
                    blit(subphyz,subjx+(float)mover,subjy);
                    break;
                    case 2:
                    blit( subtrig ,subjx+(float)mover,subjy);
                    break;
                    case 3:
                    blit( subcalc ,subjx+(float)mover,subjy);
                    break;
                }
                if (mover <41.0f) //Main title anim
                {
                    pgeFontActivate(thefont29);
                    pgeFontPrint(thefont29,141,44.0f-(float)mover,"Academic Aid", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont29,140,43.0f-(float)mover,"Academic Aid", 0xFF3EFF00);
                }
                if (moveritems >-84.0f) //Non chosen item to left anim
                {
                    pgeFontActivate(thefont17);
                    if (menupos==0)
                    {
                    pgeFontPrint(thefont17,moveritems,phyzy,"Physics", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,geomtrigy,"Trigonometry", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,calcy,"Calculator", CLR_ANS_PROMPT);
                    }
                    if (menupos==1)
                    {
                    pgeFontPrint(thefont17,moveritems,algy,"Calculus", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,geomtrigy,"Trigonometry", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,calcy,"Calculator", CLR_ANS_PROMPT);
                    }
                    if (menupos==2)
                    {
                    pgeFontPrint(thefont17,moveritems,algy,"Calculus", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,phyzy,"Physics", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,calcy,"Calculator", CLR_ANS_PROMPT);
                    }
                    if (menupos==3)
                    {
                    pgeFontPrint(thefont17,moveritems,algy,"Calculus", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,phyzy,"Physics", CLR_ANS_PROMPT);
                    pgeFontPrint(thefont17,moveritems,geomtrigy,"Trigonometry", CLR_ANS_PROMPT);
                    }
                }
                if ( itemover==0) //show selected item only
                {
                    pgeFontActivate(thefont17);
                    if (menupos==0)
                    {
                    pgeFontPrint(thefont17,itemx+1,algy+1,"Calculus", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx,algy,"Calculus", colorhigh);
                    wherey=algy;
                    }
                    if (menupos==1)
                    {
                    pgeFontPrint(thefont17,itemx+1,phyzy+1,"Physics",0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx,phyzy,"Physics", colorhigh);
                    wherey=phyzy;
                    }
                    if (menupos==2)
                    {
                    pgeFontPrint(thefont17,itemx+1,geomtrigy+1,"Trigonometry", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx,geomtrigy,"Trigonometry", colorhigh);
                    wherey=geomtrigy;
                    }
                    if (menupos==3)
                    {
                    pgeFontPrint(thefont17,itemx+1,calcy+1,"Calculator", 0xFF7DAACD); //Shadow
                    pgeFontPrint(thefont17,itemx,calcy,"Calculator", colorhigh);
                    wherey=calcy;
                    }
                    sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
                    blit(Selectorimg,currxselx+5,wherey-13.0f);

                }
             }
        EndDrawing();
    }
}

void credits(){
    char randtext[3] ="";
    flickerpreventer=1;
    int x=0;
    int y=0;
    char randchar[101] = " .,!?:;0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#\"£$%^&*()[]{}<>/\\|~`+-=_~";
    //29 max words of 29 length
    char creditstext[30][30] = {"Programming & Concept", "Vivek Javvaji (Mr305)", "Layout & GUI", "Mr305", "Graphics","Jomann", "Google", "Mr305", "Sound FX","Google Audio","Color Schemes","Mr305"} ;
    char xtralong[2][100]={"Uses pgeFont by InsertWittyName - http://insomniac.0x89.org", "Thanks to everyone for feedback! "};
    int counter=0;
    int lastpsoss=0;
    float yposy=292.0f;
    float xpos=490.f;
    while(1)
    {

        { //Init
            if (flickerpreventer!=1)
                {
                guStart();
                clearScreen(0xFFFFFFFF);
                sceCtrlPeekBufferPositive(&positive,1);
                presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
                lastpositive = positive;
                }
                flickerpreventer=0;
        }
        pgeFontActivate( thefont15);

            for (y=272; y>0 ; y-=10)
            {
                for (x=0;x<(int)vfpu_randf(50.0,480.0);x+=15)
                    {

                sprintf(randtext,"%c",randchar[(int)vfpu_randf(0, 99)]);
                pgeFontPrint(thefont15,x,y,randtext,0xFF007D00);
            }
        }

        yposy-=0.1f;
        pgeFontActivate( thefont29);
        pgeFontPrintX(thefont29,0,372,creditstext[counter],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont29,230.0f-(lastpsoss/2.0f),yposy,creditstext[counter],RGB(0,0xff,100));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+1],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35.0,creditstext[counter+1],RGB(0,100,0xff));



        pgeFontActivate( thefont29); //layout
        pgeFontPrintX(thefont29,0,372,creditstext[counter+2],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont29,230.0f-(lastpsoss/2.0f),yposy + 35 * 3.0,creditstext[counter+2],RGB(0,0xff,100));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+3],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 4.0,creditstext[counter+3],RGB(0,100,0xff));



        pgeFontActivate( thefont29); //gfx
        pgeFontPrintX(thefont29,0,372,creditstext[counter+4],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont29,230.0f-(lastpsoss/2.0f),yposy + 35 * 6.0,creditstext[counter+4],RGB(0,0xff,100));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+5],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 7.0,creditstext[counter+5],RGB(0,100,0xff));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+6],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 8.0,creditstext[counter+6],RGB(0,100,0xff));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+7],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 9.0,creditstext[counter+7],RGB(0,100,0xff));


        pgeFontActivate( thefont29); //gfx
        pgeFontPrintX(thefont29,0,372,creditstext[counter+8],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont29,230.0f-(lastpsoss/2.0f),yposy + 35 * 11.0,creditstext[counter+8],RGB(0,0xff,100));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+9],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 12.0,creditstext[counter+9],RGB(0,100,0xff));


        pgeFontActivate( thefont29); //gfx
        pgeFontPrintX(thefont29,0,372,creditstext[counter+10],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont29,230.0f-(lastpsoss/2.0f),yposy + 35 * 14.0,creditstext[counter+10],RGB(0,0xff,100));

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,creditstext[counter+11],RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,230.0f-(lastpsoss/2.0f),yposy + 35 * 15.0,creditstext[counter+11],RGB(0,100,0xff));

        if (yposy+ 35* 15.0 < 100)
        {
            xpos -= 0.2f;

        pgeFontActivate( thefont19);
        pgeFontPrintX(thefont19,0,372,(const char *)xtralong,RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,xpos,136,xtralong[0],RGB(0,100,0xff));

        pgeFontPrintX(thefont19,0,372,(const char *)xtralong,RGB(0,0xff,100),&lastpsoss);
        pgeFontPrint(thefont19,xpos + 750,136,xtralong[1],RGB(0,100,0xff));
        }

        EndDrawing();
        if (presses.Buttons & PSP_CTRL_CIRCLE){ fade=1; MainMenu(); }
        if (xpos<-950.0f) { fade=1; MainMenu(); }
    }
    }

/*
ShowCreditsmessage:

int delayaa=0;
    int delayvar=3;
    int reverse=0;


        if (xx < 480 && reverse==0) xx+=5;
            drawQuad(0,102,xx,68,RGBA(0,0,0,100));
        if (presses.Buttons & PSP_CTRL_CIRCLE) creditsmsgshown=1;

        if (xx >= 480)
        {
        if (speed > 0) ssspeed -=acceaal;
        if (placepos > 70) placepos-=ssspeed;

        if (reverse==0)
            {
        pgeFontActivate(thefont19);
        pgeFontPrint(thefont19,placepos+1,138+1,"Press TRIANGLE at any time for Credits",0xFF000000);
        pgeFontPrint(thefont19,placepos,138,"Press TRIANGLE at any time for Credits",0xFFFF7D00);
            }

        if ((placepos <=70) && (reverse==0)) { sceKernelDelayThread(2000000); reverse=1; }
        }
            if (reverse==1)
            {
            ssspeed++;
            placepos+=ssspeed;
            pgeFontActivate(thefont19);
            pgeFontPrint(thefont19,placepos+1,138+1,"Press TRIANGLE at any time for Credits",0xFF000000);
            pgeFontPrint(thefont19,placepos,138,"Press TRIANGLE at any time for Credits",0xFFFF7D00);
            if (placepos >= 480)
            {
                if (xx>0) xx -=10; if (xx <=0) creditsmsgshown=1;
                }
            }

>END<

*/
