#ifndef __GEN_MSEED_H
#define __GEN_MSEED_H

#include "mtypes.h"

int GenMSeed(int,int,RAWALL,const char*);

int GenPack(const char *,RAWALL,int,int);
int EofPack(RAWALL,int,int);


int GenHead(const char *fn,RAWALL,int,int);
int GenBlock0(const char *fn,RAWALL,int,int);
int GenBlock1(const char *fn,RAWALL,int,int);
int GenFrame0(const char *fn,RAWALL,int,int);
int GenFrames(const char *fn,RAWALL,int,int);


#endif

