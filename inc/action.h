#ifndef __ACTION_H
#define __ACTION_H

#include "types.h"
#include "mtypes.h"

int action(CFG cfg,SPI,SPI,pKEY,int sock,pRAWALL,pCFGALL);
int MainMSeed(int,pRAWALL,CFGALL);
int PrepareData(int,pRAWALL,CFGALL);
void *ThreadMSeed( void *arg);
void *ThreadTest( void *arg);


int ShowCMD(CMD);
int ShowPKGInfo(int,WZPKG);
int ShowStat(CFG,WZPKG,int);


#endif

