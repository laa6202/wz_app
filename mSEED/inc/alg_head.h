#ifndef __ALG_HEAD_H
#define __ALG_HEAD_H

#include "mtypes.h"

int GetSeq(char *,pRAWALL,int,int);
int GetStart(pMHEAD,pRAWALL,int,int);
int GetNumSample(U16 *,pRAWALL,int,int);

int ChangeEndianU16(U16 *);
int ChangeEndianS16(S16 *);

#endif


