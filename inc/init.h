#ifndef __INIT_H
#define __INIT_H

#include "types.h"

int InitCfg(pCFG pcfg);
int InitSPI(pSPI pcSPI,pSPI ppSPI);
int EndSPI(SPI cSPI,SPI pSPI);

#endif
