#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "dir_save.h"

int WriteToFile(const WZPKG wzpkg,FILE * fid){
	fwrite(wzpkg.head,1,sizeof(wzpkg.head),fid);
	fwrite(wzpkg.load,1,sizeof(wzpkg.load),fid);
	fwrite(wzpkg.tail,1,wzpkg.lenTail,fid);
	fwrite(wzpkg.crc,1,sizeof(wzpkg.crc),fid);
	return 0;
}


int GetFn(char * fn,const CFG cfg){
	int fUsedID = cfg.fileDir.fUsedID;
	if(fUsedID == 0)
		strcpy(fn,cfg.fileDir.fNameDef);
	else
		strcpy(fn,cfg.fileDir.fName);
	return 0;
}


int SaveOneWZPKG(const CFG cfg,WZPKG wzpkg){
	//printf("......SaveOneWZPKG......\n");
	char fn[250];
	GetFn(fn,cfg);	
//	printf("save file name : %s\n",fn);
	FILE * fid = fopen(fn,"w");
	WriteToFile(wzpkg,fid);		
	fclose(fid);	
	printf("......SaveOneWZPKG OK ......\n");
	return 0;
}


int SaveSomeWZPKG(const CFG cfg,WZPKG wzpkg,int mount){
	printf("......SaveSomeWZPKG......\n");
	char fn[250];
	GetFn(fn,cfg);	
	FILE * fid = fopen(fn,"a");
	WriteToFile(wzpkg,fid);		
	fclose(fid);	
	return 0;
}


