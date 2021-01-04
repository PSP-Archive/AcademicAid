	.set noreorder

#include "pspimport.s"

	IMPORT_START	"sceCodec_driver",0x00010000
	IMPORT_FUNC	"sceCodec_driver",0x856E7487,sceCodec_856E7487 //sceCodecOutputEnable