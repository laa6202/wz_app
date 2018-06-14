#ifndef __GEN_MSEED_H
#define __GEN_MSEED_H

#include "mtypes.h"

int GenMSeed(int,int,pRAWALL,const char*);

int GenPack(const char *,pRAWALL,int,int);
int EofPack(pRAWALL,int,int);


int GenHead(const char *fn,pRAWALL,int,int);
int GenBlock0(const char *fn,pRAWALL,int,int);
int GenBlock1(const char *fn,pRAWALL,int,int);
int GenFrame0(const char *fn,pRAWALL,int,int);
int GenFrames(const char *fn,pRAWALL,int,int);


#endif

