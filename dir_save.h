#ifndef __DIR_SAVE_H
#define __DIR_SAVE_H

int WriteToFile(const WZPKG wzpkg,FILE * fid);

int SaveOneWZPKG(const CFG cfg,WZPKG wzpkg);
int SaveSomeWZPKG(const CFG cfg, pWZPKG * pwzpkg, int mount);


#endif
