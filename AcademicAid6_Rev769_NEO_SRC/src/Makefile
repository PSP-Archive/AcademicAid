TARGET = MathAid
OBJS = pgeFont.o misc.o rapidInPSP.o main.o graphics.o framebuffer.o wavloader.o  ./Images/Algebra.o ./Images/AlgebraInvert.o ./Images/Back.o ./Images/Bar.o ./Images/BG.o ./Images/Blob.o ./Images/Board.o ./Images/D0.o ./Images/D0High.o ./Images/D1.o ./Images/D1High.o ./Images/D2.o ./Images/D2High.o ./Images/D3.o ./Images/D3High.o ./Images/D4.o ./Images/D4High.o ./Images/D5.o ./Images/D5High.o ./Images/D6.o ./Images/D6High.o ./Images/D7.o ./Images/D7High.o ./Images/D8.o ./Images/D8High.o ./Images/D9.o ./Images/D9High.o ./Images/Dot.o ./Images/DotHigh.o ./Images/Geomtrig.o ./Images/GeomtrigInvert.o ./Images/Line.o ./Images/Minus.o ./Images/MinusHigh.o ./Images/Physics.o ./Images/PhysicsInvert.o ./Images/Plane.o ./Images/Test.o ./Misc/memabcFont.o ./Images/Xstart.o ./Images/Sselect.o ./Images/Oquit.o ./Misc/memcred.o ./Images/Button_glow.o ./Images/EqualsHigh.o ./Images/ResetHigh.o ./Images/PlusHigh.o ./Images/SubtractHigh.o ./Images/DivideHigh.o ./Images/MultiplyHigh.o ./Images/CancelHigh.o ./Images/Equals.o ./Images/Reset.o ./Images/Plus.o ./Images/Subtract.o ./Images/Divide.o ./Images/Multiply.o ./Images/Cancel.o ./Images/sqrtimg.o ./Images/sqrtHigh.o ./Images/cbrtimg.o ./Images/cbrtHigh.o ./Images/calculator.o ./Images/calculatorinvert.o ./Images/Textbox.o ./Images/Selector.o sioDriver.o

CFLAGS = -O2 -G0 -g -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -g
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =
LIBS = -lpsputility -lfreetype -lpsprtc -lmikmod -lmmio -lpspaudiolib -lpspaudio -lpng -lz -lm -lpspvram -lpspgu -lpspgum -lpspdisplay -lpsppower -lpspmath -lpspfpu

LDFLAGS =

.SUFFIXES: .png .ttf

.png.o:
	bin2o -i $*.png $@ $(notdir $*)
.ttf.o:
	bin2o -i $*.ttf $@ $(notdir $*)

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

release:
		mksfo "Academica Scholastic Suite" PARAM.SFO
		pack-pbp EBOOT.PBP PARAM.SFO ./Images/icon0.png NULL NULL ./Images/pic1.png NULL mathaid.prx NULL
		cp ./EBOOT.PBP release3xx/AcademicAid6
		rm -f ./EBOOT.PBP
		cp ./sioDriver.prx ./release3xx/AcademicAid6/sioDriver.prx