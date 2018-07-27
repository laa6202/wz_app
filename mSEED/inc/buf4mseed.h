#ifndef __BUF4MSEED_H
#define __BUF4MSEED_H

#include "mtypes.h"

#define START_UTC 3600
#define START_NS  800000000

int InitWZPKG2(pWZPKG);
int InitRawAll(pRAWALL);

int GenTestWZPKG(pWZPKG,int);
int ShowWZPKGInfo(pWZPKG);
int BufInitSeek(WZPKG);
int BufWZPKG2Raw(pRAWALL,WZPKG); 

#endif
