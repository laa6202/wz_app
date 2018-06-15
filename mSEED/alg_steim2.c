//alg_steim2.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mtypes.h"
#include "alg_steim2.h"


//U32 w[16];


int TestAlg(){
	printf("TestAlg\n");
	return 0;
}



int GetFrame0(pFRAME pfrm0,pRAWALL prawAll,int did,int ch,int pos_sof){
	int pos_eof,pos;
	int i;
	U32 w;
	int c[16];
	
	pos = pos_sof;
		w = GetW1(c,prawAll,did,ch,&pos);
		pfrm0->W[1] = w;
	for(i=3;i<16;i++){
		w = GetWs(c,prawAll,did,ch,&pos);
		pfrm0->W[i] = w;
	}
		w = GetW0(c);
		pfrm0->W[0] = w; 
	pos_eof = pos;
	return pos_eof;
}
	


int GetFrames(pFRAME pfrm0,pRAWALL prawAll,int did,int ch,int pos_sof){


	return 0;
}




U32 GetW0(const int * c){
	U32 w0 = 0;
	for(int i=1;i<16;i++){
		if(c[i] == 3)	w0 |= (0x3 << (32-2*i));
		if(c[i] == 2)	w0 |= (0x2 << (32-2*i));
		if(c[i] == 1)	w0 |= (0x1 << (32-2*i));
	}
	return w0;
}


U32 GetW1(int *c,pRAWALL prawAll,int did,int ch,int* pos){
	U32 w1;
	int data = 0;
	int x = prawAll->praw[did]->x[*pos];
	int y = prawAll->praw[did]->y[*pos];
	int z = prawAll->praw[did]->z[*pos];
	if(ch==0) data = 	x;
	if(ch==1) data = 	y;
	if(ch==2) data = 	z;
	*pos = *pos +1;
	w1 = data;
	c[1] = 0;
	printf("GetW1 : pos = %d,data = %d,w1 = %d\n",*pos,data,w1);
	return w1;
}


U32 GetWs(int *c,pRAWALL prawAll,int did, int ch,int *pos){
	U32 w;
	int data[8];
	int diff[7];
	int i;
	int x,y,z;
	int pos1 = *pos;

	printf("GetWs : ");
	PreDiffData(diff,prawAll,did,ch,*pos);	
	int diffR = DiffRange(diff);
	printf("%d\t",diffR);
	printf("\n");
	pos1 += 8;
	*pos = pos1;

	return w;
}


int PreDiffData(int *diff,pRAWALL prawAll,int did,int ch,int pos){
	int data[8];
	int pos1 = pos;
	if(ch==0) data[0] = prawAll->praw[did]->x[pos1];
	if(ch==1) data[0] = prawAll->praw[did]->y[pos1];
	if(ch==2) data[0] = prawAll->praw[did]->z[pos1];
	diff[0] = 0;
	for(int i=0;i<8;i++){
		if(ch==0) data[i] = prawAll->praw[did]->x[pos1];
		if(ch==1) data[i] = prawAll->praw[did]->y[pos1];
		if(ch==2) data[i] = prawAll->praw[did]->z[pos1];
		diff[i] = data[i] - data[i-1];
	//	printf("[%d]:%d:%d  ",pos1,data[i],diff[i]);
		pos1++;	
	}

	return pos1;
}


int DiffRange(int *diff){
	int diffR;
	int maxDiff = 0;
	int absMaxDiff;
	for(int i=1;i<8;i++){	
		maxDiff = (diff[i] > maxDiff) ? diff[i] : maxDiff;
	}
	absMaxDiff = abs(maxDiff);
	if (absMaxDiff <=7 ) return 7;				//4bit
	else if(absMaxDiff <= 15) return 6;		//5bit
	else if(absMaxDiff <= 31) return 5;		//6bit
	else if(absMaxDiff <= 127) return 4;	//8bit
	else if(absMaxDiff <= 511) return 3;	//10bit
	else if(absMaxDiff <= 16383) return 2;	//15bit
	else return 1;

}
