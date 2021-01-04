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

//Based on Neo Motion Kit Sample and Loco Roco Motion Plugin (by myself)
#include <pspsdk.h>

PSP_MODULE_INFO("sioDriver", 0x1006, 1, 0);

#define PSP_UART4_FIFO 0xBE500000
#define PSP_UART4_STAT 0xBE500018
#define PSP_UART_TXFULL  0x20
#define PSP_UART_RXEMPTY 0x10

unsigned int i = 0;

void sioPutchar(int ch){
	// as you see this is _blocking_...not an issue for
	// normal use as everithing doing I/O
	// should run in its own thread..in addition, HW FIFO isn't
	// working at all by now, so queue should not be that long :)
	//sceCodec_856E7487(1,1);
//	while(_lw(PSP_UART4_STAT) & PSP_UART_TXFULL);
//	_sw(ch, PSP_UART4_FIFO);
    pspDebugSioPutchar(ch);
}

int sioGetChar(void){
   i = 0;
	while((i < 100000) && (_lw(PSP_UART4_STAT) & PSP_UART_RXEMPTY)) i++; // loop until rx buffer full

	return _lw(PSP_UART4_FIFO);

}

void sioInit(int baud){
	unsigned int k1 = pspSdkSetK1(0);
    pspDebugSioInit();
	sceKernelDelayThread(1000000);
	pspDebugSioSetBaud(baud);
    sceCodec_856E7487(1,1); //audio tada!
	pspSdkSetK1(k1);
}

int module_start(SceSize args, void *argp)
{
       sceDisplaySetBrightness(100,0);
        return 0;
}

int module_stop()
{
        return 0;
}
