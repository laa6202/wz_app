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


int FnIndex(char *fn){
	static int fIndex;
	char cIndex[8];
	memset(cIndex,0,8);
	sprintf(cIndex,"%07d",fIndex);
	printf("fIndex = %s\n",cIndex);
	strcat(fn,cIndex);
	fIndex ++;
	return 0;
}


int FnMSeed(char * fnMSeed,int ch, const char * fnCfg){
	char fn[200];
	memset(fn,0,200);
	FnBase(fn,fnCfg);
	FnChannel(fn,ch);
	FnIndex(fn);
	strcpy(fnMSeed,fn);
	strcat(fnMSeed,".mseed");
	printf("fnMSeed = %s\n",fnMSeed);
	return 0;
}









