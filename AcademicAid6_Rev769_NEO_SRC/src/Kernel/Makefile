TARGET = sioDriver
OBJS = main.o sceCodec_Driver.o

INCDIR =
CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION=371
PRX_EXPORTS = sioDriver.exp

USE_KERNEL_LIBC=1
USE_KERNEL_LIBS=1

LIBDIR =
LDFLAGS = -mno-crt0 -nostartfiles
LIBS = -lpspdebug -lpspsdk -lpsphprm_driver

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

all:
		psp-build-exports -s sioDriver.exp
		cp ./sioDriver.S ../sioDriver.S
		cp ./sioDriver.prx ../sioDriver.prx
		
clean:
		rm -f $(FINAL_TARGET) $(EXTRA_CLEAN) $(OBJS) $(PSP_EBOOT_SFO) $(PSP_EBOOT) $(EXTRA_TARGETS)
		rm -f *.S 