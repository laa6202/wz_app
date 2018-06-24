//file_op.c
//Gen file name,file index,save file etc.

#include <stdio.h>
#include <string.h>

#include "mtypes.h"
#include "file_op.h"

int FnBase(char * fn,int did,const char * fnCfg){
	char fnBase[150];
	strcpy(fnBase,"DAT/XX_SLT");
	switch(did){
		case 2: strcat(fnBase,"_D02"); break;
		case 3:	strcat(fnBase,"_D03"); break;
		case 4: strcat(fnBase,"_D04"); break;
		default : strcat(fnBase,"_DXX"); break;
	}

	if(fnCfg ==NULL){
		strcpy(fn,fnBase);	
	}
	else{
	FILE * fid = fopen(fnCfg,"r");

	fclose(fid);
	}
	return 0;
} 



int FnChannel(char *fn,int ch){
	if(ch==0)
		strcat(fn,"_SHN_0");
	else if(ch==1)
		strcat(fn,"_SHE_1");
	else if(ch==2)
		strcat(fn,"_SHZ_2");
	else
		;
	return 0;
}


int CIndex(char *cIndex,int did){
	static int index[20];
	sprintf(cIndex,"_%07d",index[did-1]);
	index[did-1] ++;
	if(index[did-1] > 1000000)
		index[did-1] = 1;
	return 0;
}


int FnMSeed(char * fnX,char * fnY,char *fnZ, int did,const char * fnCfg){
	char cIndex[10];
	memset(cIndex,0,10);
	CIndex(cIndex,did);	
	
	FnBase(fnX,did,fnCfg);
	FnBase(fnY,did,fnCfg);
	FnBase(fnZ,did,fnCfg);
	FnChannel(fnX,0);
	FnChannel(fnY,1);
	FnChannel(fnZ,2);
	strcat(fnX,cIndex);
	strcat(fnY,cIndex);
	strcat(fnZ,cIndex);
	strcat(fnX,".mseed");
	strcat(fnY,".mseed");
	strcat(fnZ,".mseed");
//	printf("fnX = %s\tfnY = %s\tfnZ = %s\n",fnX,fnY,fnZ);
	return 0;
}









