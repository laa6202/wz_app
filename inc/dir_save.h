#ifndef __DIR_SAVE_H
#define __DIR_SAVE_H

int WriteToFile(const WZPKG wzpkg,FILE * fid);
int GetFn(char * fn,const CFG cfg);

int SaveOneWZPKG(const CFG cfg,WZPKG wzpkg);
int SaveSomeWZPKG(const CFG cfg, WZPKG wzpkg, int mount);

int LogBegin();
int LogStr(const char *);


#endif
