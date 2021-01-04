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

#include "rapidInPSP.h"

extern WAV* moveplace;
extern WAV* click;


double TakeInput(char varname[100]){
    char let[150][2];
    char final[150]="";
    double finalint=0.0f;
    int horzlitpos=0;
    int vertlitpos=0;
    int hylit=0;
    int place=0;
    int row1y=80;
    int row2y=row1y+47;
    int row3y=row2y+47;
    int row4y=row3y+47;
    int coldist=50;
    int col1x=85;
    int col2x=col1x+coldist;
    int col3x=col2x+coldist;
    int negative=0;
    int disabledec=0;
    char prompt[100];
    int jk=1;
    sprintf(prompt,"Enter the value for '%s' below: ",varname);
    u32 glowcolor;
    int opa=0;
    int rev=0;
    int placex=0;
    int placex1=0;
    int timesa=0;
    int buttpress=0;
    int buttpresspos=0;
    int accel=0;
    while (1)
    {
//        pset(0,0);
//        pput("%.2f %.2f %.2f",arg1,arg2,arg3);
            FlushBadData();
            if (buttpress==1)
            {
                if (accel < 4) accel++;
                if (buttpresspos < 10) buttpresspos = buttpresspos + accel;
                if (buttpresspos==10) { accel=0; buttpress=2; }
            }
            if (buttpress==2)
            {
                if (accel < 4) accel++;
                if (buttpresspos > 0 ) buttpresspos = buttpresspos - accel;// - accel;
                if (buttpresspos==0) {  buttpress=0; accel=0; }
            }

            if (jk!=1)
            {
            guStart();
            clearScreen(0);
            }
            jk=0;
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            RenderImage(bg,0,73,480,272,0,72,480,200,0);
            if (rev==0)
            {
            if (opa<255) opa+=5;
            if  (opa==255) rev=1;
            }
            if (rev==1)
            {
            if (opa>0) opa-=5;
            if  (opa==0) rev=0;
            }
            glowcolor = RGBA(255,255,255,opa);

        { //Buttons Display Blit
            if (hylit!=1) blit(number[1],col1x,row1y);
            if (hylit!=2) blit(number[2],col2x,row1y);
            if (hylit!=3) blit(number[3],col3x,row1y);
            if (hylit!=4) blit(number[4],col1x,row2y);
            if (hylit!=5) blit(number[5],col2x,row2y);
            if (hylit!=6) blit(number[6],col3x,row2y);
            if (hylit!=7) blit(number[7],col1x,row3y);
            if (hylit!=8) blit(number[8],col2x,row3y);
            if (hylit!=9) blit(number[9],col3x,row3y);
            if (hylit!=0) blit(number[0],col1x,row4y);
            if (hylit!=11) blit(number[11],col2x,row4y);
            if (disabledec == 0)
            {
              if (hylit!=12) blit(number[12],col3x,row4y);
            }

            switch (hylit)
            {
                case 0:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col1x -10 + (buttpresspos /2 ),row4y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[0],col1x + (buttpresspos /2 ) ,row4y + (buttpresspos /2 ),numhigh[0]->imageWidth - buttpresspos,numhigh[0]->imageHeight - buttpresspos,1);
                break;
                case 1:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col1x -10 + (buttpresspos /2 ),row1y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[1],col1x + (buttpresspos /2 ),row1y + (buttpresspos /2 ),numhigh[1]->imageWidth - buttpresspos,numhigh[1]->imageHeight - buttpresspos,1);
                break;
                case 2:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col2x -10 + (buttpresspos /2 ),row1y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[2],col2x + (buttpresspos /2 ),row1y + (buttpresspos /2 ),numhigh[2]->imageWidth - buttpresspos,numhigh[2]->imageHeight - buttpresspos,1);
                break;
                case 3:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col3x -10 + (buttpresspos /2 ),row1y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[3],col3x + (buttpresspos /2 ),row1y + (buttpresspos /2 ),numhigh[3]->imageWidth - buttpresspos,numhigh[3]->imageHeight - buttpresspos,1);
                break;
                case 4:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col1x -10 + (buttpresspos /2 ),row2y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[4],col1x + (buttpresspos /2 ),row2y + (buttpresspos /2 ),numhigh[4]->imageWidth - buttpresspos,numhigh[4]->imageHeight - buttpresspos,1);
                break;
                case 5:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col2x -10 + (buttpresspos /2 ),row2y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[5],col2x + (buttpresspos /2 ),row2y + (buttpresspos /2 ),numhigh[5]->imageWidth - buttpresspos,numhigh[5]->imageHeight - buttpresspos,1);
                break;
                case 6:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col3x -10 + (buttpresspos /2 ),row2y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[6],col3x + (buttpresspos /2 ),row2y + (buttpresspos /2 ),numhigh[6]->imageWidth - buttpresspos,numhigh[6]->imageHeight - buttpresspos,1);
                break;
                case 7:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col1x -10 + (buttpresspos /2 ),row3y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[7],col1x + (buttpresspos /2 ),row3y + (buttpresspos /2 ),numhigh[7]->imageWidth - buttpresspos,numhigh[7]->imageHeight - buttpresspos,1);
                break;
                case 8:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col2x -10 + (buttpresspos /2 ),row3y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[8],col2x + (buttpresspos /2 ),row3y + (buttpresspos /2 ),numhigh[8]->imageWidth - buttpresspos,numhigh[8]->imageHeight - buttpresspos,1);
                break;
                case 9:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col3x -10 + (buttpresspos /2 ),row3y-9 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[9],col3x + (buttpresspos /2 ),row3y + (buttpresspos /2 ),numhigh[9]->imageWidth - buttpresspos,numhigh[9]->imageHeight - buttpresspos,1);
                break;
                case 11:
                sceGuColor(glowcolor);
                if (buttpress==0 ) blitresize(Button_g,col2x -10 + (buttpresspos /2 ),row4y-10 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                sceGuColor(0xFFFFFFFF);
                blitresize(numhigh[11],col2x + (buttpresspos /2 ),row4y + (buttpresspos /2 ),numhigh[11]->imageWidth - buttpresspos,numhigh[11]->imageHeight - buttpresspos,1);
                break;
                case 12:
                if (disabledec ==0)
                {
                    sceGuColor(glowcolor);
                    if (buttpress==0 ) blitresize(Button_g,col3x -10 + (buttpresspos /2 ),row4y-10 + (buttpresspos /2 ),Button_g->imageWidth - buttpresspos,Button_g->imageHeight - buttpresspos,1);
                    sceGuColor(0xFFFFFFFF);
                    blitresize(numhigh[12],col3x + (buttpresspos /2 ),row4y + (buttpresspos /2 ),numhigh[12]->imageWidth - buttpresspos,numhigh[12]->imageHeight - buttpresspos,1);
                }
                break;
            }
            }

        { // Keypad Control

            sceCtrlPeekBufferPositive(&positive,1);
            presses.Buttons = ~lastpositive.Buttons & positive.Buttons;
            lastpositive = positive;
            if (presses.Buttons & PSP_CTRL_CIRCLE)
            {
                presses.Buttons =0;
                cancel=1;
                break;
            }
            if ((presses.Buttons & PSP_CTRL_RIGHT) && (horzlitpos <2))
            {
                horzlitpos+=1;
                WAV_Play(click);
            }
            if ((presses.Buttons & PSP_CTRL_LEFT) && (horzlitpos >0))
            {
                horzlitpos -=1;
                WAV_Play(click);
            }
            if ((presses.Buttons & PSP_CTRL_DOWN) && (vertlitpos <3))
            {
                vertlitpos+=1;
                WAV_Play(click);
            }
            if ((presses.Buttons & PSP_CTRL_UP) && (vertlitpos >0))
            {
                vertlitpos -=1;
                WAV_Play(click);
            }
        }

        { //Button Highlit/Select
            if (vertlitpos ==0)
            {
                switch ( horzlitpos)
                {
                case 0:
                    hylit = 1;
                    break;
                case 1:
                    hylit = 2;
                    break;
                case 2:
                    hylit = 3;
                    break;
                }
            }
            if (vertlitpos ==1)
            {
                switch ( horzlitpos)
                {
                case 0:
                    hylit = 4;
                    break;
                case 1:
                    hylit = 5;
                    break;
                case 2:
                    hylit = 6;
                    break;
                }
            }

            if (vertlitpos ==2)
            {
                switch ( horzlitpos)
                {
                case 0:
                    hylit = 7;
                    break;
                case 1:
                    hylit = 8;
                    break;
                case 2:
                    hylit = 9;
                    break;
                }
            }

            if (vertlitpos ==3)
            {
                switch ( horzlitpos)
                {
                case 0:
                    hylit =0;
                    break;
                case 1:
                    hylit = 11;
                    break;
                case 2:
                    (disabledec==1) ? (hylit = 11) :  (hylit = 12);
                    break;
                }
            }
        }

        { // Button Is pressed, value Input here + Value Display too

            if (presses.Buttons & PSP_CTRL_CROSS)
            {
                if (buttpress ==0) buttpress=1;
                WAV_Play(moveplace);
                if (hylit==11) //Negative button
                {
                    if (place==0) strcpy(final,"");
                    (negative==0) ? (negative=1):(negative=0);
                }
                else if (hylit==12)
                {
                    sprintf(let[place],".");
                    disabledec=1;
                    hylit=9;
                }
                else //Not Decimal or Negative but a number
                    sprintf(let[place],"%d",hylit);

                if (place ==0)
                {
                    if (hylit!=11) sprintf(final,"%c",let[0][0]);
                }
                else
                {
                    if (hylit!=11) strcat(final,let[place]);
                }

                if (hylit!=11)
                    place++;
            } //If X close
        } //Block close

        pgeFontActivate(thefont19);
        pgeFontPrintX(thefont19,260,150,final,0xFFFFFFFF,&placex);
        timesa++;
        if (placex<250) placex=260;
        if (timesa <= 25) pgeFontPrint(thefont19,placex+3,150,"_",0xFF0000FF);
        if (timesa==50) timesa=0;
        if ( negative==1) pgeFontPrint(thefont19,250,150,"-",0xFFFFFFFF);
        //here
        if (presses.Buttons & PSP_CTRL_START) ///OK IS PRESSED
        {
            //WAV_Play(moveplace);
            if (place!=0)
            {
                if (negative==1)
                {
                    sprintf(prompt,"-%s",final);
                    finalint = atof(prompt);
                    return finalint;
                }
                else
                {
                    finalint = atof(final);
                    return finalint;
                }
            }
            if (place==0)
            {
                cancel=1;
                break;
            }

        }

            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            blitcrop(bg,0,0,480,72);

              { //TITLE + SubHeading
            pgeFontActivate(thefont29);
            pgeFontPrint(thefont29,163,41,"Rapid InpSP", 0xFF2176EE); //Shadow
            pgeFontPrintX(thefont29,162,40,"Rapid InpSP", 0xFF3EFF00,&placex1);

            pgeFontActivate(irregsigns);
            pgeFontPrint(irregsigns,placex1+3,33,"TM",0xFF2176EE);
            pgeFontPrint(irregsigns,placex1+2,32,"TM",0xFF3EFF00);

            pgeFontActivate(thefont17);
            pgeFontPrint(thefont17,11,66,prompt,0xFF2b5a8b);
            pgeFontPrint(thefont17,10,65,prompt,0xffadcbee);

            pgeFontPrint(thefont17,261,126,"Current value:",0xFF7DAACD);
            pgeFontPrint(thefont17,260,125,"Current value:",0xFF99CCFF);
            sceGuTexMode(GU_PSM_8888,0,0,GU_TRUE);
            blit(Misc[0],0,65);
            blit(start,285,235);
            blit(Oback,380,235);

       }

    sync();
    EndDrawing();
    } //While
return 1;
}
