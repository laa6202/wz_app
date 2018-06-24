//alg_head.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#include "mtypes.h"
#include "alg_head.h"
#include "btime.h"


int GetSeq(char * cseq,pRAWALL prawAll,int did,int ch){
	static int seqAll[NUM_DEV][3];
	int seq = seqAll[did][ch]+1;
//	printf("GetSeq : seq = %d\n",seq);
	sprintf(cseq,"%06d",seq);
	
	seqAll[did][ch]++;
	if(seqAll[did][ch] >= 1000000)
		seqAll[did][ch] = 0; 
	return 0;
}


int GetTestStart(pMHEAD phead, pRAWALL prawAll,int did,int ch){
	static int index;	
	phead->start.year = 2008;
	phead->start.day = 162;
	phead->start.hour = 14;
	phead->start.min = 28;
	phead->start.sec = 30+index*0.5;
	phead->start.res = 0;
	phead->start.us100 = 10;
	ChangeEndianU16(&(phead->start.year));
	ChangeEndianU16(&(phead->start.day));
	ChangeEndianU16(&(phead->start.us100));

	index++;
	return 0;
}


int GetStart(pMHEAD phead,pRAWALL prawAll,int did,int ch){
	
	U32 utc = prawAll->praw[did]->utc;
	U32 uns = prawAll->praw[did]->ns;
	int pos = (ch == 0) ? prawAll->praw[did]->pos_chx :
						(ch == 1) ? prawAll->praw[did]->pos_chy :
						(ch == 2) ? prawAll->praw[did]->pos_chz : 0x0;

//	printf("GetStart : utc = %u\tuns = %u\tpos = %d\n",utc,uns,pos);


	CovU2BTIME(&(phead->start),utc,uns,pos,phead->rate);

	return 0;
}


int GetNumSample(U16 * num,pRAWALL prawAll,int did,int ch){

	*num = 800;

	ChangeEndianU16(num);
	return 0;
}


int ChangeEndianS16(S16 * data){
	S16 b0,b1;
	b0 = (*data & 0xff);
	b1 = (*data & 0xff00) >> 8;
	*data = (b0 << 8) | b1;
	return 0;
}


int ChangeEndianU16(U16 * data){
	U16 b0,b1;
	b0 = (*data & 0xff);
	b1 = (*data & 0xff00) >> 8;
	*data = (b0 << 8) | b1;
	return 0;
}




