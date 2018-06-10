//file_op.c
//Gen file name,file index,save file etc.

#include <stdio.h>
#include <string.h>

#include "mtypes.h"
#include "file_op.h"

int FnBase(char * fn,const char * fnCfg){
	if(fnCfg ==NULL){
		char fnDef[] = "XX_SLT";
		strcpy(fn,fnDef);	
	}
	else{
	FILE * fid = fopen(fnCfg,"r");

	fclose(fid);
	}
	return 0;
} 



int FnChannel(char *fn,int ch){
	if(ch==0)
		strcat(fn,"_SHE_0");
	else if(ch==1)
		strcat(fn,"_SHN_1");
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
	if(index[did-1] >= 1000000)
		index[did-1] = 0;
	return 0;
}


int FnMSeed(char * fnX,char * fnY,char *fnZ, int did,const char * fnCfg){
	char cIndex[10];
	memset(cIndex,0,10);
	CIndex(cIndex,did);	
	
	FnBase(fnX,fnCfg);
	FnBase(fnY,fnCfg);
	FnBase(fnZ,fnCfg);
	FnChannel(fnX,0);
	FnChannel(fnY,1);
	FnChannel(fnZ,2);
	strcat(fnX,cIndex);
	strcat(fnY,cIndex);
	strcat(fnZ,cIndex);
	strcat(fnX,".mseed");
	strcat(fnY,".mseed");
	strcat(fnZ,".mseed");
	printf("fnX = %s\tfnY = %s\tfnZ = %s\n",fnX,fnY,fnZ);
	return 0;
}









