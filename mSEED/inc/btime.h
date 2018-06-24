#ifndef __BTIME_H
#define __BTIME_H

#include <time.h>
#include "mtypes.h"


int TestTime(void);
int CovWZ2BTIME(pBTIME,WZPKG);
int CovU2BTIME(pBTIME,U32,U32,int,S16);

int TT2Day(struct tm*);

#endif

