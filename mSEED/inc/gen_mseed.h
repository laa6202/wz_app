#ifndef __GEN_MSEED_H
#define __GEN_MSEED_H

#include "mtypes.h"

int GenMSeed(int,int,pRAWALL,const char*);

int GenPack(const char *,pRAWALL,int,int);
int EofPack(pRAWALL,int,int);


//int GenHead(const char *fn,pRAWALL,int,int);
//int GenBlock0(const char *fn,pRAWALL,int,int);
//int GenBlock1(const char *fn,pRAWALL,int,int);
//int GenFrame0(const char *fn,pRAWALL,int,int);
//int GenFrames(const char *fn,pRAWALL,int,int);
int GenHead(FILE *,pRAWALL,int,int);
int GenBlock0(FILE *,pRAWALL,int,int);
int GenBlock1(FILE *,pRAWALL,int,int);
int GenFrame0(FILE *,pRAWALL,int,int);
int GenFrames(FILE *,pRAWALL,int,int);

//int UpdateHead(const char *fn,pRAWALL,int,int,int);
//int UpdateFrm0(const char *fn,pRAWALL,int,int,int);
int UpdateHead(FILE * fid,pRAWALL,int,int,int);
int UpdateFrm0(FILE * fid,pRAWALL,int,int,int);


#endif

