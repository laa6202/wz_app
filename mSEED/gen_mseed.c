//gen_mseed.c
//Gen mseed packages and save file.
//GenMSeed handle 1 device and 1 channel,as gen 1 file per call.


#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mtypes.h"
#include "gen_mseed.h"
#include "file_op.h"
#include "alg_steim2.h"
#include "alg_head.h"


int GenMSeed(int did,int ch,pRAWALL prawAll,const char * fn){
	printf("...GenMSeed did = %d\tch = %d\tfn= %s\n",did,ch,fn);
	int end = 0;
	
	FILE * fid = fopen(fn,"wb");
	fclose(fid);	
	while(end == 0) 
	{
		GenPack(fn,prawAll,did,ch);
		end = EofPack(prawAll,did,ch);	
	}
	return 0;
}


int GenPack(const char *fn,pRAWALL prawAll,int did,int ch){
	int pos_sof;
	if(ch==0) pos_sof = prawAll->praw[did]->pos_chx;
	else if(ch==1) pos_sof = prawAll->praw[did]->pos_chy;
	else if(ch==2) pos_sof = prawAll->praw[did]->pos_chz;
	printf("\n...GenPack did = %d\tch = %d\tpos_sof = %d\n",did,ch,pos_sof);

	GenHead(fn,prawAll,did,ch);
	GenBlock0(fn,prawAll,did,ch);
	GenBlock1(fn,prawAll,did,ch);
	GenFrame0(fn,prawAll,did,ch);
	GenFrames(fn,prawAll,did,ch);
	UpdateHead(fn,prawAll,did,ch,pos_sof);
	UpdateFrm0(fn,prawAll,did,ch,pos_sof);
	return 0;
} 


int EofPack(pRAWALL prawAll,int did,int ch){
	int len = prawAll->praw[did]->len;
	int pos_sof;
	if(ch==0) pos_sof = prawAll->praw[did]->pos_chx;
	else if(ch==1) pos_sof = prawAll->praw[did]->pos_chy;
	else if(ch==2) pos_sof = prawAll->praw[did]->pos_chz;

	if(pos_sof >= len) {
		if(ch==0) prawAll->praw[did]->pos_chx = 0;
		else if(ch==1) prawAll->praw[did]->pos_chy = 0;
		else if(ch==2) prawAll->praw[did]->pos_chz = 0;
		return 1;
	}
	else 
		return 0;
}


int GenHead(const char * fn,pRAWALL prawAll,int did,int ch){
	MHEAD head;
	memset(&head,0,sizeof(MHEAD));
//	int utc = rawAll->.utc;
	
	GetSeq(head.seq,prawAll,did,ch);
	printf("......HEAD.seq = %s......\n",head.seq);
	head.quality = 'D';
	head.res = 0x20;
	strcpy(head.station, "SLT  ");
	strcpy(head.location,"00");
	if(ch==0) strcpy(head.channel,"SHN");	
	if(ch==1) strcpy(head.channel,"SHE");	
	if(ch==2) strcpy(head.channel,"SHZ");
	strcpy(head.network,"XX");
	head.rate = 2000;
	ChangeEndianS16(&head.rate);
	GetStart(&head,prawAll,did,ch);
	GetNumSample(&(head.num_sample),prawAll,did,ch);	
	head.mult = 0x1;
	ChangeEndianS16(&head.mult);
	head.act_flags = 0;
	head.io_flags = 0x20;
	head.data_flags = 0;
	head.num_block = 0x1;
	head.time_cor = 0;
	head.offset_data = 0x40;
	head.offset_block0 = 0x30;
	ChangeEndianU16(&head.offset_data);
	ChangeEndianU16(&head.offset_block0);

	FILE *fid = fopen(fn,"ab");
	if(fid == NULL) {
		printf("!!!Can not open %s\n",fn);
		_exit(-1);
	}
	fwrite(&head,1,sizeof(MHEAD),fid);
	fclose(fid);
	return 0;
}



int GenBlock0(const char * fn,pRAWALL prawAll,int did,int ch){
//	printf("......GenBlock0...... \n");
	BLOCK0 block0;
	memset(&block0,0,sizeof(BLOCK0));

	block0.code = 0x3e8;
	block0.offset = 0;
	block0.enc = 0xb;
	block0.order = 0x1;
	block0.len = 0x9;
	block0.res = 0;

	ChangeEndianU16(&(block0.code));
	ChangeEndianU16(&(block0.offset));
	

	FILE *fid = fopen(fn,"ab");
	fwrite(&block0,1,sizeof(BLOCK0),fid);
	fclose(fid);

	return 0;
}


int GenBlock1(const char * fn,pRAWALL prawAll,int did,int ch){
//	printf("......GenBlock1......\n");
	BLOCK1 block1;
	memset(&block1,0,sizeof(BLOCK1));
	FILE *fid = fopen(fn,"ab");
	fwrite(&block1,1,sizeof(BLOCK1),fid);
	fclose(fid);
	return 0;
}


int GenFrame0(const char *fn,pRAWALL prawAll,int did,int ch){
//	printf("......GenFrame0......\n");
	int pos_sof, pos_eof;

	FRAME frm0;
	memset(&frm0,0,sizeof(FRAME));
	
	if(ch==0) pos_sof = prawAll->praw[did]->pos_chx;
	else if(ch==1) pos_sof = prawAll->praw[did]->pos_chy;
	else if(ch==2) pos_sof = prawAll->praw[did]->pos_chz;

	pos_eof = GetFrame0(&frm0,prawAll,did,ch,pos_sof);
//	printf("GenFrm0: ch=%d,sof=%d,eof=%d\n",ch,pos_sof,pos_eof);

	if(ch==0) prawAll->praw[did]->pos_chx = pos_eof;
	else if(ch==1) prawAll->praw[did]->pos_chy = pos_eof;
	else if(ch==2) prawAll->praw[did]->pos_chz = pos_eof;


	FILE *fid = fopen(fn,"ab");
	fwrite(&frm0,1,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}



int GenFrames(const char *fn,pRAWALL prawAll,int did,int ch){
//	printf("......GenFrames......\n");
	int pos_sof,pos_eof;
	int i;
	FRAME frms[6];
	memset(frms,0,6*sizeof(FRAME));


	if(ch==0) pos_sof = prawAll->praw[did]->pos_chx;
	else if(ch==1) pos_sof = prawAll->praw[did]->pos_chy;
	else if(ch==2) pos_sof = prawAll->praw[did]->pos_chz;

	for(i=0;i<6;i++){
		pos_eof = GetFrames(frms+i,prawAll,did,ch,pos_sof);
//		printf("GenFrms: i=%d,sof=%d,eof=%d\n",i,pos_sof,pos_eof);
		pos_sof = pos_eof;
	}

	if(ch==0) prawAll->praw[did]->pos_chx = pos_eof;
	else if(ch==1) prawAll->praw[did]->pos_chy = pos_eof;
	else if(ch==2) prawAll->praw[did]->pos_chz = pos_eof;

	FILE * fid = fopen(fn,"ab");
	fwrite(frms,6,sizeof(FRAME),fid);
	fclose(fid);
	return 0;
}



int UpdateHead(const char * fn,pRAWALL prawAll,int did,int ch,int sof){
//	printf("......UpdateHead......\n");
	int eof;
	int len = prawAll->praw[did]->len;
	if(ch==0) eof=prawAll->praw[did]->pos_chx;
	if(ch==1) eof=prawAll->praw[did]->pos_chy;
	if(ch==2) eof=prawAll->praw[did]->pos_chx;
	if(eof >= len)	eof = len;
	int numPoint = eof - sof;
	U16 num = numPoint;
	ChangeEndianU16(&num);
	
	FILE * fid = fopen(fn,"rb+");
	int ret = fseek(fid,-482L,SEEK_END);
	if(ret != 0)
		perror("");
	int fpos = ftell(fid);
	fwrite(&num,1,sizeof(U16),fid);
	fclose(fid);

//	printf("UpdateHead : sof=%d,eof=%d,num=%d,",sof,eof,numPoint);
//	printf("fpos=%d,write=%04x\n",fpos,num);
	return 0;
}



int UpdateFrm0(const char * fn,pRAWALL prawAll,int did,int ch,int sof){
//	printf("......UpdateFrm0......\n");
	int eof;
	int len = prawAll->praw[did]->len;
	if(ch==0) eof=prawAll->praw[did]->pos_chx;
	if(ch==1) eof=prawAll->praw[did]->pos_chy;
	if(ch==2) eof=prawAll->praw[did]->pos_chx;
	if(eof >= len) eof = len;
	int numPoint = eof - sof;
	U16 num = numPoint;
	int data;
	if(ch==0) data = prawAll->praw[did]->x[eof-1];
	if(ch==1) data = prawAll->praw[did]->y[eof-1];
	if(ch==2) data = prawAll->praw[did]->z[eof-1];
	int dataEof = data;
	ChangeEndian32(&dataEof);

	FILE * fid = fopen(fn,"rb+");
	fseek(fid,-440L,SEEK_END);
	fwrite(&dataEof,1,sizeof(U32),fid);	
	fclose(fid);
//	printf("UpdateHead : sof=%d,eof=%d,num=%d,",sof,eof,numPoint);
//	printf("data=%d,write=0x%08x\n",data,dataEof);
	return 0;
}



