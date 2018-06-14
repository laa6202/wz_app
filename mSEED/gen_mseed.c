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
	MHEAD head;
	memset(&head,0,sizeof(MHEAD));
//	int utc = rawAll->.utc;
	printf("......HEAD.utc = \n");
	
	FILE *fid = fopen(fn,"a");
	fwrite(&head,1,sizeof(MHEAD),fid);
	fclose(fid);
	return 0;
}



int GenBlock0(const char * fn,RAWALL rawAll,int did,int ch){
	printf("......Block0 = \n");
	BLOCK0 block0;
	memset(&block0,0,sizeof(BLOCK0));
	FILE *fid = fopen(fn,"a");
	fwrite(&block0,1,sizeof(BLOCK0),fid);
	fclose(fid);

	return 0;
}


int GenBlock1(const char * fn,RAWALL rawAll,int did,int ch){
	printf("......Block1 = \n");
	BLOCK1 block1;
	memset(&block1,0,sizeof(BLOCK1));
	FILE *fid = fopen(fn,"a");
	fwrite(&block1,1,sizeof(BLOCK1),fid);
	fclose(fid);
	return 0;
}


int GenFrame0(const char *fn,RAWALL rawAll,int did,int ch){
	printf("......Frame0 = \n");
	FRAME frm0;
	memset(&frm0,0,sizeof(FRAME));
	FILE *fid = fopen(fn,"a");
	fwrite(&frm0,1,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}



int GenFrames(const char *fn,RAWALL rawAll,int did,int ch){
	printf("......Frames = \n");
	FRAME frms[6];
	memset(frms,0,6*sizeof(FRAME));
	FILE * fid = fopen(fn,"a");
	fwrite(frms,6,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}




