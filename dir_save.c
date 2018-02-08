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


int SaveOneWZPKG(const CFG cfg,WZPKG wzpkg){
	printf("......SaveOneWZPKG......\n");
	char fn[250];
	int fUsedID = cfg.fileDir.fUsedID;
	if(fUsedID == 0)
		strcpy(fn,cfg.fileDir.fNameDef);
	else
		strcpy(fn,cfg.fileDir.fName);
		
	FILE * fid = fopen(fn,"w");
	WriteToFile(wzpkg,fid);		
	fclose(fid);	
	return 0;
}


