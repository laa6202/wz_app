//gen_mseed.c
//Gen mseed packages and save file.
//GenMSeed handle 1 device and 1 channel,as gen 1 file per call.


#include <stdio.h>
#include <string.h>

#include "mtypes.h"
#include "gen_mseed.h"
#include "file_op.h"
#include "alg_steim2.h"



int GenMSeed(int did,int ch,pRAWALL prawAll,const char * fn){
	printf("...GenMSeed did = %d\tch = %d\tfn= %s\n",did,ch,fn);
	int eof = 0;
	
	FILE * fid = fopen(fn,"w");
	fclose(fid);	
	while(eof == 0) 
	{
		GenPack(fn,prawAll,did,ch);
		GenPack(fn,prawAll,did,ch);
		eof = EofPack(prawAll,did,ch);	
	}
	return 0;
}


int GenPack(const char *fn,pRAWALL prawAll,int did,int ch){
	printf("...GenPack did = %d\tch = %d\n",did,ch);

	GenHead(fn,prawAll,did,ch);
	GenBlock0(fn,prawAll,did,ch);
	GenBlock1(fn,prawAll,did,ch);
	GenFrame0(fn,prawAll,did,ch);
	GenFrames(fn,prawAll,did,ch);

	return 0;
} 


int EofPack(pRAWALL prawAll,int did,int ch){


	return 1;
}


int GenHead(const char * fn,pRAWALL prawAll,int did,int ch){
	MHEAD head;
	memset(&head,0,sizeof(MHEAD));
//	int utc = rawAll->.utc;
	printf("......HEAD.utc = \n");
	
	FILE *fid = fopen(fn,"a");
	fwrite(&head,1,sizeof(MHEAD),fid);
	fclose(fid);
	return 0;
}



int GenBlock0(const char * fn,pRAWALL prawAll,int did,int ch){
	printf("......Block0 = \n");
	BLOCK0 block0;
	memset(&block0,0,sizeof(BLOCK0));
	FILE *fid = fopen(fn,"a");
	fwrite(&block0,1,sizeof(BLOCK0),fid);
	fclose(fid);

	return 0;
}


int GenBlock1(const char * fn,pRAWALL prawAll,int did,int ch){
	printf("......Block1 = \n");
	BLOCK1 block1;
	memset(&block1,0,sizeof(BLOCK1));
	FILE *fid = fopen(fn,"a");
	fwrite(&block1,1,sizeof(BLOCK1),fid);
	fclose(fid);
	return 0;
}


int GenFrame0(const char *fn,pRAWALL prawAll,int did,int ch){
	printf("......Frame0 = \n");
	int pos;

	FRAME frm0;
	memset(&frm0,0,sizeof(FRAME));
	
	if(ch==0) pos = prawAll->praw[did]->pos_chx;
	else if(ch==1) pos = prawAll->praw[did]->pos_chy;
	else if(ch==2) pos = prawAll->praw[did]->pos_chz;

	pos = GetFrame0(&frm0,prawAll,did,ch,pos);

	if(ch==0) prawAll->praw[did]->pos_chx = pos;
	else if(ch==1) prawAll->praw[did]->pos_chy = pos;
	else if(ch==2) prawAll->praw[did]->pos_chz = pos;


	FILE *fid = fopen(fn,"a");
	fwrite(&frm0,1,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}



int GenFrames(const char *fn,pRAWALL prawAll,int did,int ch){
	printf("......Frames = \n");
	int pos;
	int i;
	FRAME frms[6];
	memset(frms,0,6*sizeof(FRAME));


	for(i=0;i++;i<7){
		pos = GetFrames(frms+i,prawAll,did,ch,pos);
	}

	FILE * fid = fopen(fn,"a");
	fwrite(frms,6,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}




