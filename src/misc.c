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


#include "misc.h"

extern pspUtilityMsgDialogParams dialog;

int __freemem(){
 void *ptrs[480];
 int mem, x, i;
 for (x = 0; x < 480; x++)
 {
    void *ptr = malloc(51200);
    if (!ptr) break;

    ptrs[x] = ptr;
 }
 mem = x * 51200;
 for (i = 0; i < x; i++)
  free(ptrs[i]);

 return mem;
}

void ConfigureDialog(pspUtilityMsgDialogParams *dialog, size_t dialog_size){
    memset(dialog, 0, dialog_size);

    dialog->base.size = dialog_size;
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE,
				&dialog->base.language); // Prompt language
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN,
				&dialog->base.buttonSwap); // X/O button swap

    dialog->base.graphicsThread = 0x11;
    dialog->base.accessThread = 0x13;
    dialog->base.fontThread = 0x12;
    dialog->base.soundThread = 0x10;
}

void stats(){
    frame_count++;
    sceRtcGetCurrentTick(&curr_tick);
    float curr_fps = 1.0f / curr_ms;
    double time_span = ((curr_tick-last_tick)) / (float)tick_res;
    curr_ms = time_span / frame_count;
    frame_count = 0;
    sceRtcGetCurrentTick(&last_tick);
    pspDebugScreenSetXY(0,0);
    pspDebugScreenPrintf("%d fps",(int)curr_fps);
//    pspDebugScreenSetXY(0,31);
//    pspDebugScreenPrintf("Free Ram: %d",__freemem()/1024);
}
