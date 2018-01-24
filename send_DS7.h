#ifndef __SEND_DS7_H
#define __SEND_DS7_H

#include "types.h"


typedef struct LPKGTAIL{
	unsigned int w0;	//0
	unsigned int w1_3[3];
	unsigned int w4_10[7];
	unsigned int w11;	//65535
	unsigned int w12;	//0
	unsigned int w13;	//65535
	unsigned int w14;	//32768
	unsigned int w15;	//crc
} LPKGTAIL,*pLPKGTAIL;


typedef struct LPKG{
	unsigned int load[4000];
	unsigned int expr[80];
	LPKGTAIL tail;	
}	LPKG,*pLPKG;


typedef struct SPKG{
	unsigned char load[1024];
}	SPKG,*pSPKG;


WZPKG InitWZPackage(int lenSample);
SPKG InitSmallPackage(void);
int PushWZ2L(pLPKG plpkg,WZPKG wzpkg);
int PushL2S(pSPKG  pspkg[8] ,LPKG lpkg);
unsigned int CalcLCRC(LPKG lpkg);
int SendSmallPackage(CFG cfg,SPKG spkg);
int SendDS7(CFG cfg,WZPKG wzpkg);


#endif
