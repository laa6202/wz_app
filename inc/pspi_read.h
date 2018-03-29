#ifndef __PSPI_READ_H
#define __PSPI_READ_H

int PspiInit(pSPI pspi);// 实现
int PspiRead(pWZPKG pwzpkg,pSPI pspi);// 实现

int InitWZPKG(pWZPKG pwzpkg);
int MakeWZPKG(pWZPKG pwzpkg);
int init_rand();


#endif
