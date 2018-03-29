#ifndef __CSPI_RW_H
#define __CSPI_RW_H

#include "types.h"

int CspiInit(pSPI pspi);// 实现
int CspiRead(pCMD pcmd,pSPI pspi); //实现
int CspiWrite(pCMD pcmd,pSPI pspi);//实现


#endif
