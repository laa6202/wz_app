#ifndef __ALG_STEIM2_H
#define __ALG_STEIM2_H

#include "mtypes.h"

int TestAlg(void);
int GetFrame0(pFRAME,pRAWALL,int,int,int);

U32 GetW0(const int*);
U32 GetW1(int*,pRAWALL,int,int,int *);
U32 GetWs(int*,pRAWALL,int,int,int *);

#endif

 
