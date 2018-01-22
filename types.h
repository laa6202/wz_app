#ifndef __TYPES_H
#define __TYPES_H

typedef unsigned char UCHAR;

typedef struct {
	UCHAR devid;
	UCHAR rw;
	UCHAR modid;
	UCHAR addr;
	UCHAR data;
	UCHAR q;
} CMD, *pCMD;

 
typedef struct {
	int lenLoad;
	int lenTail;	//no crc
	UCHAR head[12];
	UCHAR load[18000];
	UCHAR tail[1000];
	UCHAR crc[2];
}	WZPKG,*pWZPKG;


typedef struct {
	int  port;
	char ip[20];
	int  status;
} RHOST, *pRHOST;


typedef struct {
	char  fName[250];
	RHOST remoteHost;
} CFG, *pCFG;


#endif
