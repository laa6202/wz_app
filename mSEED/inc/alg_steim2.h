#ifndef __ALG_STEIM2_H
#define __ALG_STEIM2_H

#include "mtypes.h"

int TestAlg(void);
int InterP(int,pRAWALL);
int ShowRawP(int,pRAWALL);

int GetFrame0(pFRAME,pRAWALL,int,int,int);
int GetFrames(pFRAME,pRAWALL,int,int,int);

U32 GetW0(const int*);
U32 GetW1(int*,pRAWALL,int,int,int *);
U32 GetWs(int*,pRAWALL,int,int,int *,int);

int PreDiffData(int*,pRAWALL,int,int,int,int);
int DiffRange(int *);
U32 BuildWs(int *,int);

int ChangeEndian32(int*);
int ChangeEndianFrm(pFRAME);

#endif

 
