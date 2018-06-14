//gen_mseed.c
//Gen mseed packages and save file.

#include <stdio.h>
#include <string.h>

#include "mtypes.h"
#include "gen_mseed.h"
#include "file_op.h"


int GenMSeed(int did,int ch,RAWALL rawAll,const char * fn){
	printf("...GenMSeed did = %d\tch = %d\tfn= %s\n",did,ch,fn);
	int eof = 0;
	
	FILE * fid = fopen(fn,"w");
	fclose(fid);	
	while(eof == 0) 
	{
		GenPack(fn,rawAll,did,ch);
		eof = EofPack(rawAll,did,ch);	
	}
	return 0;
}


int GenPack(const char *fn,RAWALL rawAll,int did,int ch){
	static int index = 0;
	printf("...GenPack index = %d\n",index);

	GenHead(fn,rawAll,did,ch);
	GenBlock0(fn,rawAll,did,ch);
	GenBlock1(fn,rawAll,did,ch);
	GenFrame0(fn,rawAll,did,ch);
	GenFrames(fn,rawAll,did,ch);

	index++;
	return 0;
} 


int EofPack(RAWALL rawAll,int did,int ch){


	return 1;
}


int GenHead(const char * fn,RAWALL rawAll,int did,int ch){
	HEAD head;
	memset(&head,0,sizeof(HEAD));
//	int utc = rawAll->.utc;
	printf("......utc = \n");
	
	FILE *fid = fopen(fn,"a");
	fwrite(&head,1,sizeof(HEAD),fid);
	fclose(fid);
	return 0;
}



int GenBlock0(const char * fn,RAWALL rawAll,int did,int ch){
	printf("......Block0 = \n");


	return 0;
}




int GenBlock1(const char * fn,RAWALL rawAll,int did,int ch){
	printf("......Block1 = \n");

	return 0;
}


int GenFrame0(const char *fn,RAWALL rawAll,int did,int ch){
	printf("......Frame0 = \n");


	return 0;
}



int GenFrames(const char *fn,RAWALL rawAll,int did,int ch){
	printf("......Frames = \n");

	return 0;
}




