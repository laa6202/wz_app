#ifndef __BUF4MSEED_H
#define __BUF4MSEED_H

#include "mtypes.h"

#define START_UTC 12345
#define START_NS  67890

int InitWZPKG(pWZPKG);
int InitRawAll(pRAWALL);

int GenTestWZPKG(pWZPKG,int);
int ShowWZPKGInfo(pWZPKG);
int BufWZPKG2Raw(pRAWALL,WZPKG); 

#endif
