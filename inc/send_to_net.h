#ifndef __SEND_TO_NET_H
#define __SEND_TO_NET_H

int InitSocket(void);
int SendToNet(const WZPKG wzpkg,FILE * fid);
int GetNet(char * fn,const CFG cfg);

int SendOneWZPKG(int sock,WZPKG wzpkg);
int SendSomeWZPKG(const CFG cfg, WZPKG wzpkg, int mount);


#endif
