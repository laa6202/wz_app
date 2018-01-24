#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "send_DS7.h"


WZPKG InitWZPackage(int lenSample){
	WZPKG wzpkg;
	int lenHead = 12;
	int lenLoad = 9 * lenSample;
	int lenWZPKG = lenLoad + lenHead + 2;
	int i;
	int k=0;

	wzpkg.lenLoad = lenLoad;
	wzpkg.lenTail = 0;
	wzpkg.head[0] = 0x51;
	wzpkg.head[1] = 0x01;
	wzpkg.head[2] = 0x0;
	wzpkg.head[3] = 0x0;
	for(i=4;i<12;i++)
		wzpkg.head[i] = 0x0;
	for(i=0;i<lenSample;i++){
		k = i * 9;
		//wzpkg.load[k] = (i & 0xff0000) >> 16;
		//wzpkg.load[k+1] =	(i & 0xff00) >> 8;
		//wzpkg.load[k+2] = (i & 0xff);
		wzpkg.load[k] 	= (i & 0xff);
		wzpkg.load[k+1] =	(i & 0xff);
		wzpkg.load[k+2] = (i & 0xff);
		wzpkg.load[k+3] = 0x22;
		wzpkg.load[k+4] = 0x22;
		wzpkg.load[k+5] = 0x22;
		wzpkg.load[k+6] = 0x33;
		wzpkg.load[k+7] = 0x33;
		wzpkg.load[k+8] = 0x33;
	}
	unsigned int crc = 0;
	for(i=0;i<lenHead;i++)
		crc = crc + wzpkg.head[i];
	for(i=0;i<lenLoad;i++)
		crc = crc + wzpkg.load[i];
	wzpkg.crc[0] = crc & 0xff;
	wzpkg.crc[1] = (crc & 0xff00) >> 8;


	return wzpkg; 
}


SPKG InitSmallPackage(){
	SPKG spkg;
	int lenLoad = sizeof(spkg.load);
	int i;
	for(i=0;i<lenLoad;i++)
		spkg.load[i] = i+10;
	
	return spkg;
}


int SendSmallPackage(CFG cfg,SPKG spkg){

//	printf("SendSmallPackage()\n");	
	int sock;
	sock = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in destAddr;
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(cfg.remoteHost.port);
	destAddr.sin_addr.s_addr=inet_addr(cfg.remoteHost.ip);

//	printf("Send DGRAM to %s on %d port\n",
//				cfg.remoteHost.ip,cfg.remoteHost.port);
	
	sendto(sock,&spkg,sizeof(spkg),0,
		(struct sockaddr *)&destAddr,sizeof(destAddr));

	return 0;
}


int  PushWZ2L(pLPKG  plpkg, WZPKG wzpkg){
	int k;
	int i;
	memset(plpkg,0,8192);
	for(i=0;i<500;i++){
		plpkg->load[8*i] =
			(wzpkg.load[i*9+1]<<8) + (wzpkg.load[i*9+2]);
	}
	plpkg->tail.w11 = 0xffff;	
	plpkg->tail.w13 = 0xffff;
	plpkg->tail.w14 = 0x8000;
	unsigned int crc = CalcLCRC(*plpkg);	
	plpkg->tail.w15 = crc;

	return 0;
}



int  PushL2S(pSPKG  pspkg[8], LPKG lpkg){
	UCHAR data[8192];
	memset(data,0,8192);
	for(int i=0;i<4000;i++){
		data[i*2] = (lpkg.load[i] & 0xff00) >> 8;
		data[i*2+1] = (lpkg.load[i] & 0xff);
	}
	for(int i=0;i<80;i++){
		data[i*2+4000] = (lpkg.expr[i] & 0xff00) >> 8;
		data[i*2+4001] = (lpkg.expr[i] & 0xff);
	}

	data[8182] = (lpkg.tail.w11 & 0xff00) >> 8;
	data[8183] = lpkg.tail.w11 & 0xff;
	data[8184] = (lpkg.tail.w12 & 0xff00) >> 8;
	data[8185] = lpkg.tail.w12 & 0xff;
	data[8186] = (lpkg.tail.w13 & 0xff00) >> 8;
	data[8187] = lpkg.tail.w13 & 0xff;
	data[8188] = (lpkg.tail.w14 & 0xff00) >> 8;
	data[8189] = lpkg.tail.w14 & 0xff;
	data[8190] = (lpkg.tail.w15 & 0xff00) >> 8;
	data[8191] = lpkg.tail.w15 & 0xff;

	for(int i=0;i<8;i++)
		memset(pspkg[i],0,sizeof(SPKG));

	for(int i=0;i<1024;i++){
		pspkg[0]->load[i] = data[i]; 
		pspkg[1]->load[i] = data[i+1024]; 
		pspkg[2]->load[i] = data[i+1024 * 2]; 
		pspkg[3]->load[i] = data[i+1024 * 3]; 
		pspkg[4]->load[i] = data[i+1024 * 4]; 
		pspkg[5]->load[i] = data[i+1024 * 5]; 
		pspkg[6]->load[i] = data[i+1024 * 6]; 
		pspkg[7]->load[i] = data[i+1024 * 7]; 
	}	
	return 0;
}


unsigned int CalcLCRC(LPKG lpkg){
	int i;	
	unsigned int crc =0;
	for(i=0;i<4000;i++)
		crc = crc + lpkg.load[i];
	for(i=0;i<80;i++)
		crc = crc + lpkg.expr[i];
	crc = crc + lpkg.tail.w0;
	crc = crc + lpkg.tail.w1_3[0];
	crc = crc + lpkg.tail.w1_3[1];
	crc = crc + lpkg.tail.w1_3[2];
	for(i=4;i<=10;i++)
		crc =crc + lpkg.tail.w4_10[i];
	crc = crc + lpkg.tail.w11;
	crc = crc + lpkg.tail.w12;
	crc = crc + lpkg.tail.w13;
	crc = crc + lpkg.tail.w14;

	return crc;	
}

int SendDS7(CFG cfg,WZPKG wzpkg){
	printf("......SendDS7......\n");
	WZPKG wzpkg1 = InitWZPackage(2000);
//	SPKG spkg = InitSmallPackage();
	LPKG lpkg;
	PushWZ2L(&lpkg,wzpkg1);
	pSPKG * ppspkg;
	ppspkg = (pSPKG *) malloc(sizeof(pSPKG) * 8);
	for(int i=0;i<8;i++)
		ppspkg[i] = (pSPKG) malloc(sizeof(SPKG));
	PushL2S(ppspkg,lpkg);
	for(int i=0;i<8;i++)
		SendSmallPackage(cfg,*ppspkg[i]);

	return 0;
}



